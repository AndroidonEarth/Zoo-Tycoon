/*********************************************************************
** Program name: Zoo Tycoon
** Author: Andrew Swaim
** Date: February 4, 2018
** Description: inputValidation.hpp, specification file for the
		inputValidation functions.
*********************************************************************/

#ifndef INPUT_VALIDATION_HPP
#define INPUT_VALIDATION_HPP

#include <string>
using std::string;

char getMenuChoice(char maxChoice);
int getValidIntInRange(int min, int max);
char getValidChar(char opt1, char opt2); 
//char getFirstLetterUpper(string str);
//char getFirstLetterLower(string str);

#endif
