/*******************************************************
Name: Parser.h
Author: Christopher McDaniel
Date Started: 11 February 2020
Date Completed: 23 April 2020
Class: COSC 4316
Version: 1.1
Copyright: 2020
Description: This is a header file that creates the
class that will be utilized in the parsing of the user
provided source code. This also contains class for the
operation of a stack.

	 DISCLAIMER:
THIS PORTION "Parser.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Scanner.h", "CodeGen.h", "Quad.h",
"LL.h", "Parser.cpp", and "Driver.cpp".
*******************************************************/

#ifndef PARSER_H
#define PARSER_H

/*Include Program header files*/
#include "Scanner.h"
#include "CodeGen.h"
#include "Quad.h"
#include "LL.h"

/*Include System header files*/
#include <queue>
#include <stack>
#include <list>
#include <iostream>
#include <string>

using namespace std;

/*
Class: Stack
Parameters: (N/A)
Return: (N/A)
Description: Declares the Stack functions
and variables that will be used when
the header file is called.
*/
class Stack
{
	/*Function identifier*/
	Stack();

	/*Node pointer variable*/
	Node* top;

	/*Void function identifier*/
	void push(Token token);

	/*Token function identifiers*/
	Token pop();
	Token peek();
};

/*
Class: Parser
Parameters: (N/A)
Return: (N/A)
Description: Declares the Parser functions
and variables that will be used when
the header file is called.
*/
class Parser
{
public:

	/*Function identifier*/
	Parser(string SFileName);

	/*Void function identifier*/
	void sourceParse();

private:

	/*Integer variables*/
	int operatorKnt;
	int labelKnt = 1;
	int whileKnt = 1;
	int tempKnt = 1;

	/*Boolean variables*/
	bool errors = false;
	bool isQuad = false;

	/*Character variable*/
	char** PTable;

	/*String variables*/
	string label;
	string whileLabel;

	/*File stream variable*/
	ofstream QFile;
	ifstream PTFile;

	/*Scanner pointer variable*/
	Scanner* scanner;

	/*Stack variables*/
	stack <Token> t;
	stack <string> startWhile;
	stack <string> fixUp;
	stack <string> Stack_Brack;
	stack <string> Stack_Paren;

	/*List variables*/
	list <Quad> mainQ;
	list <Quad> procedureQ;

	/*Integer function identifier*/
	int classToInt(string str);

	/*Void function identifiers*/
	void isError(string oper, Quad& quad, queue <Token>& q);
	void Quad_add(Quad quad);

	/*Boolean function identifiers*/
	bool varCheck(list <Quad> quads, LL* table);
	bool assignCheck(list <Quad> quads, LL* table);

	/*String function identifier*/
	string intToClass(int num);

	/*Token function identifier*/
	Token errorRecov(Token current, int& topCol, int& choice);
	
	/*Used to determine syntax of variable statement*/
	int varState[4][3] =
	{
		1, -1, -1,
		-1, 2, 3,
		1, -1, -1,
		-1, -1, -1
	};

	/*Used to determine syntax of constant statement*/
	int constState[6][5] =
	{
		1, -1, -1, -1, -1,
		-1, 2, -1, -1, -1,
		-1, -1, 3, -1, -1,
		-1, -1, -1, 4, 5,
		1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1
	};
};

#endif
