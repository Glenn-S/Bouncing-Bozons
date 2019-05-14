/******************************************************************
 * atmosphere.cpp
 *
 * Author: Glenn Skelton
 * Last Modified: November 21, 2018
 *
 * Inspiration borrowed from tutorial example code
 *
 ******************************************************************/

#include <iostream>

#include "atmosphere.h"
using namespace std;


atmosphere::atmosphere() : status(0),
						   silentStartTime(0.0f),
						   melodiousStartTime(0.0f),
						   screechStartTime(0.0f),
						   ttlYodels(0),
						   ttlPerfect(0),
						   ttlTimeSilent(0.0f),
						   ttlTimeMelodious(0.0f),
						   ttlTimeScreech(0.0f) {
 
}


atmosphere::~atmosphere() {

}

