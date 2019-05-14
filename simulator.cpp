/******************************************************************
 * simulator.cpp
 *
 * Author: Glenn Skelton
 * Last Modified: November 21, 2018
 *
 * Inspiration borrowed from tutorial example code
 *
 ******************************************************************/


#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>

#include "simulator.h"
#include "bozon.h"
#include "atmosphere.h"

#define bozon_sort(x) sort(x.begin(), x.end(), [](const bozon &a, const bozon &b) -> bool {return a.time > b.time;})

using namespace std;


/****************** SIMULATOR CLASS ************************/
// constructor/deconstructor
simulator::simulator(int M, double S, double Y) {
	this->setM(M);
	this->setS(S);
	this->setY(Y);
}
simulator::~simulator() {

}

/*********************** GETTER/SETTER ************************/
int simulator::getM() {
	return this->M;
}
void simulator::setM(int M) {
	this->M = M > 0 ? M : 0; // signifies unset
}
double simulator::getS() {
	return this->S;
}
void simulator::setS(double S) {
	this->S = S > 0.0f ? S : 0.0f; // signifies unset
}
double simulator::getY() {
	return this->Y;
}
void simulator::setY(double Y) {
	this->Y = Y > 0.0f ? Y : 0.0f; // signifies unset
}

/************************* SIMULATOR METHODS ****************************/

/**
 * Purpose: To run the simulation based on the parameters set.
 */
void simulator::run() {
	atmosphere channel = atmosphere(); // initialize the statistical variables
	bozon curEvent; // local storage for current bozon
	int ttlSinging = 0; // counter for how many bozons are singing at a time
	bool perfect = false; // variable for knowing if a yodel was perfect or not
	bozon nextEvent; // store the next event being created
	vector<bozon> eventList; // list of all events
	double curTime; // simulator current time

	curTime = 0.0;
	srandom(SEED); // init random seed

	// initialize all events
	for (int i = 0; i < getM(); i++) {
		eventList.push_back(bozon(exponential(this->S), SLEEP, i)); // all bozons start out sleeping
	}
	bozon_sort(eventList); // sort the eventList


	/************************************* Main simulation loop *************************************/
	while (curTime < SIM_END_TIME) {
		if (!eventList.empty()) {
			curEvent = eventList.back(); // get the last element (the next to leave)
			eventList.pop_back(); // remove the last element
#if DEBUG
			cout << curEvent.toString() << endl;
#endif
		}
		else {
			cout << "Event list is empty" << endl;
			break; // no more events to process
		}

		// update current time
		curTime = curEvent.time;

		// Evaluate event
		switch (curEvent.type) {
		case SLEEP: // sleep finishing, yodle event starting
			switch (channel.status) {
			case SILENT:
				// channel is now melodies
				channel.ttlTimeSilent += curTime - channel.silentStartTime;
				channel.status = MELODIOUS;
				channel.melodiousStartTime = curTime;
				perfect = true; // remains until all events finish or another yodel starts
				break;
			case MELODIOUS:
				// record the amount of melodious time
				channel.ttlTimeMelodious += curTime - channel.melodiousStartTime;
				channel.status = SCREECH; // there are now 2 singing
				channel.screechStartTime = curTime;
				perfect = false; // yodel is no longer perfect
				break;
			case SCREECH: // do nothing since we are only adding more singing
				break;
			default:
				cout << "Invalid type of channel" << endl;
			}

			// generate new event
			channel.ttlYodels++; // incrememnt since a yodle event has begun
			ttlSinging++; // add to the total current singers

			// define this bozons next event which will be the yodel end time
			nextEvent = bozon(exponential(this->Y) + curTime, YODLE, curEvent.id);
			break;


		case YODLE: // yodle event finishing, sleep starting
			switch (channel.status) {
			case SILENT:
				cout << "Error, silent state for a bozon yodelling is not possible" << endl;
				break;
			case MELODIOUS:
				// turn to silent since now no bozon is singing
				channel.status = SILENT;
				channel.ttlTimeMelodious += curTime - channel.melodiousStartTime;
				channel.silentStartTime = curTime; // reset the silent time
				if (perfect) channel.ttlPerfect++; // a perfect yodel so add to the total
				break;
			case SCREECH:
				if (ttlSinging-1 == 1) {
					// update state variables
					channel.status = MELODIOUS;
					channel.ttlTimeScreech += curTime - channel.screechStartTime;
					channel.melodiousStartTime = curTime;
				}
				break;
			default:
				cout << "Invalid type of channel" << endl;
			}

			if (ttlSinging > 0) ttlSinging--; // decrement the total current bozons singing

			// generate new event
			nextEvent = bozon(bozon(exponential(this->S) + curTime, SLEEP, curEvent.id));
			break;
		default:
			cout << "Invalid type of event:" << endl;
		}

		eventList.push_back(nextEvent); // add event updated new event into list
		bozon_sort(eventList); // sort the eventList
	}

	// update statistical counters one last time
	switch (channel.status) {
	case SILENT:
		channel.ttlTimeSilent += curTime - channel.silentStartTime;
		break;
	case MELODIOUS:
		channel.ttlTimeMelodious += curTime - channel.melodiousStartTime;
		if (perfect) channel.ttlPerfect++;
		break;
	case SCREECH:
		channel.ttlTimeScreech += curTime - channel.screechStartTime;
		break;
	}

#if DEBUG
	cout << "done test" << endl;
#endif
	/****************************************** Report ****************************************/
	cout << "************************ REPORT *************************" << endl;
	cout << "Total Yodels: " << channel.ttlYodels << endl;
	cout << "Total Perfect Yodels: " <<  channel.ttlPerfect << endl;
	cout << "Total Time Units Silent: " << channel.ttlTimeSilent << endl;
	cout << "Total Time Units Melodious: " << channel.ttlTimeMelodious << endl;
	cout << "Total Time Units Screechy: " << channel.ttlTimeScreech << endl;
#if DEBUG
	cout << "Total Time: " << channel.ttlTimeScreech + channel.ttlTimeMelodious + channel.ttlTimeSilent << endl;
#endif
	printf("Percentage Perfect Yodels: %.2f%%\n", (float)channel.ttlPerfect / channel.ttlYodels * 100);
	printf("Percentage Silent: %.2f%%\n", channel.ttlTimeSilent / SIM_END_TIME * 100);
	printf("Percentage Melodious: %.2f%%\n", channel.ttlTimeMelodious / SIM_END_TIME * 100);
	printf("Percentage Sceechy: %.2f%%\n", channel.ttlTimeScreech / SIM_END_TIME * 100);
	cout << "*********************************************************" << endl;

}

/**
 * Purpose: To generate a random floating point number uniformly distributed
 * in [0,1].
 *
 * borrowed from assignment description
 */
double simulator::uniform01() {
	return (((double)1.0 * random()) / (1.0 * MAX_INT));
}

/**
 * Purpose: Generate a random floating point number from an exponential distribution
 * with a mean mu.
 *
 * borrowed from assignment description
 */
double simulator::exponential(double mu) {
	return -(mu) * log(uniform01());
}










