/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: main.cpp, driver for the Zoo class. Simply starts
		the seed for the random number generator, then creates a
		Zoo object, which automatically starts the game.
*********************************************************************/

#include "Zoo.hpp"

#include <iostream>
#include <ctime>

// Testing
using std::cout;

int main() {

	// Setup seed and srand for use with rand().
	unsigned seed = time(0);
	srand(seed);

	// Create a Zoo object to begin the game.
	Zoo game;

	getchar();
	return 0;
}