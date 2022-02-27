/*******************************************************
Name: LL.h
Author: Christopher McDaniel
Date Started: 11 February 2020
Date Completed: 23 April 2020
Class: COSC 4316
Version: 1.1
Copyright: 2020
Description: This is a header file that creates the
classes that will be utilized by the Linked List body
file to create the symbol table used by the program.

	 DISCLAIMER:
THIS PORTION "LL.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Token.h", "CodeGen.h", "Scanner.h",
"Parser.h", and "LL.cpp".
*******************************************************/

#ifndef LL_H
#define LL_H

/*Include Program header file*/
#include "Token.h"

/*Include System header files*/
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

/*
Class: Node
Parameters: (N/A)
Return: (N/A)
Description: Declares the Node functions
and variables that will be used when
the header file is called.
*/
class Node
{
public:

	/*Pointer variables*/
	Token token;
	Node* next;

	/*
	Constructor: Node
	Parameters: (Token toke, Node* n)
	Description: Gives token the value
	of 'toke' and next the value of 'n'.
	*/
	Node(Token toke, Node* n)
	{
		token = toke;
		next = n;
	}
};

/*
Class: LL
Parameters: (N/A)
Return: (N/A)
Description: Declares the Linked List
functions and variables that will be
used when the header file is called.
*/
class LL
{
public:

	/*Node pointer variables*/
	Node* head;
	Node* last;

	/*
	Constructor: LL
	Parameters: (string outStream)
	Description: Sets the initial values.
	*/
	LL(string outStream)
	{
		this->head = NULL;
		this->symStream = outStream;
	}

	/*Boolean function identifier*/
	bool inLL(string TString);

	/*Void function identifiers*/
	void add(Token newToken);
	void printLL();

	/*String function identifier*/
	string getClass(string TString);

private:

	/*String variable*/
	string symStream;

	/*Output filestream variable*/
	ofstream STFile;
};

#endif