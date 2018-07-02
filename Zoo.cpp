/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: Zoo.cpp, implementation file for the Zoo class.
*********************************************************************/

// Classes
#include "Zoo.hpp"
#include "Tiger.hpp"
#include "Penguin.hpp"
#include "Turtle.hpp"

// Helper functions
#include "inputValidation.hpp"
#include "menu.hpp"

// I/O and printing
#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::left;
using std::right;

/*
* Constructor for the Zoo class. Simply calls runGame when
* created to start the game.
*/
Zoo::Zoo() {
	runGame();
}

/**
* The main function of the Zoo class. Holds all important variables,
* user inputs, and function calls to run the game. This function
* is automatically called when a Zoo object is created, and when the
* function is finished control returns to main() and the program ends.
*/
void Zoo::runGame() {

	//////////////////////////////////////////////////////////////////
	// Variables
	//////////////////////////////////////////////////////////////////

	// Constant variables.
	const int MIN_STARTING_ANIMALS = 1;
	const int MAX_STARTING_ANIMALS = 2;
	const int STARTING_CAPACITY = 10;
	const int START_NUM_OF_TYPES = 3;
	const int NUM_OF_EVENTS = 4;
	const int STARTING_MONEY = 100000;
	const int BONUS_MIN = 250;
	const int BONUS_MAX = 500;
	const int ADULT_AGE = 3;
	const int BASE_FOOD_COST = 10;

	// Game variables
	AnimalType typeToBuy;
	int eventNum;
	bool cancel;
	bool animalAdded;
	Animal* animalPtr;

	// User choice input variables
	char choice;
	int startingAnimals;

	//////////////////////////////////////////////////////////////////
	// Program begins.
	//////////////////////////////////////////////////////////////////

	// Display the intro and first menu.
	displayIntro();
	firstMenu();

	// Get menu choice. charChoice == '2' means user selected to quit instead.
	choice = getMenuChoice('2');

	// Start program, beginning with getting starting info.
	while (choice != '2') {
		
		//////////////////////////////////////////////////////////////////
		// Initialize starting variables
		//////////////////////////////////////////////////////////////////

		// Initialize starting money.
		money = STARTING_MONEY;
		days = 0;
		numOfTypes = START_NUM_OF_TYPES;
		
		// Allocate memory.
		animals = new Animal**[START_NUM_OF_TYPES];
		capacities = new int[START_NUM_OF_TYPES];
		numOfAnimals = new int[START_NUM_OF_TYPES];
		shuffledTypes = new int[START_NUM_OF_TYPES];

		for (int i = 0; i < START_NUM_OF_TYPES; i++) {

			animals[i] = new Animal*[STARTING_CAPACITY];
			capacities[i] = STARTING_CAPACITY;
			numOfAnimals[i] = 0;
			shuffledTypes[i] = i;

			for (int j = 0; j < STARTING_CAPACITY; j++) {
				animals[i][j] = NULL;
			}
		}

		//////////////////////////////////////////////////////////////////
		// Get starting info.
		//////////////////////////////////////////////////////////////////

		// Print introductory instructions.
		cout << "\nStarting Money:     $100,000\n\n"
			<< "To begin the game, please buy 1 or 2 of each animal.\n"
			<< "(Note: The cost of each animal will be subtracted from the starting money.)\n\n";

		// Print tiger info.
		typeToBuy = TIGER;
		printAnimalInfo(typeToBuy, BASE_FOOD_COST);

		// Get number of tigers.
		cout << "\nHow many Tigers would you like to buy?\n\n";
		startingAnimals = getValidIntInRange(MIN_STARTING_ANIMALS, MAX_STARTING_ANIMALS);

		// Buy the tigers.
		for (int i = startingAnimals; i > 0; i--) {

			createAnimal(typeToBuy, &animalPtr, BASE_FOOD_COST);
			addAnimal(typeToBuy, &animalPtr);
			money -= animalPtr->getCost();
		}

		// Print penguin info.
		typeToBuy = PENGUIN;
		printAnimalInfo(typeToBuy, BASE_FOOD_COST);

		// Get number of penguins.
		cout << "\nHow many Penguins would you like to buy?\n\n";
		startingAnimals = getValidIntInRange(MIN_STARTING_ANIMALS, MAX_STARTING_ANIMALS);

		// Buy the penguins.
		for (int i = startingAnimals; i > 0; i--) {

			createAnimal(typeToBuy, &animalPtr, BASE_FOOD_COST);
			addAnimal(typeToBuy, &animalPtr);
			money -= animalPtr->getCost();
		}

		// Print turtle info.
		typeToBuy = TURTLE;
		printAnimalInfo(typeToBuy, BASE_FOOD_COST);

		// Get number of turtles.
		cout << "\nHow many Turtles would you like to buy?\n\n";
		startingAnimals = getValidIntInRange(MIN_STARTING_ANIMALS, MAX_STARTING_ANIMALS);

		// Buy the turtles.
		for (int i = startingAnimals; i > 0; i--) {

			createAnimal(typeToBuy, &animalPtr, BASE_FOOD_COST);
			addAnimal(typeToBuy, &animalPtr);
			money -= animalPtr->getCost();
		}

		////////////////////////////////////////////////////////////////////
		// Start game.
		////////////////////////////////////////////////////////////////////

		do {

			////////////////////////////////////////////////////////////////////
			// Beginning of the day.
			////////////////////////////////////////////////////////////////////

			// Increment the day.
			days++;

			// Increase the age of each animal
			ageAllAnimals();

			// Initialize/reset daily feed cost, payoff, and bonus.
			feedingCost = 0;
			payoff = 0;
			bonus = 0;

			// Print the info for the start of the day.
			printDayStart();

			// Prompt to continue.
			cout << "\nPress enter to continue...\n";
			cin.ignore();

			////////////////////////////////////////////////////////////////////
			// Pay Costs.
			////////////////////////////////////////////////////////////////////

			// Pay the daily feeding cost.
			payFeedingCost();
			printCosts();

			// Prompt to continue.
			cout << "\nPress enter to continue...\n";
			cin.ignore();

			////////////////////////////////////////////////////////////////////
			// Event occurs.
			////////////////////////////////////////////////////////////////////

			// Pick a random event number.
			eventNum = rand() % NUM_OF_EVENTS;
			// Get the event name associated with the number.
			eventName = static_cast<RandomEvent>(eventNum);

			switch (eventName) {
			case SICKNESS:
				sicknessEvent();
				break;
			case ATTENDBOOM:
				attendBoomEvent(BONUS_MIN, BONUS_MAX);
				break;
			case BIRTH:
				animalBornEvent(ADULT_AGE, BASE_FOOD_COST);
				break;
			case NOTHING:
				// Nothing happens.
				break;
			}

			// Print the random event.
			printRandomEvent();

			// Prompt to continue.
			cout << "\nPress enter to continue...\n";
			cin.ignore();

			////////////////////////////////////////////////////////////////////
			// Get profits.
			////////////////////////////////////////////////////////////////////

			// Calculate and add the daily profits.
			calcProfits();
			printProfits();

			// Prompt to continue.
			cout << "\nPress enter to continue...\n";
			cin.ignore();

			////////////////////////////////////////////////////////////////////
			// Buy new animal.
			////////////////////////////////////////////////////////////////////

			// Ask the user if they would like to buy a new animal.
			cout << "\nDo you want to buy a new animal (y/n)?\n\n";
			choice = getValidChar('y', 'n');

			// If the user selected yes, attempt to buy an animal.
			if (choice == 'y') {

				// Initialize/reset flags.
				animalAdded = false;
				cancel = false;
				do {

					// Prompt user to enter the type of animal to buy.
					cout << "\nEnter the type of animal you would like to buy:\n";
					animalSelectMenu();

					// Get user choice.
					choice = getMenuChoice('4');

					// Get the type and loop again or cancel.
					switch (choice) {
					case '1':
						typeToBuy = TIGER;
						break;
					case '2':
						typeToBuy = PENGUIN;
						break;
					case '3':
						typeToBuy = TURTLE;
						break;
					case '4':
						// If 4 was selected the user decided to cancel buying.
						cancel = true;
						break;
					}

					// If the user did not select to cancel (option 4).
					if (cancel == false) {

						// Print the info of the selected animal and get confirmation
						// the user would like to buy it.
						printAnimalInfo(typeToBuy, BASE_FOOD_COST);
						cout << "\nAre you sure you want to buy this animal (y/n)?\n\n";
						choice = getValidChar('y', 'n');

						// If the user is sure they want to buy it then continue.
						// If they select no here then rest will be skipped, and
						// the loop will restart and prompt the user for a different type.
						if (choice == 'y') {

							// Create an animal object to get the cost info.
							createAnimal(typeToBuy, &animalPtr, BASE_FOOD_COST, ADULT_AGE);

							// Check if the cost of the animal they are attempting to buy exceeds
							// the amount of money they have.
							if (animalPtr->getCost() > money) {

								// If it does, prompt for a different type or offer to cancel buying.
								cout << "\nNot enough money. Do you want to buy a different type "
									<< "of animal (y/n)?\n\n";
								choice = getValidChar('y', 'n');

								// If they do not want to select a different type of animal,
								// then cancel buying.
								if (choice == 'n') {

									// Deallocate the memory before canceling.
									delete animalPtr;
									animalPtr = NULL;

									cancel = true;

								}
								// Otherwise if they do want to select a different type.
								else if (choice == 'y') {

									// Deallocate the memory and loop again.
									delete animalPtr;
									animalPtr = NULL;
								}
							}
							// Otherwise, if they have enough money then add the animal
							// and subtract the cost from the player's money.
							else {

								addAnimal(typeToBuy, &animalPtr);
								money -= animalPtr->getCost();
								animalAdded = true;
							}
						}
					}

				// If an animal was not added but the user also did not cancel,
				// then loop again.
				} while (animalAdded == false && cancel == false);

				// Print result message.
				if (animalAdded == true) {

					cout << "\nAnimal successfully purchased!\n";
				}
				else if (cancel == true) {

					cout << "\nCanceled buying animal.\n";
				}
			}

			////////////////////////////////////////////////////////////////////
			// End of the day.
			////////////////////////////////////////////////////////////////////

			// Print the info for the end of the day
			printDayEnd();

			// Prompt to continue.
			cout << "\nPress enter to continue...\n";
			cin.ignore();

			////////////////////////////////////////////////////////////////////
			// Determine next step.
			////////////////////////////////////////////////////////////////////

			// Check for game over.
			if (money < 0) {

				// If so, print game over message and set selection to
				// 2 to end the while loop.
				cout << "\nSorry, you are out of money!\n"
					<< "\nGAME OVER!\n" << endl;
				choice = '2';

				// Prompt to continue.
				cout << "\nPress enter to continue...\n";
				cin.ignore();
			}
			// Otherwise if not game over.
			else {

				// prompt to continue playing.
				midGameMenu();
				choice = getMenuChoice('2');
			}
		} while (choice != '2');

		////////////////////////////////////////////////////////////////////
		// Game finished.
		////////////////////////////////////////////////////////////////////

		// Deallocate memory.
		for (int type = 0; type < numOfTypes; type++) {

			// Delete each animal object.
			for (int animal = 0; animal < numOfAnimals[type]; animal++) {

				delete animals[type][animal];
			}

			// Delete the array of each animal type.
			delete[] animals[type];
		}
		// Delete the rest of the arrays.
		delete[] animals;
		delete[] capacities;
		delete[] numOfAnimals;
		delete[] shuffledTypes;

		// Display main menu.
		playAgainMenu();
		// Get user choice. If '2' (quit) is selected loop will be exited
		// and program will end.
		choice = getMenuChoice('2');
	}

	////////////////////////////////////////////////////////////////////
	// Program ending.
	////////////////////////////////////////////////////////////////////

	displayOutro();
}

/*
* Function that iterates through all the existing animal objects and 
* increments their age using their built in incrementAge() function.
*/
void Zoo::ageAllAnimals() {

	// Loop through each animal type.
	for (int type = 0; type < numOfTypes; type++) {

		// Loop through each animal of the given type if there are any
		// until an empty space is encountered.
		for (int animal = 0; animal < numOfAnimals[type]; animal++) {

			// Increment the age of the animal.
			animals[type][animal]->incrementAge();
		}
	}
}

/*
* Function to calculate the total food cost of the day according to the
* food cost of each animal type multiplied by the number of each animal type.
*/
void Zoo::payFeedingCost() {

	int costOfType = 0;		// To hold the cost for each animal type.

	// Add up the feed cost for each existing animal.
	for (int type = TIGER; type < numOfTypes; type++) {

		// If there exists at least one animal of the current type.
		if (animals[type][0] != NULL && numOfAnimals[type] != 0) {

			// Get the food cost of the current animal type.
			costOfType = animals[type][0]->getFoodCost();

			// Multiply it by the number of animals of the type.
			costOfType *= numOfAnimals[type];

			// Add the cost to the total daily feeding cost.
			feedingCost += costOfType;
		}
	}

	// Subtract the total cost from the players money.
	money -= feedingCost;
}

/*
* Function to shuffle the array of type indexes. During certain random events,
* after the array is shuffled, it is iterated through until a criteria is met,
* and if the criteria is not met then the next index is selected, and so on.
* The purpose of this is to randomize the selection of animal types while also
* keeping track of which types have already been selected in the case the criteria 
* is not met.
*/
void Zoo::shuffleTypeIndexes() {

	int temp;		// To hold a temporary index for swapping.
	int index2;		// To hold an second index for swapping.

	for (int index1 = numOfTypes - 1; index1 > 0; index1--) {

		// Get a random index.
		index2 = rand() % index1;

		// Swap the current index with the random index.
		temp = shuffledTypes[index1];
		shuffledTypes[index1] = shuffledTypes[index2];
		shuffledTypes[index2] = temp;
	}
}

/*
* The function that is called if the random event is that a sickness occurs
* to an animal in the zoo. First a random type is selected, and if there exists
* an animal(s) of the type then a random animal of the type is selected
* and removed from the dynamic array. If no animal exists of a selected type then
* another random type is selected, and so on. If there are no animals in the zoo
* of any type, the function will recover and change the event type to the nothing
* happens event.
*/
void Zoo::sicknessEvent() {

	bool animalRemoved = false;		// To indicate if an animal was successfully removed.
	int type = 0;				    // To hold the current index of animal types.

	// Shuffle the array of type indexes.
	shuffleTypeIndexes();
	
	// Step through the shuffled array of type indexes.
	while (animalRemoved == false && type < numOfTypes) {

		randomType = static_cast<AnimalType>(shuffledTypes[type]);

		// If there exists at least one animal of the current type.
		if (animals[randomType][0] != NULL && numOfAnimals[randomType] != 0) {

			// Get a random animal of the type.
			int animal = rand() % numOfAnimals[randomType];

			// Remove the animal from the array.
			delete animals[randomType][animal];
			animals[randomType][animal] = NULL;

			// Shift all the following elements down.
			for (int j = animal; j < numOfAnimals[randomType] - 1; j++) {
				animals[randomType][j] = animals[randomType][j + 1];
			}

			// Set the last element to null and decrement the number of animals of the type.
			animals[randomType][numOfAnimals[randomType] - 1] = NULL;
			numOfAnimals[randomType]--;

			// Indicate an animal has been successfully removed.
			animalRemoved = true;
		}

		type++;
	}

	// If an animal was not removed, that means that there exist no animals to be removed.
	// Recover and change to the nothing happened event.
	if (animalRemoved == false) {
		
		eventName = NOTHING;	
	}
}

/*
* The function that is called if the random event is that a boom in zoo attendance
* occurs. First the function checks if there exist any tigers in the zoo, and if not
* the function recovers and changes the random event to the nothing happens event.
* However, if there are any tigers then a random bonus is generated between the 
* min and max bonus and multiplied by the number of tigers in the zoo.
*/
void Zoo::attendBoomEvent(int minBonus, int maxBonus) {

	// Check if there are any tigers in the zoo.
	if (animals[TIGER][0] != NULL && numOfAnimals[TIGER] != 0) {

		// Get the random bonus amount.
		bonus = minBonus + (rand() % (maxBonus - minBonus + 1));

		// Multiply it by the number of tigers in the zoo.
		bonus *= numOfAnimals[TIGER];
	}
	// If there are no tigers in the zoo, recover and change to the nothing happened event.
	else {

		eventName = NOTHING;
	}
}

/*
* The function that occurs if the random event is that a baby animal is born.
* Picks an animal type at random and checks to see if any animals of the type
* exist. If not than another random type is selected. If there do exist animals
* of the selected type, the function checks to see if any animals of the type are
* of adult age, and if so adds baby animals to the zoo depending on the number of
* babies specific to the type of animal. If no animals are able to give birth then
* the function recovers and changes the random event to the nothing happens event.
*/
void Zoo::animalBornEvent(int adultAge, int baseFoodCost) {

	bool animalsBorn = false;	// To indicate if any baby animals were born.
	Animal* animalPtr = NULL;	// To hold a pointer to an animal object.
	int type = 0;				// To hold the current index of animal types.
	int animal = 0;				// To hold the current index of animal of the given type.

	// Shuffle the array of type indexes.
	shuffleTypeIndexes();

	// Step through the shuffled array of type indexes.
	while (animalsBorn == false && type < numOfTypes) {

		randomType = static_cast<AnimalType>(shuffledTypes[type]);

		// If there exists at least one animal of the current type.
		if (animals[randomType][0] != NULL && numOfAnimals[randomType] != 0) {

			// Check if any are adults.
			while (animalsBorn == false && animal < numOfAnimals[randomType]) {

				// If an adult was found.
				if (animals[randomType][animal]->getAge() >= adultAge) {

					// Get how many babies the animal type creates.
					int numOfBabies = animals[randomType][0]->getNumOfBabies();
					for (int i = 0; i < numOfBabies; i++) {

						// Create and add animals of the given type (age 1).
						createAnimal(randomType, &animalPtr, baseFoodCost);
						addAnimal(randomType, &animalPtr);
					}

					// Indicate animals successfully born.
					animalsBorn = true;
				}

				animal++;
			}
		}

		type++;
	}

	// If a baby animal was not born, this means there are no adults of any 
	// of the types of animals, so recover and change the event to the nothing
	// happens event.
	if (animalsBorn == false) {

		eventName = NOTHING;
	}
}

/*
* Function to calculate the profits earned each day, by iterating through each
* animal type and if there exist any animals of the type, multiplying the number of
* the animals by their payoff amount specific to their animal type, and adding it
* to the total payoff of the day. Then the total payoff, as well as any bonus 
* accrued during an attendance boom event, are added to the player's money.
*/
void Zoo::calcProfits() {

	int payoffOfType = 0;		// To hold the daily profit of each animal type.

	// Add up the payoff for each existing animal.
	for (int type = TIGER; type < numOfTypes; type++) {

		// If there exists at least one animal of the current type.
		if (animals[type][0] != NULL && numOfAnimals[type] != 0) {

			// Get the daily payoff of the given animal type.
			payoffOfType = animals[type][0]->getPayoff();

			// Multiply it by the number of animals of the given type.
			payoffOfType *= numOfAnimals[type];

			// Add it to the total daily payoff.
			payoff += payoffOfType;
		}
	}

	// Add the total payoff, plus the bonus if there is one, to the players money.
	money += payoff;
	money += bonus;
}

/*
* Function to create an animal object based on the desired type of the animal.
* The age of the animal is an optional argument and if not used then the age will
* default to 1 for a baby animal. Otherwise the adult age constant, 3, is usually
* passed instead to create an adult animal.
*/
void Zoo::createAnimal(AnimalType type, Animal** animalPtr, int baseFoodCost, int age)
{
	switch (type) {
	case TIGER:
		*animalPtr = new Tiger(baseFoodCost, age);
		break;
	case PENGUIN:
		*animalPtr = new Penguin(baseFoodCost, age);
		break;
	case TURTLE:
		*animalPtr = new Turtle(baseFoodCost, age);
		break;
	}
}

/*
* Function to add an animal pointer to the dynamic array specified by the type
* argument. If the animal is not able to be added then the array is full, so the
* function will first double the capacity of the array and then add the animal to
* the first spot in the second half of the array.
*/
void Zoo::addAnimal(AnimalType type, Animal** animalPtr)
{
	bool animalAdded = false;		// To detect if an animal was added successfully.
	int animal = 0;

	// Check if the array is full.
	while (animalAdded == false && animal < capacities[type]) {

		// If an empty spot is encountered, add the animal to it and stop looping.
		if (animals[type][animal] == NULL) {

			animals[type][animal] = *animalPtr;
			animalAdded = true;
		}

		animal++;
	}

	// If the animal was not added, then the array was full.
	if (animalAdded == false) {

		// Double the array capacity first.
		int newCapacity = capacities[type] * 2;

		// Create a new array the size of the new capacity.
		Animal** tempArray = new Animal*[newCapacity];
		for (int i = 0; i < capacities[type]; i++) {

			// Copy contents over to new array.
			tempArray[i] = animals[type][i];
		}
		// Delete the previous array.
		delete[] animals[type];

		// Initialize remaining contents of new array.
		for (int i = capacities[type]; i < newCapacity; i++) {
			tempArray[i] = NULL;
		}
		// Assign previous array to new array.
		animals[type] = tempArray;

		// Add the animal to the first new slot in the array.
		animals[type][capacities[type]] = *animalPtr;
		animalAdded = true;

		// Update the capacity.
		capacities[type] = newCapacity;
	}

	// Keep track of the number of the animal type.
	numOfAnimals[type]++;
}

/*
* Function to print the information of a given animal type to the screen
* for user convenience. Must take the base food cost as a parameter in order to
* create a temporary animal object. This is get the information about the animal
* type stored as data member variables of the class, making sure to deallocate the
* memory before ending the function.
*/
void Zoo::printAnimalInfo(AnimalType type, int baseFoodCost) {

	Animal* tempAnimal = NULL;		// To hold the temp animal object for getting info.
	string typeStr = "";			// To hold a string indicating the type of animal.

	// Create the temp animal object based on the animal type and get string
	// also based on the animal type for printing.
	switch (type) {
	case TIGER:
		tempAnimal = new Tiger(baseFoodCost);
		typeStr = "Tiger Info";
		break;
	case PENGUIN:
		tempAnimal = new Penguin(baseFoodCost);
		typeStr = "Penguin Info";
		break;
	case TURTLE:
		tempAnimal = new Turtle(baseFoodCost);
		typeStr = "Turtle Info";
		break;
	}

	// Print the top border.
	cout << '\n';
	for (int i = 0; i < 32; i++) {
		cout << "-";
	}
	cout << endl;

	// Print an empty row.
	cout << left << setw(31) << "|" << "|" << endl;

	// Print the animal type name row.
	cout << setw(10) << "|" << setw(21) << typeStr << "|" << endl;

	// Print an empty row.
	cout << left << setw(31) << "|" << "|" << endl;

	// Print the cost row.
	cout << setw(4) << "|"
		<< setw(18) << "Cost:"
		<< "$"
		<< setw(8) << tempAnimal->getCost() << "|" << endl;

	// Print the number of babies row.
	cout << setw(4) << "|"
		<< setw(19) << "Number of Babies:"
		<< setw(8) << tempAnimal->getNumOfBabies() << "|" << endl;

	// Print the food cost row.
	cout << setw(4) << "|"
		<< setw(18) << "Food Cost:"
		<< "$"
		<< setw(8) << tempAnimal->getFoodCost() << "|" << endl;

	// Print the payoff row.
	cout << setw(4) << "|"
		<< setw(18) << "Payoff:"
		<< "$"
		<< setw(8) << tempAnimal->getPayoff() << "|" << endl;

	// Print an empty row.
	cout << left << setw(31) << "|" << "|" << endl;

	// Print the bottom border.
	for (int i = 0; i < 32; i++) {
		cout << "-";
	}
	cout << endl;

	// Deallocate the memory for the temp animal.
	delete tempAnimal;
	tempAnimal = NULL;
}

/*
* Function to print the player's money and the amount of each animal
* at the beginning of the day.
*/
void Zoo::printDayStart() {

	// Print the top border.
	cout << '\n';
	for (int i = 0; i < 37; i++) {
		cout << "-";
	}
	cout << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print day title row.
	cout << setw(9) << "|"
		<< setw(17) << "Beginning of Day "
		<< setw(10) << days << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the number of tigers row.
	cout << setw(7) << "|"
		<< setw(17) << "# of Tigers:"
		<< setw(12) << numOfAnimals[TIGER] << "|" << endl;

	// Print the number of penguins row.
	cout << setw(5) << "|"
		<< setw(19) << "# of Penguins:"
		<< setw(12) << numOfAnimals[PENGUIN] << "|" << endl;

	// Print the number of turtles row.
	cout << setw(6) << "|"
		<< setw(18) << "# of Turtles:"
		<< setw(12) << numOfAnimals[TURTLE] << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the starting money row.
	cout << setw(5) << "|"
		<< setw(19) << "Starting Money:"
		<< "$"
		<< setw(11) << money << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the bottom border.
	for (int i = 0; i < 37; i++) {
		cout << "-";
	}
	cout << endl;
}

/*
* Function to print the daily costs.
*/
void Zoo::printCosts() {

	// Print the top border.
	cout << '\n';
	for (int i = 0; i < 37; i++) {
		cout << "-";
	}
	cout << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print costs title row.
	cout << setw(12) << "|"
		<< setw(24) << "Today's Costs" << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the feed cost row.
	cout << setw(9) << "|"
		<< setw(15) << "Feed Cost:"
		<< "$"
		<< setw(11) << feedingCost << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the money row.
	cout << setw(5) << "|"
		<< setw(19) << "Updated Money:"
		<< "$"
		<< setw(11) << money << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the bottom border.
	for (int i = 0; i < 37; i++) {
		cout << "-";
	}
	cout << endl;
}

/*
* Function to print a message for whatever random event occured.
*/
void Zoo::printRandomEvent() {

	string eventMsgType = "";
	string eventMsg = "";

	// Get the name of the animal type the event happened to.
	switch (randomType) {
	case TIGER:
		eventMsgType = "tiger";
		break;
	case PENGUIN:
		eventMsgType = "penguin";
		break;
	case TURTLE:
		eventMsgType = "turtle";
	}

	// Get the message for the event.
	switch (eventName) {
	case SICKNESS:
		eventMsg = "A " + eventMsgType + " passed away today...";
		break;
	case ATTENDBOOM:
		eventMsg = "A boom in attendance occured!";
		break;
	case BIRTH:
		eventMsg = " A " + eventMsgType + " gave birth today!";
		break;
	case NOTHING:
		eventMsg = "  Nothing happened today.";
		break;
	}

	// Print the top border.
	cout << '\n';
	for (int i = 0; i < 37; i++) {
		cout << "-";
	}
	cout << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the random event title row.
	cout << setw(12) << "|"
		<< setw(24) << "Random Event" << "|" << endl;

	// Print the random event message row.
	cout << setw(4) << "|"
		<< setw(32) << eventMsg << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the bottom border.
	for (int i = 0; i < 37; i++) {
		cout << "-";
	}
	cout << endl;
}

/*
* Function to print the daily profits.
*/
void Zoo::printProfits() {

	// Print the top border.
	cout << '\n';
	for (int i = 0; i < 37; i++) {
		cout << "-";
	}
	cout << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print profits title row.
	cout << setw(11) << "|"
		<< setw(25) << "Today's Profits" << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the payoff row.
	cout << setw(4) << "|"
		<< setw(20) << "Today's Payoff:"
		<< "$"
		<< setw(11) << payoff << "|" << endl;

	// Print the bonus row.
	cout << setw(7) << "|"
		<< setw(17) << "Event Bonus:"
		<< "$"
		<< setw(11) << bonus << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the money row.
	cout << setw(5) << "|"
		<< setw(19) << "Updated Money:"
		<< "$"
		<< setw(11) << money << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the bottom border.
	for (int i = 0; i < 37; i++) {
		cout << "-";
	}
	cout << endl;
}

/*
* Function to print the results at the end of the day including
* the number of each animal type and the player's final money amount.
*/
void Zoo::printDayEnd() {

	// Print the top border.
	cout << '\n';
	for (int i = 0; i < 37; i++) {
		cout << "-";
	}
	cout << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print day title row.
	cout << setw(12) << "|"
		<< setw(11) << "End of Day "
		<< setw(13) << days << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the number of tigers row.
	cout << setw(7) << "|"
		<< setw(17) << "# of Tigers:"
		<< setw(12) << numOfAnimals[TIGER] << "|" << endl;

	// Print the number of penguins row.
	cout << setw(5) << "|"
		<< setw(19) << "# of Penguins:"
		<< setw(12) << numOfAnimals[PENGUIN] << "|" << endl;

	// Print the number of turtles row.
	cout << setw(6) << "|"
		<< setw(18) << "# of Turtles:"
		<< setw(12) << numOfAnimals[TURTLE] << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the ending money row.
	cout << setw(6) << "|"
		<< setw(18) << "Ending Money:"
		<< "$"
		<< setw(11) << money << "|" << endl;

	// Print an empty row.
	cout << left << setw(36) << "|" << "|" << endl;

	// Print the bottom border.
	for (int i = 0; i < 37; i++) {
		cout << "-";
	}
	cout << endl;
}