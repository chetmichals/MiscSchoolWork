/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 2, Program 2
Due Time and Date: October 6th, 2010 at 11 PM EST
Last Changed: October 6th at 4:25 AM EST
Instructor: Ingrid Buckley
Objective: Calculates the Wind Chill Factor
Total Points: 100 For Entire Assignment, 25 for this program
*/

#include <iostream>
#include <cmath>

using namespace std;

double getWindChill(double temp, double windSpeed);//Calculates the windchill factor
double getTemp();//Displays prompts ands gets tempiture
double getWindSpeed();//displays prompts and gets Wind Speed

int main()
{
	double temp = 0, windSpeed = 0, windChill=0;
	cout << "This program calulates Windchill factor." << endl << endl;
	temp = getTemp();
	windSpeed=getWindSpeed();
	windChill=getWindChill(temp, windSpeed);
	cout << "Wind Chill Factor is " << windChill << endl;
	return 0;
}

/*Name: getWindChill
Purpose: Calculates the Windchill factor
Precondition: Tempiture must be 10C or less
Postcondition: None
How to call: getWindChill(temp, windSpeed)
Note: Tempiture is in Celsius, Windspeed is in Meters per Second*/


double getWindChill(double temp, double windSpeed)
{
	return(13.12 + 0.6215*temp - 11.37 * pow(windSpeed, .16) + .3965 * temp * pow(windSpeed, .016));
}

/*Name: getTemp
Purpose: Gets input for tempiture
Precondition: None
Postcondition: None
How to call: getTemp()
Note: Tempiture is in Celisus, must be less 10C or less*/


double getTemp()
{
	double temp=0;
	cout << "Please input the tempiture in Celius." << endl << "Please note the Tempiture must be 10C or below. " << endl;
	do
	{
		cin >> temp;
		if (temp > 10)
		{
			cout << "Tempiture is greater then 10C. Please input a Tempiture below 10C. " << endl;
			}
		}
	while  (temp > 10);
	return temp;
	}

/*Name: getWindSpeed
Purpose: Gets input for Windspeed
Precondition: None
Postcondition: None
How to call: getWindSpeed()
Note: Windspeed is in Meters per Second*/
double getWindSpeed()
{
	double windspeed=0;
	cout << "Please input the windspeed in M/S. " << endl;
	cin >> windspeed;
	return windspeed;
}