/*******************************************************
Name: Scanner.cpp
Author: Christopher McDaniel
Date Started: 11 February 2020
Date Completed: 23 April 2020
Class: COSC 4316
Version: 1.1
Copyright: 2020
Description: This is a body file that performs a 'Scan'
of the source code and passes the appropriate outputs
into .txt files.

	 DISCLAIMER:
THIS PORTION "Scanner.cpp" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Scanner.h".
*******************************************************/

/*Include Program header files*/
#include "Scanner.h"

/*
Constructor: Scanner
Parameters: (string SFileName)
Description: Open and closes the files that
will be used in the creation of the Scanner
and First pass arrays. It then populates
said arrays.
*/
Scanner::Scanner(string SFileName)
{
	/*Integer variables*/
	int i, j;

	//Get input file.

	SFile.open(SFileName.c_str(), fstream::in);	//Open and read the file.
	if (SFile.fail())	//Checks if opening was successful.
	{
		cout << "Error opening source code input file " << SFileName;
		cout << endl;
		exit(EXIT_FAILURE);	//End program.
	}

	TFile.open("Token List.txt");	//Open token list.
	if (TFile.fail())	//Checks if opening was successful.
	{
		cout << "Error opening Token List.txt!";
		cout << endl;
		exit(EXIT_FAILURE);	//End program
	}

	DTFile.open("InputFiles/ScannerDFSA.txt");	//Scanner decision table.
	if (DTFile.fail())	//Checks if opening was successful.
	{
		cout << "Error opening ScannerDFSA.txt!";
		cout << endl;
		exit(EXIT_FAILURE);	//End program
	}

	DTFile >> rows;
	DTFile >> columns;

	ScTable = new int* [rows];	//Make scanner table a 2D array.
	for (i = 0; i < rows; i++)
	{
		ScTable[i] = new int[columns];

		for (j = 0; j < columns; j++)	//Populate the table.
		{
			DTFile >> ScTable[i][j];
		}
	}
	DTFile.close();	//Close scanner decision table file.

	DTFile.open("InputFiles/FirstPassDFSA.txt");	//First pass decision table.
	if (DTFile.fail())	//Checks if opening was successful.
	{
		cout << "Error opening FirstPassDFSA.txt!";
		cout << endl;
		exit(EXIT_FAILURE);	//End program
	}

	DTFile >> rows;
	DTFile >> columns;

	FPTable = new int* [rows];	//Make first pass table a 2D array.
	for (i = 0; i < rows; i++)
	{
		FPTable[i] = new int[columns];

		for (j = 0; j < columns; j++)	//Populate the table.
		{
			DTFile >> FPTable[i][j];
		}
	}
	DTFile.close();	//Close scanner decision table file.
}

/*
Function: buildToken
Parameters: (N/A)
Description: Uses the scanner DFSA to build
tokens one character at a time. Returns EOF
token when finished.
*/
Token Scanner::buildToken()
{
	if (SFile.tellg() == 0)	//If current position of the file pointer is at the start of the file, LChar is set to 0.
	{
		LChar = ' ';	//LChar = a whitespace.
	}

	/*Structure variable*/
	Token newToken;

	/*Initizalize new token string*/
	newToken.TString = "";

	/*Integer variables*/
	int state = 0;	//Set intial state to 0.
	int choice;

	/*Character variable*/
	char cha = LChar;

	/*Boolean variable*/
	bool finish = false;	//Set finish to a state of false.

	while (!finish)
	{
		switch (state)
		{
		default:
		{
			cout << "Error: Unkown state in the Scanner DFSA.";
			cout << endl;
			exit(EXIT_FAILURE);

			break;
		}
		case 0:		//Get next character
		{
			choice = charToInt(cha);
			state = ScTable[0][choice];

			if (state == 0)
			{
				cha = nextChar();
			}

			break;
		}
		case 1:		//ERROR
		{
			cout << "Error, there is an illegal character in the input! : " << cha;
			cout << endl;
			exit(EXIT_FAILURE);

			break;
		}
		case 2:		// Asterisk
		{
			newToken.TString += cha;

			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[2][choice];

			break;
		}
		case 3:		//Digit
		{
			if (isdigit(cha))
			{
				newToken.TString += cha;
			}

			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[3][choice];

			break;
		}
		case 4:		// <integer>,	final state
		{
			newToken.TClass = INTEGER;
			finish = true;

			break;
		}
		case 5:		//LetterDigit
		{
			if (isalnum(cha))	//Checks if 'character' is either a letter or number.
			{
				newToken.TString += cha;
			}

			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[5][choice];

			break;
		}
		case 6:		// <var>,	final state
		{
			int index = isReserved(newToken);	//Give index the value returned from the function isReserved.
			if (index != -1)
			{
				newToken = reserved[index];
			}
			else if (index == -1)
			{
				newToken.TClass = VARNAME;
			}

			finish = true;

			break;
		}
		case 7:		//Slash
		{
			newToken.TString += cha;

			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[7][choice];

			break;
		}
		case 8:		//Left comment (/*)
		{
			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[8][choice];

			break;
		}
		case 9:		//Right comment (*/)
		{
			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[9][choice];

			if (state == 0)
			{
				newToken.TString = "";
				cha = nextChar();
			}

			break;
		}
		case 10:	// '/' <mop>,	final state
		{
			newToken.TClass = MOP;
			finish = true;

			break;
		}
		case 11:	//Equal
		{
			newToken.TString += cha;

			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[11][choice];

			break;
		}
		case 12:	// '=' <assign>,	final state
		{
			newToken.TClass = ASSIGN;
			finish = true;

			break;
		}
		case 13:	// '==' <relop>,	final state
		{
			newToken.TClass = RELOP;
			newToken.TString += cha;
			cha = nextChar();
			finish = true;
			break;
		}
		case 14:	//Less than
		{
			newToken.TString += cha;
			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[14][choice];

			break;
		}
		case 15:	// '<' <relop>,	final state
		{
			newToken.TClass = RELOP;
			finish = true;

			break;
		}
		case 16:	// '<=' <relop>,	final state
		{
			newToken.TClass = RELOP;
			newToken.TString += cha;
			cha = nextChar();
			finish = true;

			break;
		}
		case 17:	// '{' $LB,	final state
		{
			newToken.TClass = LBRACK;
			newToken.TString += cha;
			cha = nextChar();
			finish = true;

			break;
		}
		case 18:	// '}' $RB,	final state
		{
			newToken.TClass = RBRACK;
			newToken.TString += cha;
			cha = nextChar();
			finish = true;

			break;
		}
		case 19:	//Add
		{
			newToken.TString += cha;
			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[19][choice];

			break;
		}
		case 20:	// '+' <addop>,	final state
		{
			newToken.TClass = ADDOP;
			finish = true;

			break;
		}
		case 21:	//Subtract
		{
			newToken.TString += cha;
			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[21][choice];

			break;
		}
		case 22:	// '-' <addop>,	final state
		{
			newToken.TClass = ADDOP;
			finish = true;

			break;
		}
		case 23:	// ',' <comma>,	final state
		{
			newToken.TClass = COMMA;
			newToken.TString += cha;
			cha = nextChar();
			finish = true;

			break;
		}
		case 24:	// ';' <semi>,	final state
		{
			newToken.TClass = SEMICOLON;
			newToken.TString += cha;
			cha = nextChar();
			finish = true;

			break;
		}
		case 25:	// '\0' EOF,	final state
		{
			newToken.TClass = END_OF_FILE;
			finish = true;

			break;
		}
		case 26:	// '*' <mop>,	final state
		{
			newToken.TClass = MOP;
			finish = true;

			break;
		}
		case 27:	//Greater than
		{
			newToken.TString += cha;
			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[27][choice];

			break;
		}
		case 28:	// '>' <relop>,	final state
		{
			newToken.TClass = RELOP;
			finish = true;

			break;
		}
		case 29:	// '>=' <relop>,	final state
		{
			newToken.TClass = RELOP;
			newToken.TString += cha;
			cha = nextChar();
			finish = true;

			break;
		}
		case 30:	// '(' $LP,	final state
		{
			newToken.TClass = LPAREN;
			newToken.TString += cha;
			cha = nextChar();
			finish = true;

			break;
		}
		case 31:	// ')' $RP,	final state
		{
			newToken.TClass = RPAREN;
			newToken.TString += cha;
			cha = nextChar();
			finish = true;

			break;
		}
		case 32:	//Exclamation mark
		{
			newToken.TString += cha;
			cha = nextChar();
			choice = charToInt(cha);
			state = ScTable[32][choice];

			break;
		}
		case 33:	// '!' <NOT>,	final state
		{
			newToken.TClass = NOT;
			finish = true;

			break;
		}
		case 34:	// '!=' <relop>,	final state
		{
			newToken.TClass = RELOP;
			newToken.TString += cha;
			cha = nextChar();
			choice = charToInt(cha);
			finish = true;

			break;
		}
		}
	}

	LChar = cha;

	return newToken;
}

/*
Function: buildSTable
Parameters: (N/A)
Description: Creates the Symbol Table
from the Linked List. Also, creates
the token list.
*/
void Scanner::buildSTable()
{
	/*Resets the file pointer to the start of the file.*/
	SFile.clear();	//Remove flags and allow for further operations to be attempted on file stream.
	SFile.seekg(0, SFile.beg);	//Sets the pointer to the beginning of the file stream.

	/*SymTable variable*/
	SymTable = new LL("Symbol Table.txt");

	/*Structure variable*/
	Token newToken;

	/*Integer variables*/
	int choice, i;
	int DSA = 0;
	int CSA = 0;
	int state = 0;

	/*Boolean variables*/
	bool finish = false;

	while (!finish)
	{
		switch (state)
		{
		default:
		{
			cout << "Error: Token class is unknown.";
			cout << endl;
			exit(EXIT_FAILURE);
			break;
		}
		case 0:	//Start
		{
			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[0][choice];

			break;
		}
		case 1:	//Class
		{
			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[1][choice];

			break;
		}
		case 2:	//Add '<ProgramName>' to the Symbol Table.	<var>
		{
			newToken.TClass = PROGRAMNAME;
			newToken.address = CSA;
			newToken.segment = CS;
			CSA += 2;
			SymTable->add(newToken);

			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[2][choice];

			break;
		}
		case 3:	// '{', ';'
		{
			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[3][choice];

			break;
		}
		case 4:	//CONST, ','
		{
			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[4][choice];

			break;
		}
		case 5:	//Add '$CONST' to the Symbol Table.	<var>
		{
			newToken.TClass = CONST;
			newToken.address = DSA;
			newToken.segment = DS;
			CSA += 2;
			SymTable->add(newToken);

			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[5][choice];

			break;
		}
		case 6:	// '='
		{
			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[6][choice];

			break;
		}
		case 7:	//Assign the last value to the 'CONST' variable.	<int>
		{
			SymTable->last->token.value = newToken.TString;
			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[7][choice];

			break;
		}
		case 8:	//VAR, ','
		{
			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[8][choice];

			break;
		}
		case 9:	//Add variable to the Symbol Table	<var>
		{
			if (!SymTable->inLL(newToken.TString))
			{
				newToken.address = DSA;
				newToken.segment = DS;
				newToken.value = '?';
				DSA += 2;
				SymTable->add(newToken);
			}

			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[9][choice];

			break;
		}
		case 10:	//Any, reserved words <var>
		{
			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[10][choice];

			break;
		}
		case 11:	//Add integer to the Symbol Table.	<int>
		{
			newToken.TString = "lit" + newToken.TString;

			if (!SymTable->inLL(newToken.TString))
			{
				newToken.address = DSA;
				newToken.segment = DS;
				newToken.value = newToken.TString.substr(3);	//Returns 'lit' with its value initialized to a copy of a sub-string.
				DSA += 2;
				SymTable->add(newToken);
			}

			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[11][choice];

			break;
		}
		case 12:	//Reached 'EOF' (End of pass 1).
		{
			finish = true;

			break;
		}
		case 13:
		{
			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[13][choice];

			break;
		}
		case 14:	//Add '<PROCEDURE>' to the Symbol Table.
		{
			if (!SymTable->inLL(newToken.TString))
			{
				newToken.TClass = PROCEDURENAME;
				newToken.address = CSA;
				newToken.segment = CS;
				CSA += 2;
				SymTable->add(newToken);
			}

			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[14][choice];

			break;
		}
		case 15:
		{
			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[15][choice];

			break;
		}
		case 16:	//Add '<PROCEDURE>' parameter(s) to the Symbol Table.
		{
			newToken.address = CSA;
			newToken.segment = CS;
			CSA += 2;
			SymTable->add(newToken);

			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[16][choice];

			break;
		}
		case 17:
		{
			newToken = buildToken();
			choice = tokenToInt(newToken);
			state = FPTable[17][choice];
			break;
		}
		}

		if (newToken.TClass != END_OF_FILE)
		{
			TFile << newToken.TString << "\t" << newToken.TClass;
			TFile << endl;
		}
	}

	TFile.close();	//Close token list file.

	//Add '<temp>' variables to the Symbol Table.
	newToken.TClass = "";
	newToken.value = "?";	//Prints '?' in value position.
	newToken.segment = DS;

	for (i = 0; i < 8; i++)
	{
		newToken.TString = "T" + to_string(i + 1);	//Returns string with value of i + 1.
		newToken.TClass = TEMP;
		newToken.address = DSA;
		DSA += 2;
		SymTable->add(newToken);
	}

	SymTable->printLL();
}

/*
Function: isReserved
Parameters: (Token token)
Description: Checks to see if the
string value is one of the reserved
words.
*/
int Scanner::isReserved(Token token)
{
	/*Integer variables*/
	int i;

	for (i = 0; i < reservedKnt; i++)
	{
		if (reserved[i].TString == token.TString)
		{
			return i;
		}
	}
	
	return -1;
}

/*
Function: charToInt
Parameters: (char ch)
Description: Converts a specified character
to a numeric value that can be passed to
another function. Unrecognized characters
are passed to a function that displays
an error message.
*/
int Scanner::charToInt(char ch)
{
	if (isalpha(ch))		//Letter
	{
		return 0;
	}
	else if (isdigit(ch))	//Digit
	{
		return 1;
	}
	else if (ch == '*')		// '*', Multiplication
	{
		return 2;
	}
	else if (ch == '/')		// '/', Division
	{
		return 3;
	}
	else if (ch == '=')		// '=', Assignment
	{
		return 4;
	}
	else if (ch == '<')		// '<', Less than
	{
		return 5;
	}
	else if (isspace(ch))	// ' ' Whitespace
	{
		return 6;
	}
	else if (ch == '{')		// '{', Left bracket
	{
		return 7;
	}
	else if (ch == '}')		// '}', Right bracket
	{
		return 8;
	}
	else if (ch == '+')		// '+', Addition
	{
		return 9;
	}
	else if (ch == '-')		// '-', Subtract
	{
		return 10;
	}
	else if (ch == ',')		// ',', Comma
	{
		return 11;
	}
	else if (ch == ';')		// ';', Semicolon
	{
		return 12;
	}
	else if (ch == '\0')	//End of the file.
	{
		return 13;
	}
	else if (ch == '>')		// '>', Greate than
	{
		return 14;
	}
	else if (ch == '(')		// '(', Left parenthesis
	{
		return 15;
	}
	else if (ch == ')')		// ')', Right parenthesis
	{
		return 16;
	}
	else if (ch == '!')		// '!', Exclamation point
	{
		return 17;
	}
	else					//Other
	{
		return 18;
	}
}

/*
Function: tokenToInt
Parameters: (Token token)
Description: Converts a recognized token's class
to a numeric value.
*/
int Scanner::tokenToInt(Token token)
{
	if (token.TClass == CLASS)				// $CLASS
	{
		return 0;
	}
	else if (token.TClass == VARNAME)		// <var>
	{
		return 1;
	}
	else if (token.TClass == LBRACK)		// '{'	$LB
	{
		return 2;
	}
	else if (token.TClass == RBRACK)		// '}'	$RB
	{
		return 3;
	}
	else if (token.TClass == SEMICOLON)		// ';'	<semi>
	{
		return 4;
	}
	else if (token.TClass == CONST)			// $CONST
	{
		return 5;
	}
	else if (token.TClass == VAR)			// <$var>
	{
		return 6;
	}
	else if (token.TClass == ASSIGN)		// '='	<assign>
	{
		return 7;
	}
	else if (token.TClass == INTEGER)		// 1 ... infinite	<integer>
	{
		return 8;
	}
	else if (token.TClass == COMMA)			// ','	<comma>
	{
		return 9;
	}
	else if (token.TClass == END_OF_FILE)	// '\0'	EOF
	{
		return 10;
	}
	else if (isReserved(token) != -1 && token.TClass != PROCEDURE)	//Reserved words that are not $PROCEDURE.
	{
		return 11;
	}
	else if (token.TClass == ADDOP || token.TClass == MOP)			// '+', '-', '*', '/'	<addop> and <mop>
	{
		return 12;
	}
	else if (token.TClass == PROCEDURE)		// $PROCEDURE
	{
		return 13;
	}
	else if (token.TClass == LPAREN)		// '('	$LP
	{
		return 14;
	}
	else if (token.TClass == RPAREN)		// ')'	$RP
	{
		return 15;
	}
	else if (token.TClass == RELOP)			// '<', '<=', '>', '>=', '==', '!=', <relop>
	{
		return 16;
	}
}

/*
Function: nextChar
Parameters: (N/A)
Description: Gets the next available character
from the Source Code file. If it's not EOF reads
the next character else returns '\0'.
*/
char Scanner::nextChar()
{
	/*Char variable*/
	char cha;

	if (SFile.peek() != EOF)	//If not End of File
	{
		SFile >> noskipws >> cha;	//Read next char skipping whitespaces.
	}
	else	//End of File
	{
		cha = '\0';
	}

	return cha;
}