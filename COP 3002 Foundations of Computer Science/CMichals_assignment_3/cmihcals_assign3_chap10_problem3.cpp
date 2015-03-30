/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 3, Program 3
Due Time and Date: October 21, 2010 at 11:00 PM 
Last Changed: October 21, 2010 at 12:15 PM
Instructor: Ingrid Buckley
Objective: To convert the provided CDAccount Structer into a Class

Note: This code is an adaptation of example code provided in the 6th Edition of Problem Solving with C++,
by Walter Savitch, copyright 2007 by Pearson Education
*/


#include <iostream>
using namespace std;


//////////////////////////////////////////////////////////////////////////////////////
//CDAccount Class Starts here
//////////////////////////////////////////////////////////////////////////////////////
class CDAccount
{
public: 
	void GetInput();
	void Calculations();
	void PrintOutput();
private: 
	double balance;
    double interest_rate; 
	double rate_fraction; 
	double interest; 
    int term;//months until maturity
};

void CDAccount::GetInput()
{
    cout << "Enter account balance: $";
    cin >> balance;

    cout << "Enter account interest rate: ";
    cin >> interest_rate;
    cout << "Enter the number of months until maturity\n"
         << "(must be 12 or fewer months): ";
    cin >> term;
}

void CDAccount::Calculations()
{
    rate_fraction = interest_rate/100.0;
    interest = balance*rate_fraction*(term/12.0);
    balance = balance + interest;
}

void CDAccount::PrintOutput()
{
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "When your CD matures in " 
         << term << " months,\n"
         << "it will have a balance of $" 
         << balance << endl; 

}

//////////////////////////////////////////////////////////////////////////////////////
//CDAccount Class Ends here
//////////////////////////////////////////////////////////////////////////////////////

int main( )
{
    CDAccount account;
	account.GetInput();
	account.Calculations();
	account.PrintOutput();
    return 0;
}