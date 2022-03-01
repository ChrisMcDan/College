/*
============================================================================
Name: Homework3.cpp
Author: Christopher R. McDaniel
Date: 9 November 2019
Class: COSC 2347
Version: 1.1
Copyright: 2019
Description: Program to take user input for a file, read the file, then
encrypt or decrypt said file into a user given output file using a user
provided key.
============================================================================
*/

#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <ctype.h>
#include <cstdlib>

using namespace std;

int User_Choice();
void encrypt(ifstream& in_stream, ofstream& out_stream, int& key);
void decrypt(ifstream& in_stream, ofstream& out_stream, int& key);

/*
============================================================================
Function: encrypt
Parameters: (ifstream) for in_stream, (ofstream) for out_stream, and int key.
Return: (void)
Description: Asks for user input of file and encrypts data within input file and
puts it in a user specified output file.
============================================================================
*/
void encrypt(ifstream& in_stream, ofstream& out_stream, int& key)
{
	//Declaration of variables
	char key1, key2, key3, key4, key5;
	char sum;
	char plain[26], cipher[26], next;

	cout << "Enter the filename of the file that is being encrypted: "; //Ask for user input
	cin >> plain; //User input

	in_stream.open(plain); //Open file
	if (in_stream.fail()) //Checks if opening was successful
	{
		cout << "Error opening plaintext file!" << endl;
		exit(1);
	}

	cout << "Enter the filename of the file that the cipher is being written to: "; //Ask for user input
	cin >> cipher; //User input

	out_stream.open(cipher); //Open file
	if (out_stream.fail()) //Checks if opening was successful
	{
		cout << "Error opening ciphertext file!" << endl;
		exit(1);
	}

	cout << "Enter your 5-letter key: "; //Ask for user input
	cin >> key; //User input

	in_stream.get(next);

	while (!in_stream.eof()) //Test for End of File
	{
		//if (!isspace(next)) //Checks for whitespace
		
			if (isalpha(next)) //Checks for alphabet
			{
				if (isupper(next)) //Checks for uppercase letters
				{
					sum = ((next - 65 + key) % 26) + 65;
					out_stream.put(sum);
				}
				else if (islower(next)) //Checks for lowercase letters
				{
					sum = ((next - 97 + key) % 26) + 97;
					out_stream.put(sum);
				}
			}
			if (isdigit(next)) //Checks for digit
			{
				sum = ((next - 48 + key) % 10) + 48;
				out_stream.put(sum);
			}
		
		in_stream.get(next);
	}

	cout << "Encrypted!" << endl << endl;
}

/*
============================================================================
Function: decrypt
Parameters: (ifstream) for in_stream, (ofstream) for out_stream, and int key.
Return: (void)
Description: Asks for user input of file and decrypts data within input file and
puts it in a user specified output file.
============================================================================
*/
void decrypt(ifstream& in_stream, ofstream& out_stream, int& key)
{
	//Declaration of variables
	char sum;
	char decrypt[26], encrypt[26], next;

	cout << "Enter the filename of the file that is being decrypted: "; //Ask for user input
	cin >> encrypt; //User input

	in_stream.open(encrypt); //Open file
	if (in_stream.fail()) //Checks if opening was successful
	{
		cout << "Error opening encrypted file!" << endl;
		exit(1);
	}

	cout << "Enter the name of the file the plaintext will be written to: "; //Ask for user input
	cin >> decrypt; //User input

	out_stream.open(decrypt); //Open file
	if (out_stream.fail()) //Checks if opening was successful
	{
		cout << "Error opening decrypted file!" << endl;
		exit(1);
	}

	cout << "Enter your 5-letter key: "; //Ask for user input
	cin >> key; //User input

	in_stream.get(next);
	while (!in_stream.eof()) //Test for End of File
	{
		//if (!isspace(next)) //Checks for whitespace
		
			if (isalpha(next)) //Checks for alphabet
			{
				if (isupper(next)) //Checks for uppercase letters
				{
					sum = ((next - 65 + 26 - key) % 26) + 65;
					out_stream.put(sum);
				}
				else if (islower(next)) //Checks for lowercase letters
				{
					sum = ((next - 97 + 26 - key) % 26) + 97;
					out_stream.put(sum);
				}
			}
			if (isdigit(next)) //Checks for digit
			{
				sum = ((next - 48 - key + 10 * 10) % 10) + 48;
				out_stream.put(sum);
			}
		
		in_stream.get(next);
	}

	cout << "Decrypted!" << endl << endl;
}

/*
============================================================================
Function: main
Parameters: (N/A)
Return: Program output
Description: Prints my information and results from the program being ran.
============================================================================
*/
int main()
{
	//Declaration of variables
	ifstream in_stream;
	ofstream out_stream;
	int key;
	int choice;

	//Displays my information
	cout << "\n\n";
	cout << " *************************************************************\n"; //Border
	cout << "|      Department: COSC 2347 - Special Topics/Programming     |\n"; //Prints Department and course number
	cout << "|                  Name: Christopher McDaniel                 |\n"; //Prints my name
	cout << "|         SamID: 000652957     E-mail: crm089@shsu.edu        |\n"; //Prints my SamID and my E-mail address
	cout << " *************************************************************\n"; //Border
	cout << "\n\n";

	//Selects User_Choice
	choice = User_Choice(); //Calls User_Choice function

	//Uses user input to decide which function to use
	while (choice > 1 || choice < 3)
	{
		if (choice == 1) //Encrypt
		{
			encrypt(in_stream, out_stream, key); //Calls Encryption function
		}
		else if (choice == 2) //Decrypt
		{
			decrypt(in_stream, out_stream, key); //Calls Decryption function
		}
		else if (choice == 3) //Exit
		{
			break;
		}
	}

	in_stream.close(); //Closes the open file
	out_stream.close(); //Closes the open file

	return 0;
}

/*
============================================================================
Function: User_Choice
Parameters: (N/A)
Return: choice
Description: Asks for user to decide what they want to do and checks to
ensure user provided value is valid.
============================================================================
*/
int User_Choice()
{
	//Declaration of variables
	int choice;

	//Menu
	cout << "To ENCRYPT press 1, DECRYPT press 2, and EXIT press 3: "; //Asks for user input
	cin >> choice; //User input

	//Checks for valid user input
	while (choice < 1 || choice > 3)
	{
		cout << "Please enter a valid number (1, 2, or 3): ";	//Asks user for valid input
		cin >> choice;	//Re-enter user input
	}

	return choice;
}

//Switch statement for each character in the key
int 1()
{
	switch
}