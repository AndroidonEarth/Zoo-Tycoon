/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: Turtle.hpp, specification file for the Turtle
		derived class.
*********************************************************************/

#ifndef TURTLE_HPP
#define TURTLE_HPP

#include "Animal.hpp"

class Turtle : public Animal {
private:
	Turtle();

protected:
	// Inherits data member variables from Animal

public:
	Turtle(int aFoodCost, int aAge = 0 );

	int getAge() { return this->age; }
	int getCost() { return this->cost; }
	int getNumOfBabies() { return this->numOfBabies; }
	int getFoodCost() { return this->foodCost; }
	int getPayoff() { return this->payoff; }
	void incrementAge() { this->age++; }
};

#endif // !TURTLE_HPP
