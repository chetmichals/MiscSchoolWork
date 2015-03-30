/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 1, Program 1
Due Time and Date: September 23rd, 2010 at 11 PM EST
Last Changed: September 23rd, 2010, at 9:01 PM EST
Instructor: Ingrid Buckley
Objective: To caluclate all prime numbers between 3 and 100
Total Points: 100 For Entire Assignment, 20 for this program
*/

#include <iostream>
using namespace std;

int main()
{
	int Number=3, Divisor=2; /*Intalzing the numbers. Setting 'Number' to 3 due to program specifications, 
							 setting devisor to 2 due to definition of a prime number.*/
	while (Number <= 100) //Setting a loop to keep going till Number = 100
	{
		if (Number == Divisor) /*If failed conditions below repeated times, Number = Divisor proving its a prime number, steps up
							   Number and Reinitalizes Divisor*/
		{	
			cout << Number << " Is a Prime Number" << endl;
			Number++;
			Divisor = 2;
		}		
		else if (Number % Divisor == 0) /*If ever true, number is not a prime number, steps up Number and Reinitalizes Divisor */
		{
			Number++;
			Divisor = 2;
		}
		else if (Number % Divisor != 0 && Number > Divisor) //Steps up the Divisor.
		{
			Divisor++;
		}
		
	}
	return 0;
}
