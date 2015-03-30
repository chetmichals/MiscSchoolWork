/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 3, Program 3
Due Time and Date: October 21, 2010 at 11:00 PM 
Last Changed: October 21, 2010 at 11:45 AM
Instructor: Ingrid Buckley
Objective: To make a class that tracks Millage driven and Fuel Ecconemy, and create a program to use it.
*/
#include <iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////
//Odometer Class Starts here
//////////////////////////////////////////////////////////////////////////////////////
class Odometer {
public:
    void initalizeOdometer();
	void UserInputMPG();
	void UserInputMiles();
    //double testfunction();
	void OdometerReset();
	void OutputCurrentStats();
private:
    double totalMiles , MPG, odometer;
};

void Odometer::initalizeOdometer()
{
	totalMiles = 0;
	MPG = 0;
	odometer = 0;
}

void Odometer::UserInputMPG()
{
    cout << "What is you fuel ecconmeny in miles per gallon: ";
    cin >> MPG;

}

void Odometer::UserInputMiles()
{
	double temp=0;
	cout << "How many miles did you drive: ";
    cin >> temp;
	odometer= odometer+temp;
	totalMiles= totalMiles + temp;
}

void Odometer::OdometerReset()
{
	odometer = 0;
	cout << endl << "Odometer reset to 0" << endl;
}

/*
double Odometer::testfunction()
{
    return (totalMiles*MPG);
}
*/

void Odometer::OutputCurrentStats()
{
	double temp = odometer/MPG; //Calculates gallons of gas used since odometer reset
	cout << endl << "At " << MPG << " Miles per Gallon, you have used " << temp << " gallons of Gas since \nyour last odometer reset." << endl << endl;
	cout << "You have driven a total of " << totalMiles << " miles, and your odometer reads " << odometer << "." << endl << endl;
}

//////////////////////////////////////////////////////////////////////////////////////
//Odometer Class Ends here
//////////////////////////////////////////////////////////////////////////////////////


int main()
{
    char cont = 'y', reset = 'n'; //Cont is used for main while loop, reset is use for odometer reset condition
	Odometer test; //Makes instance of Odometer Class object to test the class functions
	test.initalizeOdometer();
    test.UserInputMPG();
	while (cont == 'y' || cont == 'Y')
	{
		test.UserInputMiles();
		test.OutputCurrentStats();
		cout <<"Would you like to reset your odometer? Type in yes if you do." << endl;
		cin >> reset;
		if (reset == 'y' || reset == 'Y')
			test.OdometerReset();
		cin.ignore(10, '\n'); //Clears input buffer upto 10 characters
		cout <<"Would you like to continue? Type in yes if you do." << endl;
		cin >> cont;
		cin.ignore(10, '\n'); //Clears input buffer upto 10 characters
	}
    return 0;
}
