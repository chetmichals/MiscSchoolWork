/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 1, Program 4
Due Time and Date: September 23rd, 2010 at 11 PM EST
Last Changed: September 23rd, 2010, at 10:35 PM EST
Instructor: Ingrid Buckley
Objective: To take user input and check against an item cost, denying invalid denomiations, and giving change
Total Points: 100 For Entire Assignment, 20 for this program
*/


#include <iostream>
#include <iomanip> //used to allow for setprecision
using namespace std;

void InsertMoney(double &change);
int main()
{
	double change=0;
	cout << "One Deep Fried Twinkie costs $3.50" << endl;
	cout << "This Machine accepets $1 Bills, quarters, dimes, and nickels." <<endl << endl;
	InsertMoney(change);
	cout << endl << "Enjoy your Deep Fried Twinkie" << endl << "Your change is $" << fixed << setprecision(2) <<change << endl;
	return 0;
}

void InsertMoney(double &change)
{
	double money=0, totalMoney=0;
	while (totalMoney < 3.5)
	{
		cout << "Input ammount of Inserted Money: $";
		cin >> money;
		if (money == 1||money==.25||money==.1||money==.05) //check for valid denomination
		{
			totalMoney=money+totalMoney;
			if (totalMoney>=3.5) break; //breaks while loop as soon as total money is greater or equal to 3.5
			cout << endl <<"Current Total is $"<< fixed << setprecision(2) << totalMoney<< endl<<endl;
		}
		else
		{
			cout << endl <<"We do not accept that denomination" << endl <<endl;
		}
	}
	change=totalMoney-3.5;
}