// Christopher McDaniel
// TaxAppPhase10.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void MainMenu();
double CalcFedTax(int, double, double, double[], double[], double[]);

int main()
{
	//variables
	int dependents = 0;
	double grossPay = 0;
	double taxablePay = 0;
	double withholding = 0;
	int mStatus = 0;
	int payPeriod = 0;
	string clientFName = " ";
	string clientLName = " ";

	//constants
	double const SSPCT = 0.062;
	double const MEDPCT = 0.0145;
	double const BWith = 155.80;
	double const MWith = 337.50;

	double fedTax = 0;
	double ssTax = 0;
	double medTax = 0;
	double netPay = 0;

	//array
	double SBBase[8] = { 0, 0, 35.90, 201.05, 719.80, 1794.16, 4650.31, 4673.41 };
	double SBMax[8] = { 88, 447, 1548, 3623, 7460, 16115, 16181, 0 };
	double SBPct[8] = { 0, 0.10, 0.15, 0.25, 0.28, 0.33, 0.35, 0.396 };

	double MBBase[8] = { 0, 0, 71.70, 402, 1144.25, 2008.61, 4335.77, 5062.72 };
	double MBMax[8] = { 333, 1050, 3252, 6221, 9308, 16360, 18437, 0 };
	double MBPct[8] = { 0, 0.10, 0.15, 0.25, 0.28, 0.33, 0.35, 0.396 };

	double SMBase[8] = { 0, 0, 77.70, 435.45, 1559.45, 3887.09, 10075.91, 10125.26 };
	double SMMax[8] = { 192, 969, 3354, 7850, 16163, 34917, 35058, 0 };
	double SMPct[8] = { 0, 0.10, 0.15, 0.25, 0.28, 0.33, 0.35, 0.396 };

	double MMBase[8] = { 0, 0, 155.40, 871.05, 2479.30, 4351.94, 9394.01, 10969.01 };
	double MMMax[8] = { 721, 2275, 7046, 13479, 20167, 35446, 39946, 0 };
	double MMPct[8] = { 0, 0.10, 0.15, 0.25, 0.28, 0.33, 0.35, 0.396 };

	int choice = 0;

	MainMenu();
	cin >> choice;

	while (choice != 0)
	{
		switch (choice)
		{
		case 1:

			//input
			cout << endl;
			cout << "What's your first name?: ";
			cin >> clientFName; 
			cout << endl;
			cout << "what's your last name?: ";
			cin >> clientLName;
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

					fedTax = CalcFedTax(dependents, BWith, grossPay, SBBase, SBMax, SBPct);

				}
				else   //monthly
				{
					if (payPeriod == 1)
					{

						fedTax = CalcFedTax(dependents, MWith, grossPay, SMBase, SMMax, SMPct);

					}
				}
			}
			if (mStatus == 1)	// married
			{
				if (payPeriod == 0)   // biweekly
				{

					fedTax = CalcFedTax(dependents, BWith, grossPay, MBBase, MBMax, MBPct);

				}
				else    //monthly
				{
					if (payPeriod == 1)    //monthly
					{

						fedTax = CalcFedTax(dependents, MWith, grossPay, MMBase, MMMax, MMPct);

					}
				}
			}

			ssTax = grossPay * SSPCT;
			medTax = grossPay * MEDPCT;
			netPay = grossPay - fedTax - ssTax - medTax;

			//output
			cout << endl;
			cout << "This is the paycheck description for " << clientFName << " " << clientLName << endl;
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

double CalcFedTax(int dep, double withDepAmt, double grossPay, double Base[], double Max[], double Pct[])
{

	double withholding = 0;
	double taxablePay = 0;
	double fedTax = 0;

	withholding = dep * withDepAmt;
	taxablePay = grossPay - withholding;

	if (taxablePay <= Max[0])   //Level 1
	{
		fedTax = 0;
	}
	else if (taxablePay <= Max[1])    //Level 2
	{
		fedTax = Base[1] + (Pct[1] * (taxablePay - Max[0]));
	}
	else if (taxablePay <= Max[2])    //Level 3
	{
		fedTax = Base[2] + (Pct[2] * (taxablePay - Max[1]));
	}
	else if (taxablePay <= Max[3])    //Level 4
	{
		fedTax = Base[3] + (Pct[3] * (taxablePay - Max[2]));
	}
	else if (taxablePay <= Max[4])    //Level 5
	{
		fedTax = Base[4] + (Pct[4] * (taxablePay - Max[3]));
	}
	else if (taxablePay <= Max[5])    //Level 6
	{
		fedTax = Base[5] + (Pct[5] * (taxablePay - Max[4]));
	}
	else if (taxablePay <= Max[6])    //Level 7
	{
		fedTax = Base[6] + (Pct[6] * (taxablePay - Max[5]));
	}
	else    //Level 8
	{
		fedTax = Base[7] + (Pct[7] * (taxablePay - Max[6]));
	}

	return fedTax;
}