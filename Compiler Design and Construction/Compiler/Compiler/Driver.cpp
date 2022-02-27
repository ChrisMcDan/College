/*******************************************************
Name: Driver.cpp
Author: Christopher McDaniel
Date Started: 11 February 2020
Date Completed: 23 April 2020
Class: COSC 4316
Version: 1.1
Copyright: 2020
Description: This is the main driving body file that
gets the source code file and passes it to the
Parser body file.

	 DISCLAIMER:
THIS PORTION "Driver.cpp" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Parser.h".
*******************************************************/

/*Include Program header files*/
#include "Parser.h"

/*
Function: main
Parameters: (N/A)
Description: Asks the user for source
file input and passes it to the Parser.
*/
int main() {
	/*String variable*/
	string SFile;

	//Ask for user input.
	cout << "Enter the name of the input file: ";
	cin >> SFile;	//Get user input.

	Parser parser(SFile);	//Pass source code file to Parser.
	parser.sourceParse();	//Parse the source code file.
}