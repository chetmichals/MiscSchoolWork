/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 4, Program 4
Due Time and Date: Novermber 18th, 2010 at 11 PM EST
Last Changed: Novermber 18th, 2010 at 6:45 PM EST
Instructor: Ingrid Buckley
Objective: To make a class with serveral over rided operators, used for storing the radius of a circle
Total Points: 100 For Entire Assignment, 25 for this program
*/

#include <iostream>


using namespace std;
class SimpleCircle
{
public:
	SimpleCircle(int input); // sets radius to inputed number
	SimpleCircle(); // sets radius to 5

	friend SimpleCircle operator++(SimpleCircle&);
	friend ostream& operator <<(ostream&, const SimpleCircle&);
	friend SimpleCircle operator*(SimpleCircle&, const SimpleCircle&);
private:
	int radius;
};

SimpleCircle::SimpleCircle(int input)
{
	radius=input;
}

SimpleCircle::SimpleCircle()
{
	radius=5;
}

	
SimpleCircle operator++(SimpleCircle& input) //increments
{
	input.radius=input.radius+1;
	return 0;
}

ostream& operator <<(ostream& stream, const SimpleCircle& input)
{
	stream << input.radius;
	return stream;
}

SimpleCircle operator*(SimpleCircle& input1, const SimpleCircle&input2) //Could not figure out how to get = to work, used * instead to make equal
{
	input1.radius=input2.radius;
	return 0;
}


int main()
{
	SimpleCircle circle1, circle2(9);
	cout << "Circle 1 has a radius of " << circle1 << endl;
	cout << "Circle 2 has a radius of " << circle2 << endl;
	circle1++;
	circle2++;

	cout << endl << "After Incrementing Values:" << endl;
	cout << "Circle 1 has a radius of " << circle1 << endl;
	cout << "Circle 2 has a radius of " << circle2 << endl;
	circle1*circle2;
	
	cout << endl << "After assingin the value to each other:" << endl;
	cout << "Circle 1 has a radius of " << circle1 << endl;
	cout << "Circle 2 has a radius of " << circle2 << endl;

	return 0;
}