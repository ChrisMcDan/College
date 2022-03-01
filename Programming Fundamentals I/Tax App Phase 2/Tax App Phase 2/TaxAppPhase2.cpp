// Christopher McDaniel
// TaxAppPhase10.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	//variables
	int dependents = 0;
	double grossPay = 0;
	double taxablePay = 0;
	double witholding = 0;
	int mStatus = 0;
	int payPeriod = 0;

	double const SSPCT = 0.062;
	double const MEDPCT = 0.0145;

	double fedTax = 0;
	double ssTax = 0;
	double medTax = 0;
	double netPay = 0;

	int choice = 0;

	//Menu input
	cout << "Tax Calculator" << endl;
	cout << endl;
	cout << "1. Calculate Tax" << endl;
	cout << endl;
	cout << "0. Exit" << endl;
	cout << endl;
	cout << "Enter Choice: ";
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
						witholding = dependents * 155.80;
						taxablePay = grossPay - witholding;

						if (taxablePay <= 88)   //Level 1
						{
							fedTax = 0;
						}
						else if (taxablePay > 88 && taxablePay <= 447)    //Level 2
						{
							fedTax = 0 + (0.10 * (taxablePay - 88));
						}
						else if (taxablePay > 447 && taxablePay <= 1548)    //Level 3
						{
							fedTax = 35.90 + (0.15 * (taxablePay - 447));
						}
						else if (taxablePay > 1548 && taxablePay <= 3623)    //Level 4
						{
							fedTax = 201.05 + (0.25 * (taxablePay - 1548));
						}
						else if (taxablePay > 3623 && taxablePay <= 7460)    //Level 5
						{
							fedTax = 719.80 + (0.28 * (taxablePay - 3623));
						}
						else if (taxablePay > 7460 && taxablePay <= 16115)    //Level 6
						{
							fedTax = 1794.16 + (0.33 * (taxablePay - 7460));
						}
						else if (taxablePay > 16115 && taxablePay <= 16181)    //Level 7
						{
							fedTax = 4650.31 + (0.35 * (taxablePay - 16115));
						}
						else if (taxablePay > 16181)    //Level 8
						{
							fedTax = 4673.41 + (0.396 * (taxablePay - 16181));
						}
					}
					else    //monthly
					{
						if (payPeriod == 1)    //monthly
						{
							witholding = dependents * 337.50;
							taxablePay = grossPay - witholding;

							//include tax bracket for single/monthly

							if (taxablePay <= 192)     //Level 1
							{
								fedTax = 0;
							}

							else if (taxablePay > 192 && taxablePay <= 969)    //Level 2
							{
								fedTax = 0 + (0.10 * (taxablePay - 192));
							}
							else if (taxablePay > 969 && taxablePay <= 3354)    //Level 3
							{
								fedTax = 77.70 + (0.15 * (taxablePay - 969));
							}
							else if (taxablePay > 3354 && taxablePay <= 7850)    //Level 4
							{
								fedTax = 435.45 + (0.25 * (taxablePay - 3354));
							}
							else if (taxablePay > 7850 && taxablePay <= 16163)    //Level 5
							{
								fedTax = 1559.45 + (0.28 * (taxablePay - 7850));
							}
							else if (taxablePay > 16163 && taxablePay <= 34917)    //Level 6
							{
								fedTax = 3887.09 + (0.33 * (taxablePay - 16163));
							}
							else if (taxablePay > 34917 && taxablePay <= 35058)    //Level 7
							{
								fedTax = 10075.91 + (0.35 * (taxablePay - 34917));
							}
							else if (taxablePay > 35058)    //Level 8
							{
								fedTax = 10125.26 + (0.396 * (taxablePay - 35058));
							}
						}
					}
				}
				if (mStatus == 1)
				{
					if (payPeriod == 0)   // biweekly
					{
						witholding = dependents * 155.80;
						taxablePay = grossPay - witholding;

						if (taxablePay <= 333)   //Level 1
						{
							fedTax = 0;
						}
						else if (taxablePay > 333 && taxablePay <= 1050)    //Level 2
						{
							fedTax = 0 + (0.10 * (taxablePay - 333));
						}
						else if (taxablePay > 1050 && taxablePay <= 3252)    //Level 3
						{
							fedTax = 71.70 + (0.15 * (taxablePay - 1050));
						}
						else if (taxablePay > 3252 && taxablePay <= 6221)    //Level 4
						{
							fedTax = 402 + (0.25 * (taxablePay - 3252));
						}
						else if (taxablePay > 6221 && taxablePay <= 9308)    //Level 5
						{
							fedTax = 1144.25 + (0.28 * (taxablePay - 6221));
						}
						else if (taxablePay > 9308 && taxablePay <= 16360)    //Level 6
						{
							fedTax = 2008.61 + (0.33 * (taxablePay - 9308));
						}
						else if (taxablePay > 16360 && taxablePay <= 18437)    //Level 7
						{
							fedTax = 4335.77 + (0.35 * (taxablePay - 16360));
						}
						else if (taxablePay > 18437)    //Level 8
						{
							fedTax = 5062.72 + (0.396 * (taxablePay - 18437));
						}
					}
					else    //monthly
					{
						if (payPeriod == 1)    //monthly
						{
							witholding = dependents * 337.50;
							taxablePay = grossPay - witholding;

							//include tax bracket for married/monthly

							if (taxablePay <= 721)     //Level 1
							{
								fedTax = 0;
							}

							else if (taxablePay > 721 && taxablePay <= 2275)    //Level 2
							{
								fedTax = 0 + (0.10 * (taxablePay - 721));
							}
							else if (taxablePay > 2275 && taxablePay <= 7046)    //Level 3
							{
								fedTax = 155.40 + (0.15 * (taxablePay - 2275));
							}
							else if (taxablePay > 7046 && taxablePay <= 13479)    //Level 4
							{
								fedTax = 871.05 + (0.25 * (taxablePay - 7046));
							}
							else if (taxablePay > 13479 && taxablePay <= 20167)    //Level 5
							{
								fedTax = 2479.30 + (0.28 * (taxablePay - 13479));
							}
							else if (taxablePay > 20167 && taxablePay <= 35446)    //Level 6
							{
								fedTax = 4351.94 + (0.33 * (taxablePay - 20167));
							}
							else if (taxablePay > 35446 && taxablePay <= 39946)    //Level 7
							{
								fedTax = 9394.01 + (0.35 * (taxablePay - 35446));
							}
							else if (taxablePay > 39946)    //Level 8
							{
								fedTax = 10969.01 + (0.396 * (taxablePay - 39946));
							}
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

		system("cls");
		//Menu input
		cout << "Tax Calculator" << endl;
		cout << endl;
		cout << "1. Calculate Tax" << endl;
		cout << endl;
		cout << "0. Exit" << endl;
		cout << endl;
		cout << "Enter Choice: ";
		cin >> choice;
	}

	return 0;
}