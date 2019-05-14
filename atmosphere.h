/******************************************************************
 * atmosphere.h
 *
 * Author: Glenn Skelton
 * Last Modified: November 21, 2018
 *
 * Inspiration borrowed from tutorial example code
 *
 ******************************************************************/

#include <iostream>
using namespace std;

#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H

class atmosphere {
public:
	atmosphere();
	virtual ~atmosphere();

	/* State variables */
	int status; // current state of the environment (silent, melodious, screech)
	double silentStartTime; // keep track of when a silent period begins
	double melodiousStartTime; // keep track of when a melodius period begins
	double screechStartTime; // keep track of when a screech period begins

	/* Statistical counters for environment */
	int ttlYodels; // total number of yodels attempted
	int ttlPerfect; // total number of yodels perfect from start to finish
	double ttlTimeSilent; // total time that the colony was silent
	double ttlTimeMelodious; // total time that the colony had melodious yodeling
	double ttlTimeScreech; // total time that the colony had screeched yodeling
private:

};

#endif /* ATMOSPHERE_H */
