//Christopher McDaniel, SamID: 000652957
//6 September 2019
//COSC 2347
//This program will calculate the effect gravity has on a projectile

#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <time.h>
#include <math.h>
using namespace std;

//Formulas
//Function for amount of Time Taken to impact ground
void TimeTaken(float a, float b, float c)
{
	//Result will be stored in time
	double time;

	//Function that calculates the time it is taken for the object to impact the ground
	//disc = Discriminant of quadratic
	double disc = sqrt((b * b) - (4 * a * c)); //Discriminant formula

	double x1 = ((-b + disc) / (2 * a)); //Calculation for first root

	if (disc > 0) //Checks first root to see if it is a positive number
	{
		time = x1;	//Sets x1 equal to time
	}

	else if (disc < 0); //If negative calculate second root
	{
		double x2 = ((-b - disc) / (2 * a)); //Calculates second root

		if (disc > 0) //Checks to see if positive
		{
			time = x2;	//Sets x2 equal to time
		}
	}

	cout << "Answers\n";
	cout << setprecision(2) << fixed << "The projectile will take " << time << " seconds to hit the ground\n"; //Output for time it takes projectile to impact ground
	cout << "\n";
}

//Function for Max Height of object
void MaxHeight(float a, float b, float c)
{
	double max; //Storage for the result
	double vertex; //Highest point of object
	vertex = (-b / (2 * a)); //Calculates the highest point of the object

	max = (a * (vertex * vertex) + b * vertex + c); //Calculates the max height achieved by the object

	cout << setprecision(2) << fixed << "The maximum height the object will reach is " << max << " feet.\n"; //Output for maximum height
}

int main() //Main function
{
	//Displays my information
	cout << "\n";
	cout << "\n";
	cout << " *************************************************************\n";
	cout << "|      Department: COSC 2347 - Special Topics/Programming     |\n"; //Prints Department and course number
	cout << "|                  Name: Christopher McDaniel                 |\n"; //Prints my name
	cout << "|         SamID: 000652957     E-mail: crm089@shsu.edu        |\n"; //Prints my SamID and my E-mail address
	cout << " *************************************************************\n";
	cout << "\n";
	cout << "\n";

	//Variable names
	float GravConst = -16; //Gravitational constant
	float IniHt; //Initial Height
	float IniVel; //Initial Velocity

	//Variable inputs
	cout << "Enter the initial velocity (v0) in feet/seconds: "; //Asking for input for initial velocity
	cin >> IniVel;		//Input for initial velocity
	cout << "\n";
	cout << "Enter initial height of (s0) in feet: "; //Asking for input for initial height
	cin >> IniHt;		//Input for initial height
	cout << "\n";
	cout << "\n";

	TimeTaken(GravConst, IniVel, IniHt);
	MaxHeight(GravConst, IniVel, IniHt);
}