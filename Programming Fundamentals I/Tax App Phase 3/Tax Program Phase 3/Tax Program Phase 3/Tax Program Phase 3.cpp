// Christopher McDaniel
// TaxAppPhase10.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

void MainMenu();
double CalcFedTax(int, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);

int main()
{
	//variables
	int dependents = 0;
	double grossPay = 0;
	double taxablePay = 0;
	double withholding = 0;
	int mStatus = 0;
	int payPeriod = 0;

	double const SSPCT = 0.062;
	double const MEDPCT = 0.0145;

	double fedTax = 0;
	double ssTax = 0;
	double medTax = 0;
	double netPay = 0;

	int choice = 0;

	MainMenu();
	cin >> choice;

	while (choice != 0)
	{
		switch (choice)
		{
		case 1:
			//input

			cout << "Tax Calculator" << endl;
			cout << endl;
			cout << "Are you married? (0=no, 1=yes): ";
			cin >> mStatus;
			cout << endl;
			cout << "What is your Pay Period? (0=biweekly, 1=monthly): ";
			cin >> payPeriod;
			cout << endl;
			cout << "Number of Dependents? ";
			cin >> dependents;
			cout << endl;
			cout << "What is your Gross Pay per Pay Period? ";
			cin >> grossPay;
			cout << endl;

			//processing

			if (mStatus == 0)    // single
			{
				if (payPeriod == 0)   // biweekly
				{

					fedTax = CalcFedTax(dependents, 155.80, grossPay, 88, 447, 1548, 3623, 7560, 16115, 16181, 0, 35.90, 201.05, 719.80, 1794.16, 4650.31, 4673.41, .10, .15, .25, .28, .33, .35, .396);
				
				}
				else   //monthly
				{

					fedTax = CalcFedTax(dependents, 337.50, grossPay, 192, 969, 3354, 7850, 16163, 34917, 35058, 0, 77.70, 435.45, 1559.45, 3887.09, 10075.91, 10125.26, .10, .15, .25, .28, .33, .35, .396);

				}
			}
			if (mStatus == 1)	// married
			{
				if (payPeriod == 0)   // biweekly
				{

					fedTax = CalcFedTax(dependents, 155.80, grossPay, 333, 1050, 3252, 6221, 9308, 16360, 18437, 0, 71.70, 402, 1144.25, 2008.61, 4335.77, 5062.72, .10, .15, .25, .28, .33, .35, .396);

				}
				else    //monthly
				{
					if (payPeriod == 1)    //monthly
					{

						fedTax = CalcFedTax(dependents, 337.50, grossPay, 721, 2275, 7046, 13479, 20167, 35446, 39946, 0, 155.40, 871.05, 2479.30, 4351.94, 9394.01, 10969.01, .10, .15, .25, .28, .33, .35, .396);

					}
				}
			}

			ssTax = grossPay * SSPCT;
			medTax = grossPay *  MEDPCT;
			netPay = grossPay - fedTax - ssTax - medTax;

			//output

			cout << endl;
			cout << setprecision(2) << fixed;
			cout << "Fed Tax: " << fedTax << endl;
			cout << "SS Tax: " << ssTax << endl;
			cout << "Med Tax: " << medTax << endl;
			cout << "Net Pay: " << netPay << endl;

			system("pause");
			break;

		default:
			cout << "Please Choose an Available Option!!" << endl;
			system("pause");
			break;

		}

		MainMenu();
		cin >> choice;
	}

	return 0;
}

void MainMenu()
{

	system("cls");
	//Menu input
	cout << "Tax Calculator" << endl;
	cout << endl;
	cout << "1. Calculate Tax" << endl;
	cout << endl;
	cout << "0. Exit" << endl;
	cout << endl;
	cout << "Enter Choice: "; 
}

double CalcFedTax(int dep, double withDepAmt, double grossPay, double L1Max, double L2Max, double L3Max, double L4Max, double L5Max, double L6Max, double L7Max, double L2Base, double L3Base, double L4Base, double L5Base, double L6Base, double L7Base, double L8Base, double L2Pct, double L3Pct, double L4Pct, double L5Pct, double L6Pct, double L7Pct, double L8Pct)
{

	double withholding = 0;
	double taxablePay = 0;
	double fedTax = 0;

	withholding = dep * withDepAmt;
	taxablePay = grossPay - withholding;

	if (taxablePay <= L1Max)   //Level 1
	{
		fedTax = 0;
	}
	else if (taxablePay <= L2Max)    //Level 2
	{
		fedTax = L2Base + (L2Pct * (taxablePay - L1Max));
	}
	else if (taxablePay <= L3Max)    //Level 3
	{
		fedTax = L3Base + (L3Pct * (taxablePay - L2Max));
	}
	else if (taxablePay <= L4Max)    //Level 4
	{
		fedTax = L4Base + (L4Pct * (taxablePay - L3Max));
	}
	else if (taxablePay <= L5Max)    //Level 5
	{
		fedTax = L5Base + (L5Pct * (taxablePay - L4Max));
	}
	else if (taxablePay <= L6Max)    //Level 6
	{
		fedTax = L6Base + (L6Pct * (taxablePay - L5Max));
	}
	else if (taxablePay <= L7Max)    //Level 7
	{
		fedTax = L7Base + (L7Pct * (taxablePay - L6Max));
	}
	else    //Level 8
	{
		fedTax = L8Base + (L8Pct * (taxablePay - L7Max));
	}

	return fedTax;
}