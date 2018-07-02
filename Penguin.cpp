/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: Penguin.cpp, implementation file for the Penguin
		derived class.
*********************************************************************/

#include "Penguin.hpp"

/*
* Constructor for the Penguin class. This constructor must be used over
* default constructor in order to properly assign an age and food cost
* based on the project specifications.
*/
Penguin::Penguin(int aFoodCost, int aAge) {
	this->age = aAge;
	this->cost = 1000;
	this->numOfBabies = 5;
	this->foodCost = aFoodCost;
	this->payoff = 100;
}