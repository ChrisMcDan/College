/*
============================================================================
Name: Homework 2.cpp
Author: Christopher R. McDaniel
Date: 30 September 2019
Class: COSC 2347
Version: 1.1
Copyright: 2019
Description: Program to take user input then print out a trapezoid using said input and calculating the area.
============================================================================
*/

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

//Define global variables
int height, b1, b2, TrapArea, b_in1, b_in2; //height, base 1, base 2, and Trapezoid Area
char letter; //Symbol

bool isOdd(int b_in)
{
	if ((b_in % 2 != 0)) //Checks if odd using remainder
	{
		return true; //Says it's even
	}
	else
	{
		return false; //Says it's odd
	}
}

/*
============================================================================
Function: check_b1()
Parameters: (N/A)
Return: (int) Base 1 value
Description: Checks to ensure value is within range and odd.
============================================================================
*/

////////////////////////Checks to see if b1 is odd and within proper range of 1-17////////////////////////
int check_b1()
{
	//Define local variables
	bool check_b1 = true; //Declare boolean variable with true value
	int Min = 1; //Define Min
	int Max = 17; //Define Max

	do
	{
		cout << "Enter an odd integer for Base1 of trapezoid (1 - 17): "; //Asking for user input
		cin >> b_in1; //User input

		if (((b_in1 >= Min) && (b_in1 <= Max)) && (isOdd(b_in1))) //Checks if within range
		{
			check_b1 = false;
		}
		else
		{
			check_b1 = true; //Base 1 is not within range.
			cout << "Ensure the integer is within the proper range (1-17) and odd.\n";
		}
	} while (check_b1 == true); //Checks to make sure it's within range and odd

	return b_in1; //return value
}

/*
============================================================================
Function: check_b2()
Parameters: (N/A)
Return: (int) Base 2 value
Description: Checks to ensure value is within range and odd.
============================================================================
*/

////////////////////////Checks to see if b2 is odd and within proper range of 3-19////////////////////////
int check_b2(int b2)
{
	//Define local variables
	bool check_b2 = true; //Declare boolean variable with true value
	int Min = 3; //Define Min
	int Max = 19; //Define Max

	do
	{
		cout << "Enter an odd integer for base2 > base1 of trapezoid (3 - 19): "; //Asking for user input
		cin >> b_in2; //User input

		if (((b_in2 >= Min) && (b_in2 <= Max))) //Checks range
		{
			if ((b_in1 < b_in2) && (isOdd(b_in2))) //Checks to make sure b2 value is greater than b1.
			{
				check_b2 = false;
			}
			else
			{
				check_b2 = true; //Base 1 is larger than Base 2
				cout << "Integer must be larger than Base 1, but still odd.\n";
			}
		}
		else
		{
			check_b2 = true; //Base 2 is not within range.
			cout << "Ensure the integer is within the proper range (3-19) and odd.\n";
		}
	} while (check_b2 == true); //Checks to make sure it's within range and odd

	return b_in2; //return value
}

/*
============================================================================
Function: (Void) Trapezoid
Parameters: (int) for Base 1, (int) Base 2, (int) height, (char) letter.
Return: (void)
Description: Draws Trapezoid using user input.
============================================================================
*/

////////////////////////Void function to print Trapezoid////////////////////////
void Trapezoid(int b1, int b2, int height, char letter)
{
	cout << "Please enter a printable character to draw Trapezoid: "; //Asking for user input
	cin >> letter; //User input

	for (int row = 0; row < height; ++row) //Start at 0 and increase incrementally until height is reached.
	{
		for (int column = height - row; column > 0; --column) //Write spaces
		{
			cout << " "; //Output spaces
		}
		for (int column = 0; column < (b1 + 2 * row); ++column) //Write character
		{
			cout << letter; //Output letters
		}

		cout << "\n";
	}
}

////////////////////////Main function////////////////////////
int main()
{
	//Displays my information
	cout << "\n\n";
	cout << " *************************************************************\n"; //Border
	cout << "|      Department: COSC 2347 - Special Topics/Programming     |\n"; //Prints Department and course number
	cout << "|                  Name: Christopher McDaniel                 |\n"; //Prints my name
	cout << "|         SamID: 000652957     E-mail: crm089@shsu.edu        |\n"; //Prints my SamID and my E-mail address
	cout << " *************************************************************\n"; //Border
	cout << "\n\n";

	cout << "Print a trapezoid and calculate its area."; //What program does
	cout << "\n\n";

	b_in1 = check_b1(); //Checks to see if b1 is odd

	b_in2 = check_b2(b_in2); //Checks to see if b2 is odd

	height = ((b_in2 - b_in1) / 2) + 1; //Calculate the height

	TrapArea = (height * (b_in1 + b_in2) / 2); //Formula for area of Trapezoid

	Trapezoid(b_in1, b_in2, height, letter); //Sends values to Trapezoid function to print Trapezoid

	cout << "\n";
	cout << "The area of the trapezoid = " << TrapArea << " (units squared)"; //Print result

	return 0;
}