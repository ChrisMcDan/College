/*******************************************************
Name: CodeGen.cpp
Author: Christopher McDaniel
Date Started: 11 February 2020
Date Completed: 23 April 2020
Class: COSC 4316
Version: 1.1
Copyright: 2020
Description: This is a body file that generates the .asm
file, reads portions from the IO1Nasm32Linux.asm and uses
 them as inputs to help in the generation of the code.

	 DISCLAIMER:
THIS PORTION "CodeGen.cpp" IS REQUIRED TO BE USED IN
CONJUNCTION WITH "CodeGen.h".
*******************************************************/

/*Include Program header files*/
#include "CodeGen.h"

/*
Constructor: CodeGen
Parameters: (list <Quad> q, LL* table)
Description: Creates the Assembly file
that will be generated.
*/
CodeGen::CodeGen(list <Quad> q, LL* table)
{
	/*Call variables and assign new value*/
	queue_Quad = q;
	SymTable = table;

	/*String variable*/
	string name = "AssemblyCode/";

	//Names the Assembly program from the <ProgramName> in the Symbol Table.
	if (SymTable->head->token.TClass == "<ProgramName>")
	{
		name += SymTable->head->token.TString;
	}

	name += ".asm";	//Adds '.asm' to the end of the file name

	out_stream.open(name);	//Open the file.
	if (out_stream.fail())	//Checks if opening was successful.
	{
		cout << "Error: The file could not be opened properly: " << name;
		cout << endl;
		exit(EXIT_FAILURE);	//End program.
	}
}

/*
Function: genCode
Parameters: (N/A)
Description: Uses the quads generated by the Parser
to create the Assembly language equivalent of the
source program. For the literal values, optimization
will occur.
*/
void CodeGen::genCode()
{
	/*Integer variable*/
	int choice;

	/*String variable*/
	string lit = "lit";

	/*Call this function*/
	addDSandBS();	//Adds these sections to start of Assembly file.

	//Put 'section .txt' into Assembly file.
	out_stream << "\nsection .txt\t ;Start of the main program-------------------------------------------.\n\n";

	while (queue_Quad.size() != 0)
	{
		choice = quadToInt(queue_Quad.front());

		switch (choice)
		{
		case 0:		//'+'
		{
			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			if (queue_Quad.front().operand_2.compare(0, 3, lit) == 0)
			{
				out_stream << "\tadd ax, " << queue_Quad.front().operand_2.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tadd ax, [" << queue_Quad.front().operand_2 << "]\n";
			}

			out_stream << "\tmov [" << queue_Quad.front().operand_3 << "], ax\n\n";

			break;
		}
		case 1:		//'-'
		{
			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			if (queue_Quad.front().operand_2.compare(0, 3, lit) == 0)
			{
				out_stream << "\tsub ax, " << queue_Quad.front().operand_2.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tsub ax, [" << queue_Quad.front().operand_2 << "]\n";
			}

			out_stream << "\tmov [" << queue_Quad.front().operand_3 << "], ax\n\n";

			break;
		}
		case 2:		//'*'
		{
			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			if (queue_Quad.front().operand_2.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov bx, " << queue_Quad.front().operand_2.substr(3) << "\n" << "\tmul word bx\n";
			}
			else
			{
				out_stream << "\tmul word [" << queue_Quad.front().operand_2 << "]\n";
			}

			out_stream << "\tmov [" << queue_Quad.front().operand_3 << "], ax\n\n";

			break;
		}
		case 3:		//'/'
		{
			out_stream << "\tmov dx, 0\n";

			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			if (queue_Quad.front().operand_2.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov bx, " << queue_Quad.front().operand_2.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov bx, [" << queue_Quad.front().operand_2 << "]\n";
			}

			out_stream << "\tdiv bx\n" << "\tmov [" << queue_Quad.front().operand_3 << "], ax\n\n";

			break;
		}
		case 4:		//'='
		{
			if (queue_Quad.front().operand_2.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov word [" << queue_Quad.front().operand_1 << "], "
					<< queue_Quad.front().operand_2.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_2 << "]\n" << "\tmov ["
					<< queue_Quad.front().operand_1 << "], ax\n\n";
			}

			break;
		}
		case 5:		//'IF'
		{
			break;
		}
		case 6:		//'THEN'
		{
			out_stream << queue_Quad.front().operand_1 << "\n\n";

			break;
		}
		case 7:		//'L#' labels
		{
			out_stream << queue_Quad.front().operation << ":\tnop\n";

			break;
		}
		case 8:		//'WHILE'
		{
			out_stream << queue_Quad.front().operand_1 << ":\tnop\n";

			break;
		}
		case 9:		//'DO'
		{
			out_stream << queue_Quad.front().operand_1 << "\n";

			break;
		}
		case 10:	//'W#' labels
		{
			out_stream << "\tjmp " << queue_Quad.front().operation << "\n";

			break;
		}
		case 11:	//'CLASS'
		{
			out_stream << "   global _start\n_start:";
			break;
		}
		case 12:	//'PROCEDURE'
		{
			out_stream << queue_Quad.front().operand_1 << ":\tnop\n";
			break;
		}
		case 13:	//'>'
		{
			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			if (queue_Quad.front().operand_2.compare(0, 3, lit) == 0)
			{
				out_stream << "\tcmp ax, " << queue_Quad.front().operand_2.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tcmp ax, [" << queue_Quad.front().operand_2 << "]\n";
			}

			out_stream << "\tjle ";

			break;
		}
		case 14:	//'<'
		{
			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			if (queue_Quad.front().operand_2.compare(0, 3, lit) == 0)
			{
				out_stream << "\tcmp ax, " << queue_Quad.front().operand_2.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tcmp ax, [" << queue_Quad.front().operand_2 << "]\n";
			}

			out_stream << "\tjge ";

			break;
		}
		case 15:	//'>='
		{
			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			if (queue_Quad.front().operand_2.compare(0, 3, lit) == 0)
			{
				out_stream << "\tcmp ax, " << queue_Quad.front().operand_2.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tcmp ax, [" << queue_Quad.front().operand_2 << "]\n";
			}

			out_stream << "\tjl ";

			break;
		}
		case 16:	//'<='
		{
			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			if (queue_Quad.front().operand_2.compare(0, 3, lit) == 0)
			{
				out_stream << "\tcmp ax, " << queue_Quad.front().operand_2.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tcmp ax, [" << queue_Quad.front().operand_2 << "]\n";
			}

			out_stream << "\tjg ";

			break;
		}
		case 17:	//'!='
		{
			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			if (queue_Quad.front().operand_2.compare(0, 3, lit) == 0)
			{
				out_stream << "\tcmp ax, " << queue_Quad.front().operand_2.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tcmp ax, [" << queue_Quad.front().operand_2 << "]\n";
			}

			out_stream << "\tje ";

			break;
		}
		case 18:	//'=='
		{
			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			if (queue_Quad.front().operand_2.compare(0, 3, lit) == 0)
			{
				out_stream << "\tcmp ax, " << queue_Quad.front().operand_2.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tcmp ax, [" << queue_Quad.front().operand_2 << "]\n";
			}

			out_stream << "\tjne ";

			break;
		}
		case 19:	//'CALL'
		{
			out_stream << "\tcall " << queue_Quad.front().operand_1 << "\n";

			break;
		}
		case 20:	//'ODD'
		{
			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			out_stream << "\ttest al, 1\n" << "\tjz ";	//Is an even number, jump zero.

			break;
		}
		case 21:	//'READ'
		{
			out_stream << "\tcall PrintString\n"
				<< "\tcall GetAnInteger\n"
				<< "\tmov ax, [ReadInt]\n"
				<< "\tmov [" << queue_Quad.front().operand_1 << "], ax\n\n";

			break;
		}
		case 22:	//'WRITE'
		{
			if (queue_Quad.front().operand_1.compare(0, 3, lit) == 0)
			{
				out_stream << "\tmov ax, " << queue_Quad.front().operand_1.substr(3) << "\n";
			}
			else
			{
				out_stream << "\tmov ax, [" << queue_Quad.front().operand_1 << "]\n";
			}

			out_stream << "\tcall ConvertIntegerToString\n\n"
				<< "\tmov eax, 4\n"
				<< "\tmov ebx, 1\n"
				<< "\tmov ecx, Result\n"
				<< "\tmov edx, ResultEnd\n"
				<< "\tint 80h\n\n";

			break;
		}
		case 23:	//'PROC_LBRACK'
		{
			break;
		}
		case 24:	//'PROC_RBRACK'
		{
			out_stream << "\tret\n";

			break;
		}
		case 25:	//'EOF'
		{
			out_stream << "fini:\n"
				<< "\tmov eax, sys_exit\n"
				<< "\txor ebx, ebx\n"
				<< "\tint 80h\n\n";

			break;
		}
		}

		queue_Quad.pop_front();
	}

	addIO();

	cout << "The Assembly Language equivalent to the given code has been generated!";
	cout << endl;
}

/*
Function: addDSandBS
Parameters: (N/A)
Description: Using the PartialDS and PartialBS files derived
from "IO1NasmLinux32.asm", this function prints the .data
and .bss sections at the beginning Assembly program and prints
the constant, variable, and temporary values using the Symbol Table.
*/
void CodeGen::addDSandBS()
{
	/*String variable*/
	string line;

	/*Node pointer*/
	Node* node = SymTable->head;

	partDS.open("InputFiles/PartialDS.txt");	//Open the file.
	if (partDS.fail())	//Checks if opening was successful.
	{
		cout << "Error: The file, 'PartialDS.txt', could not be opened properly.";
		cout << endl;
		exit(EXIT_FAILURE);	//End program.
	}

	partBS.open("InputFiles/PartialBS.txt");	//Open the file.
	if (partBS.fail())	//Checks if opening was successful.
	{
		cout << "Error: The file, 'PartialBS.txt', could not be opened properly.";
		cout << endl;
		exit(EXIT_FAILURE);	//End program.
	}

	//Reads each line of the file and prints it to the new one.
	while (getline(partDS, line))
	{
		out_stream << line;
		out_stream << endl;
	}
	out_stream << endl;	//Puts a space between the two sections.

	//Reads each line of the file and prints it to the new one.
	while (getline(partBS, line))
	{
		out_stream << line;
		out_stream << endl;
	}

	//While a node.
	while (node)
	{
		//If the node is a '$CONST'
		if (node->token.TClass == "$CONST")
		{
			//Print 'DW' and its value.
			out_stream << "\t" << node->token.TString << "\tDW" << node->token.value;
			cout << endl;
		}

		//If the node is a '<var>' or a '<temp>'
		if (node->token.TClass == "<var>" || node->token.TClass == "<temp>")
		{
			//Print 'RESW 1'
			out_stream << "\t" << node->token.TString << "\tRESW 1";
			out_stream << endl;
		}

		node = node->next;
	}
}

/*
Function: addIO
Parameters: (N/A)
Description: Using the IORoutines file derived from
"IO1NasmLinux32.asm", this function prints the I/O
procedures section at the end of the Assembly program.
*/
void CodeGen::addIO()
{
	/*String variable*/
	string line;

	IOFile.open("InputFiles/IORoutines.txt");	//Open the file.
	if (IOFile.fail())	//Checks if opening was successful.
	{
		cout << "Error: The file, IORoutines.txt, could not be opened properly.";
		cout << endl;
		exit(EXIT_FAILURE);	//End program.
	}

	//Reads each line of the file and prints it to the new one.
	while (getline(IOFile, line))
	{
		out_stream << line;
		out_stream << endl;
	}
}

/*
Function: quadToInt
Parameters: (Quad qu)
Description: Produces a numeric value associated
with the operators supported by Java 0. Helps
locate the appropriate case in the genCode function.
*/
int CodeGen::quadToInt(Quad qu)
{
	if (qu.operation == "+")
	{
		return 0;
	}
	else if (qu.operation == "-")
	{
		return 1;
	}
	else if (qu.operation == "*")
	{
		return 2;
	}
	else if (qu.operation == "/")
	{
		return 3;
	}
	else if (qu.operation == "=")
	{
		return 4;
	}
	else if (qu.operation == "IF")
	{
		return 5;
	}
	else if (qu.operation == "THEN")
	{
		return 6;
	}
	else if (qu.operation.at(0) == 'L' && isdigit(qu.operation.at(1)))
	{
		return 7;
	}
	else if (qu.operation == "WHILE")
	{
		return 8;
	}
	else if (qu.operation == "DO")
	{
		return 9;
	}
	else if (qu.operation.at(0) == 'W' && isdigit(qu.operation.at(1)))
	{
		return 10;
	}
	else if (qu.operation == "CLASS")
	{
		return 11;
	}
	else if (qu.operation == "PROCEDURE")
	{
		return 12;
	}
	else if (qu.operation == ">")
	{
		return 13;
	}
	else if (qu.operation == "<")
	{
		return 14;
	}
	else if (qu.operation == ">=")
	{
		return 15;
	}
	else if (qu.operation == "<=")
	{
		return 16;
	}
	else if (qu.operation == "!=")
	{
		return 17;
	}
	else if (qu.operation == "==")
	{
		return 18;
	}
	else if (qu.operation == "CALL")
	{
		return 19;
	}
	else if (qu.operation == "ODD")
	{
		return 20;
	}
	else if (qu.operation == "READ")
	{
		return 21;
	}
	else if (qu.operation == "WRITE")
	{
		return 22;
	}
	else if (qu.operation == "PROC_LBRACK")
	{
		return 23;
	}
	else if (qu.operation == "PROC_RBRACK")
	{
		return 24;
	}
	else if (qu.operation == "EOF")
	{
		return 25;
	}
	else
	{
		return -1;
	}
}