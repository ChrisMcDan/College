//Christopher McDaniel Cylinder Program
//Object Intro.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>

using namespace std;

class Cylinder {

public:
	double height;	  //height of cylinder
	double radius;	  //radius of cylinder
	double pi;
};

int main() {
	Cylinder Cylinder1;      //Declare Cylinder1 of type Cylinder
	Cylinder Cylinder2;      //Declare Cylinder2 of type Cylinder
	double volume = 0.0;     //Store the volume of a box here

	//Cylinder 1 specs
	Cylinder1.height = 10;
	Cylinder1.radius = 6;
	Cylinder1.pi = 3.1415;

	//Cylinder 2 specs
	Cylinder2.height = 15;
	Cylinder2.radius = 10;
	Cylinder2.pi = 3.1415;

	//Volume of Cylinder 1
	volume = Cylinder1.pi * (Cylinder1.radius * Cylinder1.radius) * Cylinder1.height;
	cout << "Volume of Cylinder 1: " << volume << endl;

	//Volume of Cylinder 2
	volume = Cylinder2.pi * (Cylinder2.radius * Cylinder2.radius) * Cylinder2.height;
	cout << "Volume of Cylinder 2: " << volume << endl;

	system("pause");

	return 0;
}