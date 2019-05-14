/******************************************************************
 * bozon.h
 *
 * Author: Glenn Skelton
 * Last Modified: November 21, 2018
 *
 * Inspiration borrowed from tutorial example code
 *
 ******************************************************************/


#include <iostream>
using namespace std;

#ifndef BOZON_H
#define BOZON_H

class bozon {
public:
	bozon();
	bozon(double time, int type, int id);
	virtual ~bozon();

	string toString();

	double time; // time of the event
	int type; // state of either yodeling or sleeping
	int id; // bozon unique identifier
};

#endif /* BOZON_H */
