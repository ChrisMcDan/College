#include <iostream>
using namespace std;

int main()
{
	int income, tax_1, tax_2, tax_3;

	cout << "What is your income? : ";
	cin >> income;

	if (income < 15000)
	{
		cout << "There is no tax on your income!!";
		cout << tax_1;
	}

	else (15001 < income < 25000);
	{
		cout << "There will be a 5% tax on your income";
		tax_2 = (1.05 * income);
		cout << "Here is your income: " << tax_2;
	}

	else if (income > 25001)
		
	cout << "There will be a 10% tax on your income";
	tax_3  = (1.10 * income);
	cout << "Here is your income: " << tax_3;
}