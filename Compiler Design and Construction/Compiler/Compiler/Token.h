/*******************************************************
Name: Token.h
Author: Christopher McDaniel
Date Started: 11 February 2020
Date Completed: 23 April 2020
Class: COSC 4316
Version: 1.1
Copyright: 2020
Description: This is a header file that creates the
structure that will be utilized to generate the token
list, linked list, and the Assembly code that will be
generated.

	 DISCLAIMER:
THIS PORTION "Token.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "LL.h".
*******************************************************/

#ifndef TOKEN_H
#define TOKEN_H

/*Include System header file*/
#include <string>

using namespace std;

/*
Struct: Token
Parameters: (N/A)
Return: (N/A)
Description: Declares the Token
variables that will be used when
the header file is called.
*/
struct Token
{
	/*String variables*/
	string TString;
	string TClass;
	string value;
	string segment;


	/*Integer variable*/
	int address;
};

#endif