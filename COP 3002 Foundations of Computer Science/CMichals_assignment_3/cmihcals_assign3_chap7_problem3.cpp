/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 3, Program 4
Due Time and Date: October 21st, 2010 at 11 PM EST
Last Changed: October 6th at 4:25 AM EST
Instructor: Ingrid Buckley
Objective: Calculates the Wind Chill Factor
Total Points: 100 For Entire Assignment, 25 for this program
*/

#include <iostream>

#define length(a) (sizeof a / sizeof a[0]) //Allows you to get the size an array easily

int delete_repeats(char Array[], int elements);

using namespace std;

int main()
{
	int startLength = 0, endLenght = 0;
	char Array1 [] = "mary had a little lamb. its fleece was white as snow.";
	char Array2 [] = "Now is the time for all good men to come to the aid of the country.";
	startLength =length(Array1);
	cout << "Starting Array: " << Array1 << endl;
	cout << "Lenth of Array: " << startLength << endl;
	endLenght = delete_repeats(Array1, startLength);
	cout << "Reuced Array: " << Array1 << endl;
	cout << "Reduce Lenth: " << endLenght << endl << endl;

	startLength =length(Array2);
	cout << "Starting Array: \n" << Array2 << endl;
	cout << "Lenth of Array: " << startLength << endl;
	endLenght = delete_repeats(Array2, startLength);
	cout << "Reuced Array: " << Array2 << endl;
	cout << "Reduce Lenth: " << endLenght << endl;

	return 0;
}

int delete_repeats(char Array[], int elements)
{
	char tempArray1[100];
	int x = 0;
	while (x < elements)
	{
	tempArray1[x]=Array[x];
	x++;
	}

	char tempLetter1, tempLetter2;
	int i1 = 0, i2 = 0, n=0;
	while (i1 < elements)
	{
		tempLetter1 = tempArray1[i1];
		if (tempLetter1 != '0')
		{
			Array[n] = tempLetter1;
			n++;
		}
		while (i2 < elements)
		{
		
			tempLetter2 = tempArray1[i2];
			if(tempLetter2 == tempLetter1)
			{
				tempArray1[i2] = '0';
			}
			i2++;
		}
		i1++;
		i2=0;
	}
	int n2 = n;
	while (n2 < elements)
	{
		Array[n2] = ' ';
		n2++;
	}
	return n;
}