/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: Tiger.hpp, specification file for the Tiger 
		derived class.
*********************************************************************/

#ifndef TIGER_HPP
#define TIGER_HPP

#include "Animal.hpp"

class Tiger : public Animal {
private:
	Tiger();

protected:
	// Inherits data member variables from Animal

public:
	Tiger(int aFoodCost, int aAge = 0);

	int getAge() { return this->age; }
	int getCost() { return this->cost; }
	int getNumOfBabies() { return this->numOfBabies; }
	int getFoodCost() { return this->foodCost; }
	int getPayoff() { return this->payoff; }
	void incrementAge() { this->age++; }

};

#endif // !TIGER_HPP
