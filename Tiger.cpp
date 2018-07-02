/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: Tiger.cpp, implementation file for the Tiger
		derived class.
*********************************************************************/

#include "Tiger.hpp"

/*
* Constructor for the Tiger class. This constructor must be used over
* default constructor in order to properly assign an age and food cost
* based on the project specifications.
*/
Tiger::Tiger(int aFoodCost, int aAge) {
	this->age = aAge;
	this->cost = 10000;
	this->numOfBabies = 1;
	this->foodCost = aFoodCost * 5;
	this->payoff = 2000;
}