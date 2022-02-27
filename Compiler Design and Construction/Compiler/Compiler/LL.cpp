/*******************************************************
Name: LL.cpp
Author: Christopher McDaniel
Date Started: 11 February 2020
Date Completed: 23 April 2020
Class: COSC 4316
Version: 1.1
Copyright: 2020
Description: This is a body file that generates and controls
the linked list that is used for the code generation.

	 DISCLAIMER:
THIS PORTION "LL.cpp" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "LL.h".
*******************************************************/

/*Include Program header files*/
#include "LL.h"

/* 
* DATA STRUCTURES HYMNAL PAGE 49.
*/

/*
Function: inLL
Parameters: (string TString)
Description: Checks to make sure
the node is in the Linked List.
*/
bool LL::inLL(string TString)
{
	/*Node pointer variable assignment*/
	Node* temp = this->head;

	while (temp)
	{
		if (temp->token.TString == TString)
		{
			return true;
		}

		temp = temp->next;
	}

	return false;
}

/*
Function: add
Parameters: (Token newToken)
Description: Adds nodes onto the
Linked List.
*/
void LL::add(Token newToken)
{
	/*Node pointer variable*/
	Node* temp = this->head;

	if (this->head == NULL)	//New first node or only node
	{
		this->head = new Node(newToken, NULL);	//Head is a new node.
		this->last = this->head;				//and the last node is the head.
	}
	else	//Interior node or new last node.
	{
		while (temp->next != NULL)	//While temp->next is not NULL.
		{
			temp = temp->next;
		}

		temp->next = new Node(newToken, NULL);	//Next is a new node.
		this->last = temp->next;				//and the last node is next.
	}
}

/*
Function: printLL
Parameters: (N/A)
Description: Prints the Symbol table
for the given source code.
*/
void LL::printLL()
{
	/*Node pointer variable assignment*/
	Node* temp = this->head;

	if (this->head == NULL)
	{
		return;
	}

	STFile.open(symStream);	//Open symbol table file.
	if (STFile.is_open())	//If symbol table file is open.
	{
		//Symbol Table output design.
		STFile << left << setw(30) << "TOKEN";		//Set field width to 30.
		STFile << left << setw(15) << "CLASS";		//Set field width to 15.
		STFile << right << setw(10) << "VALUE";		//Set field width to 10.
		STFile << right << setw(10) << "ADDRESS";	//Set field width to 10.
		STFile << right << setw(10) << "SEGMENT";	//Set field width to 10.
		STFile << endl;

		do
		{
			//Outputs token values into the Token List.
			STFile << left << setw(30) << temp->token.TString;		//Set field width to 30.
			STFile << left << setw(15) << temp->token.TClass;		//Set field width to 15.
			STFile << right << setw(6) << temp->token.value;		//Set field width to 6.
			STFile << right << setw(8) << temp->token.address;		//Set field width to 8.
			STFile << right << setw(11) << temp->token.segment;		//Set field width to 11.
			STFile << endl;
			temp = temp->next;
		} while (temp);
	}
	else
	{
		cout << "Error opening the output file" << symStream;
		cout << endl;
		exit(EXIT_FAILURE);
	}

	STFile.close();	//Close symbol table file.
}

/*
Function: getClass
Parameters: (string TString)
Description: Gets the token class
from the Linked List.
*/
string LL::getClass(string TString)
{
	/*Node pointer variable assignment*/
	Node* temp = this->head;

	while (temp)
	{
		if (temp->token.TString == TString)
		{
			return temp->token.TClass;
		}

		temp = temp->next;
	}
}