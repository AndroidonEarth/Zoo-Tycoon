/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: Penguin.hpp, specification file for the Penguin 
		derived class.
*********************************************************************/

#ifndef PENGUIN_HPP
#define PENGUIN_HPP

#include "Animal.hpp"

class Penguin : public Animal {
private:
	Penguin();

protected:
	// Inherits data member variables from Animal

public:
	Penguin(int aFoodCost, int aAge = 0);

	int getAge() { return this->age; }
	int getCost() { return this->cost; }
	int getNumOfBabies() { return this->numOfBabies; }
	int getFoodCost() { return this->foodCost; }
	int getPayoff() { return this->payoff; }
	void incrementAge() { this->age++; }

};

#endif // !PENGUIN_HPP
