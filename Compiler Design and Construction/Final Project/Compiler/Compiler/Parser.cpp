/*******************************************************
Name: Parser.cpp
Author: Christopher McDaniel
Date Started: 11 February 2020
Date Completed: 23 April 2020
Class: COSC 4316
Version: 1.1
Copyright: 2020
Description: This is a body file that parses the source
code, generates and optimizes the associated quads, and 
generates and operates the stack.

	 DISCLAIMER:
THIS PORTION "Parser.cpp" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "Parser.h".
*******************************************************/

/*Include Program header files*/
#include "Parser.h"

/*DATA STRUCTURES HYMNAL PAGE 30*/

/*
Constructor: Stack
Parameters: (N/A)
Description: Initializes stack to NULL.
*/
Stack::Stack()
{
	top = NULL;		//Indicates empty stack/list.
}

/*
Function: push
Parameters: (Token token)
Description: Pushes a new element onto
the stack incrementing it by one.
*/
void Stack::push(Token token)
{
	Node* newNode = NULL;

	if (nullptr != newNode)
	{
		newNode->token = token;	//Pt.Info <- Y.
		newNode->next = top;	//Pt.Link <- Top.
		top = newNode;			//Top <- Pt.
	}
	else	//Overflow
	{
		cout << "\nStack overflow.";
		exit(EXIT_FAILURE);
	}
}

/*
Function: pop
Parameters: (N/A)
Description: Pops the top element from
the stack decrementing it by one.
*/
Token Stack::pop()
{
	Token token;

	if (top == NULL)
	{
		cout << "\nStack Underflow.";
		return token;	//Underflow, empty stack.
	}
	else
	{
		Node* temp = top;	//Pt <- Top.
		token = top->token;	//Y <- Top.Info.
		top = top->next;	//Top <- Top.Link.

		delete temp;	//Pt => Avail, Avoid memory hemorraging.
		return token;
	}
}

/*
Function: peek
Parameters: (N/A)
Description: Returns top element of the
stack without modifying the stack.
*/
Token Stack::peek()
{
	Token token;
	if (top == NULL)	//If stack is empty.
	{
		return token;
	}
	else	//Else stack isn't empty.
	{
		token = top->token;
		return token;
	}
}

/*
Constructor: optimizeQuads
Parameters: (list<Quad> q)
Description: Gives quads the value
of 'q'.
*/
optimizeQuads::optimizeQuads(list<Quad> q)
{
	quads = q;

}

/*
Function: optimAssign
Parameters: (N/A)
Description: Optimizes the quads by
removing some redundant code.
*/
list<Quad> optimizeQuads::optimAssign()
{
	list<Quad> Quads_new;

	while (!quads.empty())	//While quads list is not empty.
	{
		if (quads.front().operation == "=")	//If the front of the quads list is '='.
		{
			//Returns the operation reference to the last element in the list container.
			if (Quads_new.back().operation == "+" || Quads_new.back().operation == "-" ||
				Quads_new.back().operation == "*" || Quads_new.back().operation == "/")
			{
				//If operand_3 on the back of the list is equal to operand_2 on the front of the list.
				if (Quads_new.back().operand_3 == quads.front().operand_2)
				{
					//Assign operand_1 at the front of the list to operand_3 at the back.
					Quads_new.back().operand_3 = quads.front().operand_1;
				}
				else	//Add the front of the quad to the end of the Quads_new container.
				{
					Quads_new.push_back(quads.front());
				}
			}
			else	//Add the front of the quad to the end of the Quads_new container.
			{
				Quads_new.push_back(quads.front());
			}
		}
		else	//Add the front of the quad to the end of the Quads_new container.
		{
			Quads_new.push_back(quads.front());
		}

		quads.pop_front();	//Pops the front of the quads list.
	}

	return Quads_new;
}

/*
Constructor: Parser
Parameters: (string SFileName)
Description: Open and closes the file that
will be used in the creation of the Precedence
array. It then populates said array. It also
creates the Quad file here.
*/
Parser::Parser(string SFileName)
{
	/*Integer variables*/
	int i, j;

	scanner = new Scanner(SFileName);

	QFile.open("Quad File.txt");	//Open file
	if (QFile.fail())	//Check if opening was successful.
	{
		cout << "Error opening Quad File.txt";
		cout << endl;
		exit(EXIT_FAILURE);	//End program.
	}

	PTFile.open("InputFiles/precedenceTable.txt");	//Open file
	if (PTFile.fail())	//Check if opening was successful.
	{
		cout << "Error opening precedenceTable.txt";
		cout << endl;
		exit(EXIT_FAILURE);	//End program.
	}

	PTFile >> operatorKnt;

	PTable = new char* [operatorKnt];	//Make Precedence Table a 2D array.
	for (i = 0; i < operatorKnt; i++)
	{
		PTable[i] = new char[operatorKnt];

		for (j = 0; j < operatorKnt; j++)	//Populate the table.
		{
			PTFile >> PTable[i][j];
		}
	}
	PTFile.close();	//Close precedence table file.
}

/*
Function: sourceParse
Parameters: (N/A)
Description: Retrieves one token at a time
from the Scanner and either pushes onto the
stack or pops from the stack in order to
generate the quads. Also, determines the
precedence of an operator as it comes in.
*/
void Parser::sourceParse()
{
	/*Token structure variables*/
	Token token;
	Token semiT;
	Token temp;

	/*Quad structure variables*/
	Quad LBracket;
	Quad RBracket;
	Quad quad;
	Quad Quad_IF;
	Quad Quad_WHILE;
	Quad Quad_ThenDo;
	Quad Quad_EOF;

	/*Boolean variable*/
	bool finish;

	/*Integer variables*/
	int choice;
	int topCol = 0;

	/*Character variable*/
	char prec;

	semiT.TString = ";";
	semiT.TClass = SEMICOLON;
	t.push(semiT);	//Pushes the initial semicolon onto the stack.

	//Get the next token.
	token = scanner->buildToken();
	choice = classToInt(token.TClass);	//Pass the return value to the variable.

	while (token.TClass != END_OF_FILE)	//While not the End of the File.
	{
		finish = false;

		while (!finish)	//While not finished.
		{
			if (token.TClass == END_OF_FILE)	//If End of File, exit.
			{
				break;
			}
			else if (choice == -1)	//Else push it onto the stack.
			{
				if (token.TClass == INTEGER)
				{
					token.TString = "lit" + token.TString;	//Gives an INTEGER the form of "lit#".
				}
				t.push(token);	//Pushes the token onto the stack.

				//Get the next token.
				token = scanner->buildToken();
				choice = classToInt(token.TClass);	//Pass the return value to the variable.
			}
			else if (t.top().TClass == SEMICOLON && token.TClass == SEMICOLON)	//Else, if it's a SEMICOLON, ';', finish.
			{
				//Get the next token.
				token = scanner->buildToken();
				choice = classToInt(token.TClass);	//Pass the return value to the variable.
				finish = true;
			}
			else	//Else it's an operator.
			{
				prec = PTable[topCol][choice];

				if (prec == '<' || prec == '=')	//Top of the stack yields to the incoming operator.
				{
					if (token.TClass == LBRACK || token.TClass == PROC_LBRACK)	//Left bracket.
					{
						Stack_Brack.push(token.TClass);	//Pushes the token class onto the bracket stack.
						t.push(token);	//Pushes the token onto the stack.
						topCol = classToInt(token.TClass);	//Pass the return value to the variable.

						LBracket = { token.TString, "?", "?", "?" };	//Left bracket quad.

						QFile << LBracket.Quad_print();	//Print left bracket quad into Quad file.
						Quad_add(LBracket);	//Send LBracket to Quad_add function.

						//Get the next token.
						token = scanner->buildToken();
						choice = classToInt(token.TClass);	//Pass the return value to the variable.
					}
					else if (token.TClass == RBRACK || token.TClass == PROC_RBRACK)	//Right bracket.
					{
						if (Stack_Brack.empty())	//Error since right bracket is missing matching left bracket.
						{
							cout << "Error: missing a matching pair of brackets";
							cout << endl;

							errorRecov(token, topCol, choice);
						}
						else	//No error since right bracket has matching left bracket.
						{
							if (Stack_Brack.top() != PROC_LBRACK)	//Create right bracket quad.
							{
								RBracket = { token.TString, "?", "?", "?" };	//Right bracket quad.

								mainQ.push_back(RBracket);	//Adds RBracket to the end of the mainQ container.
							}
							else	//Create PROC_RBRACK quad.
							{
								RBracket = { PROC_RBRACK, "?", "?", "?" };
								procedureQ.push_back(RBracket);	//Adds RBracket to the end of the procedureQ container.

								isQuad = false;	//Not a quad.
								RBracket.operation = "}";
							}

							Stack_Brack.pop();	//Pop the bracket stack.
							t.pop();	//Pops the token from the stack.

							QFile << RBracket.Quad_print();	//Print right bracket quad into Quad file.

							topCol = classToInt(t.top().TClass);	//Pass the return value to the variable.
							token = semiT;
							choice = 0;
						}
					}
					else if (token.TClass == LPAREN)	//Left parenthesis.
					{
						Stack_Paren.push(token.TClass);	//Pushes the token class onto the parenthesis stack.
						topCol = choice;
						t.push(token);	//Pushes the token onto the stack.

						//Get the next token.
						token = scanner->buildToken();
						choice = classToInt(token.TClass);	//Pass the return value to the variable.
					}
					else if (token.TClass == RPAREN)	//Right parenthesis.
					{
						if (Stack_Paren.size() > 0)
						{
							Stack_Paren.pop();	//Pop parenthesis stack.
							topCol = choice;
							t.push(token);	//Pushes the token onto the stack.

							//Get the next token.
							token = scanner->buildToken();
							choice = classToInt(token.TClass);	//Pass the return value to the variable.
						}
						else	//An error.
						{
							cout << "Error: missing a matching pair of parenthesis";
							cout << endl;

							errorRecov(token, topCol, choice);
						}
					}
					else	//Neither a bracket, '{' '}', nor a parenthesis, '(' ')'.
					{
						t.push(token);	//Pushes the token onto the stack.

						if (token.TClass == IF)	// If an 'IF' statement.
						{
							Quad_IF = { token.TString, "?", "?", "?" };	//IF statement quad.

							QFile << Quad_IF.Quad_print();	//Print IF statement quad into Quad file.
							Quad_add(Quad_IF);	//Send Quad_IF to Quad_add function.
						}
						else if (token.TClass == THEN || token.TClass == DO)	//Else, if a 'THEN' or 'DO' statement.
						{
							label = "L" + to_string(labelKnt);
							fixUp.push(label);	//Pushed the label onto the fixUp stack.
							labelKnt++;

							Quad_ThenDo = { token.TString, label, "?", "?" };	//THEN and DO statement quad.

							QFile << Quad_ThenDo.Quad_print();	//Print ThenDo statement quad into Quad file.
							Quad_add(Quad_ThenDo);	//Send Quad_ThenDo to Quad_add function.
						}
						else if (token.TClass == WHILE)	// Else, if a 'WHILE' statement.
						{
							whileLabel = "W" + to_string(whileKnt);
							whileKnt++;
							startWhile.push(whileLabel);	//Pushes the WHILE label onto the startWhile stack.

							Quad_WHILE = { token.TString, whileLabel, "?", "?" };	//WHILE statement quad.

							QFile << Quad_WHILE.Quad_print();	//Print WHILE statement quad into Quad file.
							Quad_add(Quad_WHILE);	//Send Quad_WHILE to Quad_add function.
						}

						topCol = choice;

						//Get the next token.
						token = scanner->buildToken();
						choice = classToInt(token.TClass);	//Pass the return value to the variable.
					}
				}
				else if (prec == '>')	//Top of the stack takes precedence over the incoming operator.
				{
					/*Queue variable*/
					queue <Token> q;

					/*Integer variables*/
					int operatorN;
					int popped = -1;

					while (prec == '>' || prec == '=' || prec == 'X' || prec == 'x')
					{
						operatorN = classToInt(t.top().TClass);	//Pass the return value to the variable.

						if (operatorN != -1)
						{
							if (popped != -1)
							{
								prec = PTable[operatorN][popped];

								if (prec == '>' || prec == '=' || prec == 'X' || prec == 'x')
								{
									popped = operatorN;
									q.push(t.top());	//Pushes the top token onto the quad stack.
									t.pop();
								}
							}
							else
							{
								popped = operatorN;
								q.push(t.top());	//Pushes the top token onto the quad stack.
								t.pop();	//Pops the token from the stack.
								
							}
						}
						else	//operatorN == -1.
						{
							if (t.top().TClass == TEMP)
							{
								//Generates a sub string then converts it to an integer and allows the reuse
								//of the temporaries that have been popped from the stack.
								tempKnt = stoi(t.top().TString.substr(1));
							}

							q.push(t.top());	//Pushes the top token onto the quad stack.
							t.pop();	//Pops the token from the stack.
						}
					}

					switch (popped)
					{
					case 0:	//Semicolon, ';'.
					{
						break;
					}
					case 1:	//Assignment, '='.
					{
						isError("=", quad, q);
						quad.operand_3 = "?";	//Prints '?' in operand position.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					case 2:	//Add operator, '+' and '-'.
					{
						isError("ADDOP", quad, q);
						temp.TString = "T" + to_string(tempKnt);	//Convert a numeric value to string.
						tempKnt++;

						quad.operand_3 = temp.TString;
						temp.TClass = TEMP;
						t.push(temp);	//Pushes the temporary onto the stack.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					case 3:	//Left parenthesis, '('.
					{
						//If front of quad equals a right parenthesis.
						if (q.front().TClass == RPAREN)
						{
							q.pop();	//Pop the quad.
						}

						while (q.size() != 0)
						{
							if (classToInt(q.front().TClass) == -1)
							{
								t.push(q.front());	//Pushes the front quad onto the stack.
							}
							q.pop();	//Pops the quad from the stack.
						}

						break;
					}
					case 4:	//Right parenthesis, ')'
					{
						break;
					}
					case 5:	//Multiplication operator, '*' and '/'
					{
						isError("MOP", quad, q);

						temp.TString = "T" + to_string(tempKnt);	//Convert a numeric value to a string.
						temp.TClass = TEMP;

						quad.operand_3 = temp.TString;
						t.push(temp);	//Pushes the temporary onto the stack.

						tempKnt++;

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					case 6:	//IF
					{
						quad.operation = fixUp.top();
						fixUp.pop();	//Pops the quad from the stack.

						quad.operand_1 = "?";	//Prints '?' in operand position.
						quad.operand_2 = "?";	//Prints '?' in operand position.
						quad.operand_3 = "?";	//Prints '?' in operand position.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					case 7:	// THEN
					{
						break;
					}
					case 8:	//ODD
					{
						if (q.front().TClass != VARNAME && q.front().TClass != INTEGER)	//Error
						{
							cout << "Error: Missing an operand after 'ODD'.";
							cout << endl;

							quad.operand_1 = "ERROR";	//Prints "ERROR" in operand position.

							errors = true;	//Is error.
						}
						else	//Good
						{
							quad.operand_1 = q.front().TString;
							q.pop();	//Pops the quad from the stack.
						}

						quad.operation = q.front().TString;
						q.pop();	//Pops the quad from the stack.

						quad.operand_2 = "?";	//Prints '?' in operand position.
						quad.operand_3 = "?";	//Prints '?' in operand position.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					case 9:	//Relational Operator, '<', '<=', '>', '>=', '==', and '!='.
					{
						isError("RELOP", quad, q);
						quad.operand_3 = "?";	//Prints '?' in operand position.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					case 10:	//Left bracket, '{'.
					{
						break;
					}
					case 11:	//Right bracket, '}'
					{
						break;
					}
					case 12:	//CALL
					{
						if (q.front().TClass == RPAREN)
						{
							while (q.front().TClass != LPAREN)
							{
								q.pop();	//Pops the quad from the stack.
							}
							q.pop();	//Pops the quad from the stack.
						}

						if (q.front().TClass == VARNAME)
						{
							quad.operand_1 = q.front().TString;
							q.pop();	//Pops the quad from the stack.
						}
						else if (q.front().TClass != VARNAME)
						{
							cout << "Error: Missing the procedure identifier after the keyword 'CALL'.";
							cout << endl;

							quad.operand_1 = "ERROR";	//Prints "ERROR" in operand position.

							errors = true;	//Is error.
						}

						quad.operation = q.front().TString;
						q.pop();	//Pops the quad from the stack.

						quad.operand_2 = "?";	//Prints '?' in operand position.
						quad.operand_3 = "?";	//Prints '?' in operand position.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					case 13:	//WHILE
					{
						quad.operation = startWhile.top();
						startWhile.pop();	//Pops the WHILE from the stack.

						quad.operand_1 = "?";	//Prints '?' in operand position.
						quad.operand_2 = "?";	//Prints '?' in operand position.
						quad.operand_3 = "?";	//Prints '?' in operand position.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						quad.operation = fixUp.top();
						fixUp.pop();	//Pops the quad from the stack.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					case 14:	//DO
					{
						break;
					}
					case 15:	//COMMA, ','
					{
						break;
					}
					case 16:	//CLASS
					{
						if (q.front().TClass == VARNAME)
						{
							quad.operand_1 = q.front().TString;
							q.pop();	//Pops the quad from the stack.
						}
						else if (q.front().TClass != VARNAME)
						{
							cout << "Error: Missing the class identifier.";
							cout << endl;

							quad.operand_1 = "ERROR";	//Prints "ERROR" in operand position.

							errors = true;	//Is error.
						}

						quad.operation = q.front().TString;
						q.pop();	//Pops the quad from the stack.

						quad.operand_2 = "?";	//Prints '?' in operand position.
						quad.operand_3 = "?";	//Prints '?' in operand position.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					case 17:	//VAR
					{
						int state = 0;	//Initial switch state.
						int index;
						bool varCheck = true;	//There is a variable.

						while (varCheck)
						{
							if (q.size() > 0)
							{
								if (q.front().TClass == VARNAME)
								{
									index = 0;
								}
								else if (q.front().TClass == COMMA)
								{
									index = 1;
								}
								else if (q.front().TClass == VAR)
								{
									index = 2;
								}
								else	//Error
								{
									cout << "Error: The token " << q.front().TString << ", within the 'VAR' statement, is unexpected.";
									cout << endl;

									errors = true;	//Is error.

									break;
								}
							}

							switch (state)
							{
							case 0:
							{
								if (index == 0)	//No error
								{
									state = varState[0][index];
								}
								else	//Error
								{
									cout << "Error: Missing a variable within the 'VAR' statement.";
									cout << endl;

									varCheck = false;	//No variable.
									errors = true;	//Is error.
								}

								break;
							}
							case 1:
							{
								if (index == 1 || index == 2)	//No error
								{
									state = varState[1][index];
								}
								else	//Error
								{
									cout << "Error: The token " << q.front().TString << ", within the 'VAR' statement, is missing a ";
									cout << "'" << COMMA << "'";
									cout << endl;

									varCheck = false;	//No variable.
									errors = true;	//Is error.
								}

								break;
							}
							case 2:
							{
								if (index == 0)	//No error
								{
									state = varState[2][index];
								}
								else	//Error
								{
									cout << "Error: Missing a variable within the 'VAR' statement.";
									cout << endl;

									varCheck = false;	//No variable.
									errors = true;	//Is error.
								}
							}
							case 3:	//Error
							{
								varCheck = false;	//No variable.

								break;
							}
							}

							if (q.size() > 0)
							{
								q.pop();
							}
						}

						break;
					}
					case 18:	//CONST
					{
						int state = 0;	//Initial switch state.
						int index;
						bool constCheck = true;	//There is a constant.

						while (constCheck)
						{
							if (q.size() > 0)
							{
								if (q.front().TClass == INTEGER)
								{
									index = 0;
								}
								else if (q.front().TClass == ASSIGN)
								{
									index = 1;
								}
								else if (q.front().TClass == VARNAME)
								{
									index = 2;
								}
								else if (q.front().TClass == COMMA)
								{
									index = 3;
								}
								else if (q.front().TClass == CONST)
								{
									index = 4;
								}
								else	//Error
								{
									cout << "Error: The token " << q.front().TString << ", within the 'CONST' statement, is unexpected.";
									cout << endl;

									errors = true;	//Is error.

									break;
								}
							}

							switch (state)
							{
							case 0:
							{
								if (index == 0)	//No error
								{
									state = constState[0][index];
								}
								else	//Error
								{
									cout << "Error: Missing an integer value within the 'CONST' statement.";
									cout << endl;

									constCheck = false;	//No constant.
									errors = true;	//Is error.
								}

								break;
							}
							case 1:
							{
								if (index == 1)	//No error
								{
									state = constState[1][index];
								}
								else	//Error
								{
									cout << "Error: Missing a '=' within the 'CONST' statement.";
									cout << endl;

									constCheck = false;	//No constant.
									errors = true;	//Is error.
								}

								break;
							}
							case 2:
							{
								if (index == 2)	//No error
								{
									state = constState[2][index];
								}
								else	//Error
								{
									cout << "Error: Missing a variable value within the 'CONST' statement.";
									cout << endl;

									constCheck = false;	//No constant.
									errors = true;	//Is error.
								}

								break;
							}
							case 3:
							{
								if (index == 3 || index == 4)	//No error
								{
									state = constState[3][index];
								}
								else	//Error
								{
									cout << "Error: The token " << q.front().TString << ", within the 'CONST' statement, is unexpected.";
									cout << endl;

									constCheck = false;	//No constant.
									errors = true;	//Is error.
								}

								break;
							}
							case 4:
							{
								if (index == 0)	//No error
								{
									state = constState[4][index];
								}
								else	//Error
								{
									cout << "Error: Missing an integer value within the 'CONST' statement.";
									cout << endl;

									constCheck = false;	//No constant.
									errors = true;	//Is error.
								}

								break;
							}
							case 5:	//Error
							{
								constCheck = false;	//No constant.

								break;
							}
							}

							if (q.size() > 0)
							{
								q.pop();	//Pops the quad from the stack.
							}
						}

						break;
					}
					case 19:	//PROCEDURE
					{
						isQuad = true;	//Is a quad.

						token.TClass = PROC_LBRACK;

						if (q.front().TClass == RPAREN)
						{
							while (q.front().TClass != LPAREN)
							{
								q.pop();	//Pops the quad from the stack.
							}

							q.pop();	//Pops the quad from the stack.
						}

						if (q.front().TClass != VARNAME)	//Error
						{
							cout << "Error: Missing the procedure identifier.";
							cout << endl;

							quad.operand_1 = "ERROR";	//Prints "ERROR" in operand position.

							errors = true;	//Is error.
						}
						else if (q.front().TClass == VARNAME)	//No error
						{
							quad.operand_1 = q.front().TString;	//<ProcedureName>
							q.pop();	//Pops the quad from the stack.
						}

						quad.operation = q.front().TString;	//"PROCEDURE"
						q.pop();	//Pops the quad from the stack.

						quad.operand_2 = "?";	//Prints '?' in operand position.
						quad.operand_3 = "?";	//Prints '?' in operand position.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					case 20:	//READ
					{
						if (q.front().TClass != VARNAME)	//Error
						{
							cout << "Error: After 'READ', there is a missing variable operand.";
							cout << endl;

							quad.operand_1 = "ERROR";	//Prints "ERROR" in operand position.

							errors = true;	//Is error.
						}
						else if (q.front().TClass == VARNAME)	//No error
						{
							quad.operand_1 = q.front().TString;
							q.pop();	//Pops the quad from the stack.
						}

						quad.operation = q.front().TString;
						q.pop();	//Pops the quad from the stack.

						quad.operand_2 = "?";	//Prints '?' in operand position.
						quad.operand_3 = "?";	//Prints '?' in operand position.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					case 21:	//WRITE
					{
						if (q.front().TClass != VARNAME && q.front().TClass != INTEGER)
						{
							cout << "Error: After 'WRITE', there is a missing variable or integer operand.";
							cout << endl;

							quad.operand_1 = "ERROR";	//Prints "ERROR" in operand position.

							errors = true;	//Is error.
						}
						else
						{
							quad.operand_1 = q.front().TString;
							q.pop();	//Pops the quad from the stack.
						}

						quad.operation = q.front().TString;
						q.pop();	//Pops the quad from the stack.

						quad.operand_2 = "?";	//Prints '?' in operand position.
						quad.operand_3 = "?";	//Prints '?' in operand position.

						QFile << quad.Quad_print();	//Print the quad into Quad file.
						Quad_add(quad);

						break;
					}
					}

					topCol = operatorN;	//New top operator on the stack.

				}
				else	//Error
				{
					/*String variables*/
					string opString;
					string topString = intToClass(topCol);

					//No precedence relation = 'X' in the table.
					cout << "Error: Found '" << token.TString << "' after " << topString << ", but expected ";

					for (int i = 0; i < operatorKnt; i++)
					{
						if (PTable[topCol][i] != 'X' && PTable[topCol][i] != 'x')
						{
							opString = intToClass(i);

							cout << opString << ", ";

							errors = true;
						}
						else if (PTable[topCol][i] == 'X' || PTable[topCol][i] == 'x')
						{
							errors = false;
						}
					}

					token = errorRecov(token, topCol, choice);
				}
			}
		}
	}

	//Missing a bracket.
	if (Stack_Brack.size() > 0)	//Error
	{
		cout << "Bracket is missing its pair.";
		cout << endl;

		errors = true;	//Is error.
	}
	else	//Good
	{
		errors = false;
	}

	if (errors)	//Errors
	{
		cout << "Error: Parse was completed, but errors were detected.";
		cout << endl;
	}
	else	//No errors
	{
		scanner->buildSTable();
		Quad_EOF = { "EOF", "?", "?", "?" };	//EOF quad.
		mainQ.push_back(Quad_EOF);	//Adds Quad_EOF to the end of the procedureQ container.

		if (procedureQ.size() > 0)
		{
			mainQ.splice(mainQ.end(), procedureQ);
		}

		if (!varCheck(mainQ, scanner->SymTable))
		{
			if (assignCheck(mainQ, scanner->SymTable))
			{
				optimizeQuads optimize(mainQ);
				mainQ = optimize.optimAssign();

				CodeGen gen(mainQ, scanner->SymTable);
				gen.genCode();
			}
			else
			{
				cout << "Error: The reassignment attempt(s) of 'CONST' need(s) to be resolved before the code can be generated.";
				cout << endl;
			}
		}
		else
		{
			cout << "Error: The undeclared variable(s) need(s) to be resolved before the code can be generated.";
			cout << endl;
		}
	}

	QFile.close();	//Close Quad file.
}

/*
Function: classToInt
Parameters: (string str)
Description: Converts token classification
to a numeric value.
*/
int Parser::classToInt(string str)
{
	if (str == VARNAME || str == INTEGER || str == END_OF_FILE || str == TEMP)
	{
		return -1;
	}
	else if (str == SEMICOLON)
	{
		return 0;
	}
	else if (str == ASSIGN)
	{
		return 1;
	}
	else if (str == ADDOP)
	{
		return 2;
	}
	else if (str == LPAREN)
	{
		return 3;
	}
	else if (str == RPAREN)
	{
		return 4;
	}
	else if (str == MOP)
	{
		return 5;
	}
	else if (str == IF)
	{
		return 6;
	}
	else if (str == THEN)
	{
		return 7;
	}
	else if (str == ODD)
	{
		return 8;
	}
	else if (str == RELOP)
	{
		return 9;
	}
	else if (str == LBRACK || str == PROC_LBRACK)
	{
		return 10;
	}
	else if (str == RBRACK || str == PROC_RBRACK)
	{
		return 11;
	}
	else if (str == CALL)
	{
		return 12;
	}
	else if (str == WHILE)
	{
		return 13;
	}
	else if (str == DO)
	{
		return 14;
	}
	else if (str == COMMA)
	{
		return 15;
	}
	else if (str == CLASS)
	{
		return 16;
	}
	else if (str == VAR)
	{
		return 17;
	}
	else if (str == CONST)
	{
		return 18;
	}
	else if (str == PROCEDURE)
	{
		return 19;
	}
	else if (str == READ)
	{
		return 20;
	}
	else if (str == WRITE)
	{
		return 21;
	}
}

/*
Function: isError
Parameters: (string oper, Quad& quad, queue <Token>& q)
Description: Checks for a missing operand and looks to
see if said operand is of a valid classification.
*/
void Parser::isError(string oper, Quad& quad, queue <Token>& q)
{
	if (q.front().TClass != INTEGER && q.front().TClass != VARNAME && q.front().TClass != TEMP)	//Error
	{
		cout << "Error: Missing an operand after '" << oper << "'";
		cout << endl;

		quad.operand_2 = "ERROR";	//Prints "ERROR" in operand position.

		errors = true;	//Is error.
	}
	else
	{
		quad.operand_2 = q.front().TString;
		q.pop();
	}

	quad.operation = q.front().TString;
	q.pop();

	if (q.size() > 0)
	{
		if (q.front().TClass != INTEGER && q.front().TClass != VARNAME && q.front().TClass != TEMP)
		{
			cout << "Error: Missing an operand after '" << oper << "'";
			cout << endl;

			quad.operand_1 = "ERROR";	//Prints "ERROR" in operand position.

			errors = true;	//Is error.
		}
		else
		{
			quad.operand_1 = q.front().TString;
			q.pop();
		}
	}
	else if (q.size() <= 0)
	{
		cout << "Error: Missing an operand before '" << oper << "'";
		cout << endl;

		quad.operand_1 = "ERROR";	//Prints "ERROR" in operand position.

		errors = true;	//Is error.
	}
}

/*
Function: Quad_add
Parameters: (Quad quad)
Description: Adds quad to appropriate container.
*/
void Parser::Quad_add(Quad quad)
{
	if (!isQuad)
	{
		mainQ.push_back(quad);	//Adds quad to the end of the mainQ container.
	}
	else if (isQuad)
	{
		procedureQ.push_back(quad);	//Adds quad to the end of the procedureQ container.
	}
}

/*
Function: varCheck
Parameters: (list <Quad> quads, LL* table)
Description: Checks the symbol table to make sure
all of the variables and literals, that are in the
quad, are present.
*/
bool Parser::varCheck(list <Quad> quads, LL* table)
{
	bool undeclaredVars = false;

	while (!quads.empty())
	{
		if (quads.front().operation != "WHILE" && quads.front().operation != "DO" &&
			quads.front().operation.at(0) != 'L' && quads.front().operation != "THEN")
		{
			if (quads.front().operand_1 != "?")
			{
				if (table->inLL(quads.front().operand_1))
				{
					undeclaredVars = false;
				}
				else
				{
					undeclaredVars = true;

					cout << "The variable " << quads.front().operand_1 << " is undeclared.";
					cout << endl;
				}
			}

			if (quads.front().operand_2 != "?")
			{
				if (table->inLL(quads.front().operand_2))
				{
					undeclaredVars = false;
				}
				else
				{
					undeclaredVars = true;

					cout << "The variable " << quads.front().operand_2 << " is undeclared.";
					cout << endl;
				}
			}

			if (quads.front().operand_3 != "?")
			{
				if (table->inLL(quads.front().operand_3))
				{
					undeclaredVars = false;
				}
				else
				{
					undeclaredVars = true;

					cout << "The variable " << quads.front().operand_3 << " is undeclared.";
					cout << endl;
				}
			}
		}

		quads.pop_front();
	}

	return undeclaredVars;
}

/*
Function: assignCheck
Parameters: (list <Quad> quads, LL* table)
Description: Checks to see if any of the
quads with an assignment operator try to
illegaly assign a value to a constant.
*/
bool Parser::assignCheck(list <Quad> quads, LL* table)
{
	string oper;
	bool assignCheck = true;

	while (!quads.empty())
	{
		oper = quads.front().operation;

		if (oper == "=")
		{
			if (table->getClass(quads.front().operand_1) != CONST)
			{
				assignCheck = true;
			}
			else if (table->getClass(quads.front().operand_1) == CONST)
			{
				assignCheck = false;

				cout << "Error: CONST variable on left side of assignment statement: " << quads.front().operand_1;
				cout << endl;
			}
		}

		quads.pop_front();
	}

	return assignCheck;
}

/*
Function: intToClass
Parameters: (int num)
Description: Returns the class associated
with the value of the respective token.
Used for displaying error messages.
*/
string Parser::intToClass(int num)
{
	switch (num)
	{
	case 0:		// <semi>
	{
		return "';'";
		break;
	}
	case 1:		// <assign>
	{
		return "'='";
		break;
	}
	case 2:		// <addop>
	{
		return "'+' or '-'";
		break;
	}
	case 3:		// $LP
	{
		return "'('";
		break;
	}
	case 4:		// $RP
	{
		return "')'";
		break;
	}
	case 5:		// <mop>
	{
		return "'*', '/'";
		break;
	}
	case 6:		// $IF
	{
		return "'IF'";
		break;
	}
	case 7:		// $THEN
	{
		return "'THEN'";
		break;
	}
	case 8:		// $ODD
	{
		return "'ODD'";
		break;
	}
	case 9:		// <relop>
	{
		return "'>', '<', '<=', '>=', or '!='";
		break;
	}
	case 10:	// $LB
	{
		return "'{'";
		break;
	}
	case 11:	// $RB
	{
		return "'}'";
		break;
	}
	case 12:	// $CALL
	{
		return "'CALL'";
		break;
	}
	case 13:	// $WHILE
	{
		return "'WHILE'";
		break;
	}
	case 14:	//$DO
	{
		return "'DO'";
		break;
	}
	case 15:	// <comma>
	{
		return "','";
		break;
	}
	case 16:	// $CLASS
	{
		return "'CLASS'";
		break;
	}
	case 17:	// <$var>
	{
		return "'VAR'";
		break;
	}
	case 18:	// $CONST
	{
		return "'CONST'";
		break;
	}
	case 19:	// $PROCEDURE
	{
		return "'PROCEDURE'";
		break;
	}
	case 20:	// $READ
	{
		return "'READ'";
		break;
	}
	case 21:	// $WRITE
	{
		return "'WRITE'";
		break;
	}
	}
}

/*
Function: errorRecov
Parameters: (Token current, int& topCol, int& choice)
Description: Skips to the next line of code until a
delimiter or EOF is reached. An error has occured and
code generation has been prvented.
*/
Token Parser::errorRecov(Token current, int& topCol, int& choice)
{
	errors = true;	//Is error.	Code will not generate.

	cout << "Next line...";
	cout << endl;

	while (current.TClass != SEMICOLON && current.TClass != END_OF_FILE && current.TClass != RBRACK
		&& current.TClass != LBRACK && current.TClass != PROC_LBRACK)
	{
		current = scanner->buildToken();
	}

	while (t.top().TClass != SEMICOLON && t.size() != 1)
	{
		if (t.top().TClass == LBRACK || t.top().TClass == PROC_LBRACK)
		{
			break;
		}
		t.pop();
	}

	topCol = classToInt(t.top().TClass);	//New top of the stack
	choice = classToInt(current.TClass);	//Next token for input.

	return current;
}