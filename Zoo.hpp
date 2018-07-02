/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: Zoo.hpp, specification file for the Zoo class.
*********************************************************************/

#ifndef ZOO_HPP
#define ZOO_HPP

#include "Animal.hpp"

enum AnimalType { TIGER, PENGUIN, TURTLE };

enum RandomEvent { SICKNESS, ATTENDBOOM, BIRTH, NOTHING };

class Zoo {

private:
	Animal*** animals;		// To hold an array of animals for each animal type.
	int* capacities;		// To keep track of the capacity of each array.
	int* numOfAnimals;		// To keep track of the number of animals in each array.
	int* shuffledTypes;		// To hold an index number for each animal type to shuffle.
	int numOfTypes;			// To keep track of the current number of animal types.

	AnimalType randomType;	// To hold a randomly selected animal type from an event.
	RandomEvent eventName;	// To hold the name of the event that occured.

	int money;				// To hold the player's total money.
	int days;				// To hold the current day.
	int feedingCost;		// To hold the total cost of feeding all the animals.
	int payoff;				// To hold the total payoff from each animal.
	int bonus;				// To hold the bonus if the attendance boom event occured.

	void runGame();
	void ageAllAnimals();
	void payFeedingCost();
	void shuffleTypeIndexes();
	void sicknessEvent();
	void attendBoomEvent(int minBonus, int maxBonus);
	void animalBornEvent(int adultAge, int baseFoodCost);
	void calcProfits();
	void printAnimalInfo(AnimalType type, int baseFoodCost);
	void createAnimal(AnimalType type, Animal** animal, int baseFoodCost, int age = 1);
	void addAnimal(AnimalType type, Animal** animal);
	void printDayStart();
	void printCosts();
	void printRandomEvent();
	void printProfits();
	void printDayEnd();

	

public:
	Zoo();
};

#endif // !ZOO_HPP
