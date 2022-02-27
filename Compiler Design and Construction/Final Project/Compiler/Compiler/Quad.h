/*******************************************************
Name: Quad.h
Author: Christopher McDaniel
Date Started: 11 February 2020
Date Completed: 23 April 2020
Class: COSC 4316
Version: 1.1
Copyright: 2020
Description: This is a header file that creates the
structure that will be utilized in the creation of
the Quad.txt file, generation of the Assembly code,
and optimizing the completed code.

	 DISCLAIMER:
THIS PORTION "Quad.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "CodeGen.h", and "Parser.h".
*******************************************************/

#ifndef QUAD_H
#define QUAD_H

/*Include System header files*/
#include <list>
#include <string>
#include <iostream>

using namespace std;

/*
Struct: Quad
Parameters: (N/A)
Return: (N/A)
Description: Declares the Quad function
and variables that will be used when
the header file is called.
*/
struct Quad
{
	string operation;
	string operand_1;
	string operand_2;
	string operand_3;

	string Quad_print()
	{
		string str = operation + ", " + operand_1 + ", " + operand_2 + ", " + operand_3 + "\n";
		return str;
	}
};

/*
Class: optimizeQuads
Parameters: (N/A)
Return: (N/A)
Description: Declares the optimizeQuads
functions and variables that will be
used when the header file is called.
*/
class optimizeQuads
{
public:

	/*Function identifier*/
	optimizeQuads(list<Quad> q);

	/*Function identifier*/
	list<Quad> optimAssign();

private:

	/*List variable*/
	list <Quad> quads;
};

#endif