#include <iostream>
#include <math.h>
using namespace std;

int main()
{
	//Total and Average
	float n1, n2, n3, n4, n5, n6, tot, avg;
	cout << "Compute the total and average of six numbers\n";				//Title
	cout << "****************************************************\n";		//Seperation
	cout << " Input 6 integers numbers (separated by space) : ";			//Asking for integers
	cin >> n1 >> n2 >> n3 >> n4 >> n5 >> n6;								//Input for integers
	tot = n1 + n2 + n3 + n4 + n5 + n6;				//Calculates the total
	avg = tot / 6;									//Calculates the average

	//Answers
	cout << "\n";
	cout << " The total of six numbers is : " << tot << endl;			//Prints total
	cout << " The average of six numbers is : " << avg << endl;			//Prints average
	cout << endl;

	return 0;
}