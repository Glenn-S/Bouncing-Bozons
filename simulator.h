/******************************************************************
 * simulator.h
 *
 * Author: Glenn Skelton
 * Last Modified: November 21, 2018
 *
 * Inspiration borrowed from tutorial example code
 *
 ******************************************************************/


#include <iostream>
using namespace std;

#ifndef SIMULATOR_H
#define SIMULATOR_H

#define MAX_INT 2147483647 // maximum positive integer 2^31 - 1
#define SIM_END_TIME 1000000 // simulation end time
#define SEED 12345 // seed value for pseudo random number generator

// Bozon states
#define SLEEP 1
#define YODLE 2

// Atmosphere states
#define SILENT 0
#define MELODIOUS 1
#define SCREECH 2

#define DEBUG 0 // for debugging purposes

class simulator {
public:
	simulator(int M, double S, double Y);
	virtual ~simulator();

	void run();
	double uniform01();
	double exponential(double mu);

	int getM();
	void setM(int M);
	double getS();
	void setS(double S);
	double getY();
	void setY(double Y);

private:
	int M; // number of Bozons
	double S; // mean sleep duration
	double Y; // mean yodel duration
};


#endif /* SIMULATOR_H */
