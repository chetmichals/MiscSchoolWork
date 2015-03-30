/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 4, Program 1
Due Time and Date: Novermber 18th, 2010 at 11 PM EST
Last Changed: Novermber 17th, 2010 at 10:20 PM EST
Instructor: Ingrid Buckley
Objective: Reverse a C String with the aid of pointers
Total Points: 100 For Entire Assignment, 25 for this program
*/

#include <iostream>
#include <string.h>

using namespace std;

void ReverseString(char text[]); //Reverses String

int main()
{
	char text[264];
	cout << "Please type in a string" << endl;
	gets(text);	
	ReverseString(text);
	cout << "That String reversed is: "<< endl << text;
	return 0;
}

/*Name: ReverseString
Purpose: Reverses a String
Precondition: String must be a C String
Postcondition: C String will be reversed
How to call: ReverseString(text);*/

void ReverseString(char text[])
{
	char *front, *rear, temp; //Two pointers and a tempary value
	int i; //used for for loop
	int length=strlen(text); //Gets the length of the string
	for(i=0;i<=(length/2);i++) //Used to reverse string
	{
		front=&text[i]; 
		rear=&text[(length-i-1)];
		temp=*front;
		text[i]=*rear;
		text[(length-i-1)]=temp;
	}
}