/*
============================================================================
Name: Homework4.cpp
Author: Christopher R. McDaniel
Date: 25 November 2019
Class: COSC 2347
Version: 1.1
Copyright: 2019
Description: This is a program that will label and count the number of
objects in a given image. Each image consists of a number of pixels, 
and initially all pixels will have one of two labels, 0 and 1. 0 is
considered a background pixel while a 1 represents a pixel that is 
part of an object. The program will apply, over multiple iterations, the
same label to pixels that are connected to form objects, and then count 
the number of objects for a given image. 
============================================================================
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

using namespace std;

/*
============================================================================
Function: main
Parameters: (N/A)
Return: Program output
Description: Prints my information and results from the program being ran.
============================================================================
*/
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

	return;
}

/*
============================================================================
Function: user_file()
Parameters: (N/A)
Return: Program output
Description: Takes file from user input, checks to see if valid, and.
============================================================================
*/
int user_file()
{
	ifstream in_stream;
	ofstream out_stream;
	char image[10];

	cout << "Enter the filename of the file that has the image: "; //Ask for user input
	cin >> image; //User input

	in_stream.open(image); //Open file
	if (in_stream.fail()) //Checks if opening was successful
	{
		cout << "Error opening image file!" << endl;
		exit(1);
	}



	return;
}