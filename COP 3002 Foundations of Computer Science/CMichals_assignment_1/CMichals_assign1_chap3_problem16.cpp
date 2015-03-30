/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 1, Program 2
Due Time and Date: September 23rd, 2010 at 11 PM EST
Last Changed: September 23rd, 2010, at 8:55 PM EST
Instructor: Ingrid Buckley
Objective: To caluclate the Tempiture at which Celsisu and Fahrenhit are equal.
Total Points: 100 For Entire Assignment, 20 for this program
*/


#include <iostream>
using namespace std;

int main()
{
	int Celsius = 100, Fahrenhit = 0; //Celsius needs to be initalized to 100 per assigment
	Fahrenhit = (Celsius*9/5)+32; // Calculating the starting value of Fahrenhit using provided formual
	while (Celsius > -218) //Absoulte Zero, lowest tempiture possible
	{
		if (Celsius == Fahrenhit)
		{
			cout << "At "<< Celsius << " Degrees, both Celsius and Fahrenhit are equal" << endl;
			break; //Was getting stuck in an infinte loop due to the while condition never being false, simple fix
		}
		else //increments Celsius 1 down and recaluculates Fahrenhit
		{
			Celsius=Celsius-1;
			Fahrenhit = (Celsius*9/5)+32;
		}
	}
	return 0;
}