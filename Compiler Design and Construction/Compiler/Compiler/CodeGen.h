/*******************************************************
Name: CodeGen.h
Author: Christopher McDaniel
Date Started: 11 February 2020
Date Completed: 23 April 2020
Class: COSC 4316
Version: 1.1
Copyright: 2020
Description: This is a header file that creates the
class that will be utilized by the Code Generation 
body file to generate the assembly code.

	 DISCLAIMER:
THIS PORTION "CodeGen.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Parser.h", "LL.h", "Quad.h" and
"CodeGen.cpp".
*******************************************************/

#ifndef CODEGEN_H
#define CODEGEN_H

/*Include Program header files*/
#include "Parser.h"
#include "LL.h"
#include "Quad.h"

/*Include System header files*/
#include <fstream>
#include <queue>
#include <iostream>
#include <list>

using namespace std;

/*
Class: CodeGen
Parameters: (N/A)
Return: (N/A)
Description: Declares the CodeGen functions
and variables that will be used when
the header file is called.
*/
class CodeGen
{
public:

	/*Function identifier*/
	CodeGen(list <Quad> q, LL* table);

	/*Void function identifier*/
	void genCode();

private:

	/*File stream variable*/
	ifstream partDS;	//Data Section file.
	ifstream partBS;	//Bss Section file.
	ifstream IOFile;	//IO Routines file.
	ofstream out_stream;	//Output file.

	/*List variable*/
	list <Quad> queue_Quad;

	/*Linked list pointer variable.*/
	LL* SymTable;

	/*Function identifiers*/
	void addDSandBS();
	void addIO();

	/*Integer function identifier*/
	int quadToInt(Quad qu);
};

#endif