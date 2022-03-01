/*
============================================================================
Name: Homework4.cpp
Author: Christopher R. McDaniel
Date: 25 November 2019
Class: COSC 2347
Version: 1.1
Copyright: 2019
Description: This is a program that will label and count the number of
objects in a given image. Each image consists of a number of pixels,
and initially all pixels will have one of two labels, 0 and 1. 0 is
considered a background pixel while a 1 represents a pixel that is
part of an object. The program will apply, over multiple iterations, the
same label to pixels that are connected to form objects, and then count
the number of objects for a given image.
============================================================================
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <math.h>
#include <cstdlib>
#include <vector>

using namespace std;

//Declare void functions.
void MyInfo();
void Display(vector<int>, int);
void Print(vector<vector<int>>, int, int, int);
void Check(vector<vector<int>>, int);

//Declare vector fucntion.
vector<vector<int>> MatrixCreate(vector<int>, int);

//Declare main function.
int main();

/*
============================================================================
Function: MyInfo
Parameters: (N/A)
Return: My Info
Description: Prints out my information.
============================================================================
*/
void MyInfo()
{
	//Displays my information
	cout << "\n\n";
	cout << " *************************************************************\n"; //Border
	cout << "|      Department: COSC 2347 - Special Topics/Programming     |\n"; //Prints Department and course number
	cout << "|                  Name: Christopher McDaniel                 |\n"; //Prints my name
	cout << "|         SamID: 000652957     E-mail: crm089@shsu.edu        |\n"; //Prints my SamID and my E-mail address
	cout << " *************************************************************\n"; //Border
	cout << "\n\n";
}

/*
============================================================================
Function: main
Parameters: (N/A)
Return: Program output
Description: This function takes a user given file and add it into a vector
if it is a file. (input.txt)
============================================================================
*/
int main()
{
	//Declare variables.
	ifstream in_stream;		//Input file stream variable
	char input[30]; //Filename storage.
	char ch;	//Reads in bit.
	int bit, lines;

	//Declare vector.
	vector<int> image;	//Input vector.

	MyInfo();	//Displays my info.

	//Get input filename.
	cout << "Enter the filename of the file that has the image: "; //Ask for user input.
	cin >> input; //User input.

	in_stream.open(input); //Open file
	if (in_stream.fail()) //Checks if opening was successful
	{
		cout << "Error opening input file!" << endl;
		exit(EXIT_FAILURE);	//End program.
	}

	else
	{
		while (!in_stream.eof())	//Will only store the pixels.
		{
			in_stream.get(ch);

			if (isdigit(ch))	//If the character is a digit, push it into the vector.
			{
				bit = int(ch) - 48;	//Convert from ASCII.
				image.push_back(bit);	//Add element at the end of the vector.
			}
		}

		in_stream.close();	//Close file.
	}

	lines = sqrt(image.size());	//Square root fo the image return size.

	vector<vector<int>> MatrixImg(lines, vector<int>(lines, 0));

	MatrixImg = MatrixCreate(image, lines);	//The 2D vector

	Check(MatrixImg, lines);	//Pass values into Check function.
}

/*
============================================================================
Function: Display
Parameters: (out_stream, arrValues, ValNum)
Return: Void
Description: This function will find the number of objects within the user
given image, then prints the vector (vector<char>) into the user given
output file.
============================================================================
*/
void Display(vector<int> arrValues, int RowNum)
{
	//Declare variables
	int k;

	for (k = 0; k < arrValues.size(); k++)	////k is less than the arrValues return size.
	{
		if (k % RowNum == 0)	//Will display the image within the line.
		{
			cout << "\n";	//Print new line.
		}

		cout << arrValues.at(k) << ' ';
	}
}

/*
============================================================================
Function: MatrixCreate
Parameters: (in, RowNum)
Return: matrix
Description: This function will store the data in the user given file
into a vector matrix for later use.
============================================================================
*/
vector<vector<int>> MatrixCreate(vector<int> in, int RowNum)
{
	//Declare vector matrix.
	vector<vector<int>> matrix(RowNum, vector<int>(RowNum, 0));

	//Declare variables.
	int knt = 0;
	int i, x;

	//Store file into a matrix
	for (i = 0; i < RowNum; i++)
	{
		for (x = 0; x < RowNum; x++)
		{
			matrix[x][i] = in[knt];
			knt++;	//Increment knt.
		}
	}

	return matrix;	//return matrix to be used in another function.
}

/*
============================================================================
Function: Print
Parameters: (matrix, RowNum, Label, Big)
Return: Void
Description: This function will print the results of the program into a
user given output file. (output.txt)
============================================================================
*/
void Print(vector<vector<int>> matrix, int RowNum, int Label, int Big)
{
	//Declare variables.
	ofstream out_stream;	//Output file stream variable.
	char output[20];
	int i, x;

	//Get output filename.
	cout << "Enter the filename of the file the new image will be output to: "; //Ask for user input.
	cin >> output; //User input.


	out_stream.open(output);	//Opens output file.
	if (out_stream.fail())	//Checks if file opening failed.
	{
		cout << "Error opening output file!" << endl;
		exit(EXIT_FAILURE);	//End program.
	}

	for (i = 0; i < RowNum; i++)
	{
		for (x = 0; x < RowNum; x++)
		{
			out_stream << matrix[x][i] << " ";	//Prints matrix into file.
		}

		out_stream << "\n";	//Prints a new line in file.
	}

	//Prints results.
	out_stream << "-------------------------------------------" << "\n";
	out_stream << "The number of objects in the image: " << Label << "\n";
	out_stream << "The largest object in the image has a length of: " << Big << "(BONUS)." << "\n";
	out_stream << "\n";
}

/*
============================================================================
Function: Check
Parameters: (matrix, RowNum)
Return: Void
Description: This function will perform the first pass and cases, then the
second pass then send results into the Print function to be printed into an
output file.

--Case 1: If the top and left pixels are background pixels or do not exist,
create a new label.

--Case 2: If one is a background pixel or does not exist and the other has
a label, the current pixel will be labeled the same as the labeled pixel.

--Case 3: If both the above and left pixels have different labels, assign
the current pixel the smallest label and store that there is a relationship
between the two labels. This will be used in the second pass.
============================================================================
*/
void Check(vector<vector<int>> matrix, int RowNum)
{
	//Declare variables
	vector<int> compare;	//Compares the vectors.
	vector<int> replace;	//Replaces the vectors.
	bool check = true;	//Sets boolean value, check, to true.
	int Big = 0;	//Sets Big to 0.
	int Label = 0;	//Sets Label to 0.
	int i, x, k;	//i and x are above and left pixels.

	//First pass.
	for (i = 0; i < RowNum; i++)
	{
		for (x = 0; x < RowNum; x++)
		{
			//Case 1: If the top and left pixels are background
			//pixels or do not exist, create a new label
			if (matrix[x][i] != 0)	//Value is not a background pixel.
			{
				if (((x - 1) >= 0) && ((i - 1) >= 0))	//Check index.
				{
					//Case 2: If one is a background pixel or does not
					//exist and the other has a label, the current pixel will
					//be labeled the same as the labeled pixel
					if ((matrix[x - 1][i] > 0) && (matrix[x][i - 1] > 0))	//Checks for if matrix is greater than 0.
					{
						//Case 3: If both the above and left pixels have different labels,
						//assign the current pixel the smallest label and store that there
						//is a relationship between the two labels.This will be used in the
						//second pass.
						if (matrix[x - 1][i] != matrix[x][i - 1]) //The values are not the same.
						{
							if (matrix[x - 1][i] > matrix[x][i - 1]) //Label is lower.
							{
								for (k = 0; k < compare.size(); k++)	//k is less than the compare return size.
								{
									if (matrix[x - 1][i] == compare[k])
									{
										check = false;	//Check is false.
										break;	//Terminates loop.
									}
								}

								if (check)
								{
									compare.push_back(matrix[x - 1][i]);	//Add element at the end of the vector.
									replace.push_back(matrix[x][i - 1]);	//Add element at the end of the vector.
								}

								check = true;
								matrix[x][i] = matrix[x][i - 1];
							}
							else
							{
								for (k = 0; k < compare.size(); k++)	//k is less than the compare return size.
								{
									if (matrix[x][i - 1] == compare[i])
									{
										check = false;	//Check is false.
										break;	//Terminates loop.
									}
								}

								if (check)
								{
									compare.push_back(matrix[x][i - 1]);	//Add element at the end of the related vector.
									replace.push_back(matrix[x - 1][i]);	//Add element at the end of the related vector.
								}

								check = true;
								matrix[x][i] = matrix[x - 1][i];
							}
						}
						else	//The values are the same.
						{
							matrix[x][i] = matrix[x - 1][i];
						}
					}

					//x is a label, i is NOT a label.
					if ((matrix[x - 1][i] > 0) && (matrix[x][i - 1] == 0))
					{
						matrix[x][i] = matrix[x - 1][i];
					}

					//x is NOT a label, i is a label.
					if ((matrix[x - 1][i] == 0) && (matrix[x][i - 1] > 0))
					{
						matrix[x][i] = matrix[x][i - 1];
					}

					//x is NOT a label, and i is NOT a label.
					if ((matrix[x - 1][i] == 0) && (matrix[x][i - 1] == 0))
					{
						Label++;	//Increment Label.
						matrix[x][i] = Label;	//Set matrix to Label.
					}
				}

				//If x exists, and y does not exist.
				else if (((x - 1) >= 0) && ((i - 1) < 0))
				{
					if (matrix[x - 1][i] > 0)
					{
						matrix[x][i] = matrix[x - 1][i];
					}
					else
					{
						Label++;	//Increment Label.
						matrix[x][i] = Label;	//Set matrix to Label.
					}
				}

				//If x does not exist, and y exists.
				else if (((x - 1) < 0) && ((i - 1) >= 0))
				{
					if (matrix[x][i - 1] > 0)
					{
						matrix[x][i] = matrix[x][i - 1];
					}
					else
					{
						Label++;	//Increment Label.
						matrix[x][i] = Label;	//Set matrix to Label.
					}
				}

				//Both x and y do not exist within the matrix.
				else
				{
					Label++;	//Increment Label.
					matrix[x][i] = Label;	//Set matrix to Label.
				}
			}
		}
	}

	//Second pass.
	//Could not get the second pass to work for some reason....
	//for (i = 0; i < RowNum; i++)
	//{
	//	for (x = 0; x < RowNum; x++)
		//{
		//	for (k = 0; k < compare.size(); k++)	//k is less than the compare return size.
			//{
				//Once this is uncommented it throw this error:
				//Unhandled exception at 0x7BBFF2F6 (ucrtbased.dll) in Homework 4.exe:
				//An invalid parameter was passed to a function that considers invalid parameters fatal.
			//	if (matrix[x][i] == compare[i])
			//	{
			//		matrix[x][i] = replace[i];
			//	}
			//}
		//}
	//}

	Label = Label - compare.size();	//Labels new value is Label - compare return size.
		
	compare.clear();	//Clear contents of the related vector.
	replace.clear();	//Clear contents of the related vector.

	for (k = 1; k < Label; k++)
	{
		compare.push_back(k);	//Add element at the end of the related vector.
		replace.push_back(0);	//Add element at the end of the related vector.
	}

	//BONUS
	//Count the number of pixels in the image.
	for (i = 0; i < RowNum; i++)
	{
		for (x = 0; x < RowNum; x++)
		{
			for (k = 0; k < compare.size(); k++)
			{
				if (matrix[x][i] == compare[k])
				{
					replace[k] = (replace[k] + 1);	//Increment by 1.
				}
			}
		}
	}

	for (k = 0; k < replace.size(); k++)
	{
		if (replace[k] > Big)
		{
			Big = replace[k];	//Set Big to equal replace[k].
		}
	}



	Print(matrix, RowNum, Label, Big);	//Pass values into Print function.
}