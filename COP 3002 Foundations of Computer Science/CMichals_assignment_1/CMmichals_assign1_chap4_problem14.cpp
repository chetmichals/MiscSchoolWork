/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 1, Program 3
Due Time and Date: September 23rd, 2010 at 11 PM EST
Last Changed: September 23rd, 2010, at 10:40 PM EST
Instructor: Ingrid Buckley
Objective: To Calculate Basal Metablism Rate, the Calories used in a physical activity, amount used in digestion, and modurize the whole thing
Total Points: 100 For Entire Assignment, 20 for this program
*/


#include <iostream>
#include <cmath> //Allows use of Root Function
#include <iomanip> //Allows for adjusting the number of decimal places
using namespace std;

double Basal(double weight);
double CalForPhys(double weight, double time, double intensity);
double Digest(double foodCal);
void UserInput(double &weight, double &time, double &foodCal, double &meals);

int main()
{
	double weight = 0, time = 0 , intensity = 0, foodCal=0, meals=0, digestion=0; //Initalizes Varables
	UserInput(weight,time,intensity,foodCal); //gets user input
	digestion = Digest(foodCal); //Calculates the amount of calories lost to digestion 
	meals = (Basal(weight)+CalForPhys(weight,time,intensity))/(foodCal-digestion); //Calculates the number of portions of food item to maintain weight
	cout << endl<< "You will need to eat "<< fixed << setprecision(2) << meals; //setprecision allows for setting of the number of Decimal Places. Uses iomanip.
	cout << " Portions of your \nFavorite Food to maintain your current weight";
	cout << endl << endl <<"Besides your Metabolism and Physical Activty\nyou lost "<< fixed << setprecision(0) << digestion << " Calories due to Digestion\n\n";
}

/* Name: Basal
Input: Weight in pounds, given in a Double.
Output: Calories, as a double
Purpose: To Calculate the Basal Metalbolic rate. */

double Basal(double weight)
{
return (70 * pow((weight/2.2), .756)); //pow raises the first number to the power of the second number. Function found in cmath
}

/* Name: CalForPhys
Input: Weight in pounds, time in minutes, intensity factor of exersiese, all given as doubles
Output: Calories used, as a double
Purpose: Calculates how many Calories is required to do a physical activiey */

double CalForPhys(double weight, double time, double intensity)
{
return (.0385 * weight * time * intensity);
}

/* Name: Digest
Input: Total Calories of food eaten, in a double
Output: Calories used in digestion, as a double
Purpose: To calculate the amount of calories lost in digestion */
double Digest(double foodCal)
{
	return(foodCal*.1);
}

/* Name: UserInput
Input: Passed by Refrence Weight, Time, Intensity, and Calloris of a food item, in doubles
Output: None
Purpose: To get the input of varius varables */
void UserInput(double &weight, double &time, double &intensity, double &foodCal)
{
	cout << "Please Input Weight in pounds: ";
	cin >> weight;
	cout << endl << "Please Input Time you will be exersising: ";
	cin >> time;
	cout << endl << "Please Input the exersises intensity factor: ";
	cin >> intensity;
	cout << endl << "Please Input the Amount of Calories for your favorite food: ";
	cin >> foodCal;

}