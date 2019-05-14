/******************************************************************
 * bozon.cpp
 *
 * Author: Glenn Skelton
 * Last Modified: November 21, 2018
 *
 * Inspiration borrowed from tutorial example code
 *
 ******************************************************************/

#include <iostream>
#include "bozon.h"

using namespace std;


bozon::bozon() : time(0.0f), type(0), id(0) {

}

bozon::bozon(double time, int type, int id) {
	this->time = time;
	this->type = type;
	this->id = id;
}

bozon::~bozon() {

}

/**
 * Purpose: To provide a string representation of the bozon.
 */
string bozon::toString() {
	return "(ID :" + to_string(this->id) + ", " + to_string(this->time) + ", " + to_string(this->type) + ")";
}


