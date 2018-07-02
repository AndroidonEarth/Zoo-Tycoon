/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: Turtle.cpp, implementation file for the Turtle
		derived class.
*********************************************************************/

#include "Turtle.hpp"

/*
* Constructor for the Turtle class. This constructor must be used over
* default constructor in order to properly assign an age and food cost
* based on the project specifications.
*/
Turtle::Turtle(int aFoodCost, int aAge) {
	this->age = aAge;
	this->cost = 100;
	this->numOfBabies = 10;
	this->foodCost = aFoodCost * 0.5;
	this->payoff = 5;
}