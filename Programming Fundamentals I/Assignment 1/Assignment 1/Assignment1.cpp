// Assignment1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "Assignment1.h"

using namespace std;


int main()
{
	double pi = 3.141592653589793238463;
	double radius = 0;
	double area = 0;

	cout << "This program will calculate\n"
		"the area of a circle\n"
		"(c) 2017 Christopher McDaniel\n\n";

	cout << "Enter Radius: ";
	cin >> radius;
	cout << endl;

	area = pi * (radius * radius);

	cout << "Area: " << area << endl;
	cout << endl;

	system("Pause");

    return 0;
}

