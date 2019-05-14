/******************************************************************
 * main.cpp
 *
 * Author: Glenn Skelton
 * Last Modified: November 21, 2018
 *
 ******************************************************************/


#include <iostream>
#include <math.h>
#include "simulator.h"

using namespace std;

/* PROTOTYPES */
void printMainMenu();

/**
 * Purpose: To drive the simulation program by prompting the user for specifications of
 * M, S, and Y.
 */
int main(int argc, char *argv[]) {
	// receive commands from user to run test
	bool running = true;
	bool validChoice = false;
	char input;

	printMainMenu();
	do {
		cout << ">>>"; // place for choice
		// read in input
		input = getchar();

		// safely check the input
		while (!validChoice) {
			if (input == '1') validChoice = true;
			else if (input == '2') {
				validChoice = true;
				running = false;
			}
			else {
				// flush whatever remains in the buffer
				while ((input = getchar() != '\n') && (input != EOF)); // flush buffer
				// prompt user again
				cout << "Invalid input, please enter either 1 or 2\n>>>";
				input = getchar();
			}
		}
		// valid choice so go on
		if (input == '1') {
			// run all simulations of different colony sizes
			int M;
			double Y, S;

			cout << "Please enter M, S, and Y (<M S Y>): ";
			// get input from user
			validChoice = false;
			while (!validChoice) {
				if (scanf("%d %lf %lf", &M, &S, &Y) != 3) {
					cout << "Invalid entry, please try again: ";
				}
				else validChoice = true;
				while ((input = getchar() != '\n') && (input != EOF)); // flush buffer
			}

			// if all is good, run the simulation
			simulator *sim1 = new simulator(M, S, Y);
			cout << "simulator set up. Now running" << endl;
			sim1->run();
			delete sim1;
		}

		validChoice = false; // reset
		printMainMenu(); // prompt user again
	} while (running);

	return 0;
}

/**
 * Purpose: To print out the main menu contents.
 */
void printMainMenu() {
	cout << "\n*** Welcome to the Bozon colony simulator ***" << endl << endl;
	cout << "Please select an option" << endl;
	cout << "1-Run Simulation" << endl;
	cout << "2-quit" << endl << endl;
}


