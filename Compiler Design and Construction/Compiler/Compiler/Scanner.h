/*******************************************************
Name: Scanner.h
Author: Christopher McDaniel
Date Started: 11 February 2020
Date Completed: 23 April 2020
Class: COSC 4316
Version: 1.1
Copyright: 2020
Description: This is a header file that creates the
classes that will be utilized by the Scanner body
file to 'scan' the given program and gather it's
information to generate the token list that will be
used by the program.

	 DISCLAIMER:
THIS PORTION "Scanner.h" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "LL.h", "Parser.h", and "Scanner.cpp".
*******************************************************/

#ifndef SCANNER_H
#define SCANNER_H

/*Include Program header file*/
#include "LL.h"

/*Include System header files*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cctype>

using namespace std;

/*Global string variable definitions*/
const string CLASS = "$CLASS";
const string VAR = "<$var>";
const string CONST = "$CONST";
const string PROCEDURE = "$PROCEDURE";
const string WHILE = "$WHILE";
const string DO = "$DO";
const string IF = "$IF";
const string THEN = "$THEN";
const string ELSE = "$ELSE";
const string CALL = "$CALL";
const string READ = "$READ";
const string WRITE = "$WRITE";
const string ODD = "$ODD";

const string PROGRAMNAME = "<ProgramName>";
const string PROCEDURENAME = "<PROCEDURE>";

/*Global operator definitions*/
const string VARNAME = "<var>";
const string LBRACK = "$LB";			// '{'
const string ASSIGN = "<assign>";		// '='
const string INTEGER = "<integer>";		// 1 ... infinite
const string COMMA = "<comma>";			// ','
const string SEMICOLON = "<semi>";		// ';'
const string RBRACK = "$RB";			// '}'
const string RELOP = "<relop>";			// '<', '<=', '>', '>=', '==', '!='
const string MOP = "<mop>";				// '*', '/'
const string ADDOP = "<addop>";			// '+', '-'
const string LPAREN = "$LP";			// '('
const string RPAREN = "$RP";			// ')'
const string END_OF_FILE = "EOF";		// '\0'
const string NOT = "<NOT>";				// '!'
const string TEMP = "<temp>";

const string PROC_LBRACK = "PROC_LBRACK";
const string PROC_RBRACK = "PROC_RBRACK";

const string CS = "CS"; //Code segment
const string DS = "DS"; //Data segment

/*Token array of reserved words*/
const Token reserved[] = {	{"CONST", CONST},
							{"IF", IF},
							{"VAR", VAR},
							{"CLASS", CLASS},
							{"THEN", THEN},
							{"ELSE", ELSE},
							{"WHILE", WHILE},
							{"DO", DO},
							{"CALL", CALL},
							{"ODD", ODD},
							{"PROCEDURE", PROCEDURE},
							{"READ", READ},
							{"WRITE", WRITE}
						};

/*
Class: Scanner
Parameters: (N/A)
Return: (N/A)
Description: Declares the Scanner functions
and variables that will be used when
the header file is called.
*/
class Scanner
{
public:

	/*LinkedList pointer*/
	LL* SymTable;	//Table for the symbol table.

	/*Function identifier*/
	Scanner(string SFileName);

	/*Token function identifier*/
	Token buildToken();

	/*Void function identifier*/
	void buildSTable();

private:

	/*Integer variables*/
	int rows, columns;
	int reservedKnt = 13;
	int** ScTable;	//Table for the Scanner.
	int** FPTable;	//Table for the first pass DFSA.

	/*Character variable*/
	char LChar = ' ';

	/*Filestream variables*/
	ifstream SFile;		//Source code input file.
	ifstream DTFile;	//Decision table files.
	ofstream TFile;		//Token list output file.
	ofstream STFile;	//Symbol table output file.

	/*Integer function identifiers.*/
	int isReserved(Token token);
	int charToInt(char ch);
	int tokenToInt(Token token);

	/*Character function identifier*/
	char nextChar();
};

#endif