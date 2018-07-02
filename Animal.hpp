/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: Animal.hpp, specification file for the Animal 
		base class. This class serves as an interface for the other 
		animal-type classes.
*********************************************************************/

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

class Animal {
private:
	
protected:
	int age;
	int cost;
	int numOfBabies;
	int foodCost;
	int payoff;

public:
	//Animal();
	//~Animal();

	// Pure virtual functions
	virtual int getAge() = 0;
	virtual int getCost() = 0;
	virtual int getNumOfBabies() = 0;
	virtual int getFoodCost() = 0;
	virtual int getPayoff() = 0;
	virtual void incrementAge() = 0;

};
#endif // !ANIMAL_HPP
