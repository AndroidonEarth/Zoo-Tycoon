/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: menu.cpp, implementation file for the menu functions.
*********************************************************************/

#include "menu.hpp"
#include <iostream>
using std::cout;

/**
* Display the intro to the program. This is used when the program first
* starts to give an introduction and description of the program. 
*/
void displayIntro() {

	cout << "\n\nWELCOME!\n\n"
		<< "To Zoo Tycoon!\n";
}

/**
* Display the first menu prompt. This is used at the start of the program
* after the introduction in order to prompt the user for their first selection.
*/
void firstMenu() {

	cout << "\n\nMAIN MENU\n\n"
		<< "1) Play game\n"
		<< "2) Exit game\n\n";
}

/**
* Display animal select menu. This is used when the user is selecting an
* animal type in order to buy a new animal of that type.
*/
void animalSelectMenu() {

	cout << "\n1) Tiger\n"
		<< "2) Penguin\n"
		<< "3) Turtle\n"
		<< "4) CANCEL BUYING\n\n";
}

/**
* Display the second menu prompt. This is used after a day has passed
* in the game in order to give the user the option to continue or end 
* the game early.
*/
void midGameMenu() {

	cout << "\n\nSELECT AN OPTION\n\n"
		<< "1) Keep playing\n"
		<< "2) Exit game\n\n";
}

/**
* Display the third menu prompt. This is used after the game has ended to
* give the user the option to player the game again or end the program.
*/
void playAgainMenu() {

	cout << "\n\nMAIN MENU\n\n"
		<< "1) Play again\n"
		<< "2) Quit\n\n";
}

/**
* Display the outro to the program. This is used when the program is about to end
* to indicate so to the user.
*/
void displayOutro() {

	cout << "\nGame is exiting."
		<< "\n\nTHANK YOU FOR PLAYING!\n\n";
}