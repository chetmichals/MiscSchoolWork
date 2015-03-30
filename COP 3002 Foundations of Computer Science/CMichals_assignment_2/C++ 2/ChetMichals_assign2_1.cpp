/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 2, Program 1
Due Time and Date: October 6, 2010 at 11:00 PM 
Last Changed: October 6, 2010 at 3:54 AM
Instructor: Ingrid Buckley
Objective: To convert between Feet/Inches and Meters/Centimeters, and vise versa.
Total Points: 100 For Entire Assignment, 25 for this program
*/

#include <iostream>
using namespace std;


void imperal(); //Function that calls imperal -> metric conversions
void metric(); //Function that calls metric -> imperal conversions
void start(); //Promts user on what kind of conversion they want to do.

void getInputImperal(double &inches, double &feet); // Gets input for feet and inches
void convertImperal(double inches, double feet, double &meters, double &centimeters); // converts feet and inches into metric
void outputImperal(double meters, double centimeters); // outputs the anwser in Meters and Centimeters

void getInputMetric(double &centimeters, double &meters);// Gets input for centimeters and meters
void convertMetric(double &inches, double &feet, double meters, double centimeters);// converts metric to imperal
void outputMetric(double inches, double feet); // outputs the anwser in feet and inches

int main()
{
	char keepRunning = 'y';
	cout <<"This program can convert Metric to Imperal and Imperal to metric" << endl << endl;
	while (keepRunning == 'y')
	{
		start();
		cout << "Would you like to do anther conversion? Type y if you do, if not type any other character." << endl;
		cin >> keepRunning;
	}
	cout << "Thank you for using the program. Closeing now." << endl;
	return 0;
}

/* Name: imperal
Purpose: To call the propper fuctions to prompt for, then Convert and display Feet and and Inches into Meters and Centimeters.
Precondition: None
Postcondition: None
How to call: imeral();
Note: Centimeter will be returned as a whole number, cutting off any decimal */


void imperal()
{
	double inches=0, feet=0, meters=0, centimeters=0;
	cout <<"Now converting Feet and Inches into Metric." << endl;
	getInputImperal(inches, feet);
	convertImperal(inches, feet, meters, centimeters);
	outputImperal(meters, centimeters);
}

/*Name: getInputImperal
Purpose: To prompt for and get the input for feet and inches
Precondition: None
Postcondition: None
How to call: getInputImperal(inches, feet);
Note: The two varables are passed by reference*/



void getInputImperal(double &inches, double &feet)
{
	cout << "Please Input the amount of feet: ";
	cin >> feet;
	cout << "Please Input the amount of inches: ";
	cin >> inches;
}

/*Name: convertImperal
Purpose: Convert feet and inches to meters and centimeters
Precondition: None
Postcondition: None
How to call: convertImperal(inches, feet, meters, centimeters)
Note: Meters and Centimeters are passed by reference*/


void convertImperal(double inches, double feet, double &meters, double &centimeters)
{
	double tempNumber;
	feet=feet+(inches/12);
	meters=feet*.3048;
	tempNumber= meters;
	meters = (int)meters;
	centimeters= (int)((tempNumber-meters)*100);
}

/*Name: outputImperal
Purpose: Displays an amount in meters and centimeters to the user
Precondition: None
Postcondition: None
How to call: outputImperal(meters, centimeters)*/

void outputImperal(double meters, double centimeters)
{
	cout << "That is " << meters  << " meters and " << centimeters << " centimeters." << endl;
}
/* Name: metric
Purpose: To call the propper fuctions to prompt for, then Convert and display Meters and Centimeters into Feet and and Inches
Precondition: None
Postcondition: None
How to call: metric();
Note: Inches will be returned as a whole number, cutting off any decimal */

void metric()
{
	double inches=0, feet=0, meters=0, centimeters=0;
	cout <<"Now converting Meters and Centimeters into Impereal." << endl;
	getInputMetric(centimeters, meters);
	convertMetric(inches, feet, meters, centimeters);
	outputMetric(inches, feet);
}

/*Name: getInputMetric
Purpose: To prompt for and get the input for meters and centimeters
Precondition: None
Postcondition: None
How to call: getInputMetric(centimeters, meters);
Note: The two varables are passed by reference*/

void getInputMetric(double &centimeters, double &meters)
{
	cout << "Please Input the amount of Meters: ";
	cin >> meters;
	cout << "Please Input the amount of Centimeters: ";
	cin >> centimeters;
}

/*Name: convertMetric
Purpose: Convert meters and centimeters to feet and inches
Precondition: None
Postcondition: None
How to call: convertMetric(inches, feet, meters, centimeters)
Note: Feet and Inches are passed by reference*/

void convertMetric(double &inches, double &feet, double meters, double centimeters)
{
	double tempNumber;
	meters=meters + (centimeters/100);
	tempNumber = feet =meters/(.3048);
	feet = (int)feet;
	inches = (int)((tempNumber-feet)*12);
}

/*Name: outputMetric
Purpose: Displays an amount in feet and inches to the user
Precondition: None
Postcondition: None
How to call: outputMetric(inches, feet);*/


void outputMetric(double inches, double feet)
{
	cout << "That is " << feet  << " feet and " << inches<< " inches." << endl;
}

/*Name: start
Purpose: To inform the user about conversions done by the program, prompt which one they wish to do, and initalize the function for it
Precondition: None
Postcondition: None
How to call: start()*/
void start()
{
	int choice;
	cout << 
		"To convert from feet and inches to meters and centimeters, type in 1." << endl <<
		"To convert from meters and centimeters to feet and inches, type in 2." << endl;
	cin >> choice;
	if (choice == 1)
	{
		imperal();
	}
	else if (choice == 2)
	{
		metric();
	}
	else
	{
		cout<< "That input is invalid." << endl;
	}
}