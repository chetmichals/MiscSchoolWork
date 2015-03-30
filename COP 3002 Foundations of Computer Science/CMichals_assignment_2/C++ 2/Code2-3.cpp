/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 2, Program 3
Due Time and Date: October 6, 2010 at 11:00 PM 
Last Changed: October 6, 2010 at 5:15 PM
Instructor: Ingrid Buckley
Objective: To take two files with list of numbers, from smallest to largest, and output a single file with a list of numbers,
from smallest to largest
Total Points: 100 For Entire Assignment, 25 for this program
*/

#include <iostream>
#include <fstream>


using namespace std;

int CompareNumbers(ifstream &fileOne, ifstream &fileTwo, ofstream &outputFile); 
/*Used to take two files with list of numbers from smallest to largest and output a single file 
with the numbers smallest to largest */

int main ()
{
	ifstream fileOne ("input1.txt"); //Opens first file, for reading input
	ifstream fileTwo ("input2.txt"); //Opens second file, for reading input
	ofstream outputFile ("output.txt"); //Creates output file
	CompareNumbers(fileOne,fileTwo,outputFile); // Call CompareNumbers Function
	
	// Closes files and ends program
	fileOne.close();
	fileTwo.close();
	outputFile.close();
	return 0;
}

/* Name: CompareNumbers
Purpose: To call the propper fuctions to prompt for, then Convert and display Feet and and Inches into Meters and Centimeters.
Precondition: The Two input files and output file must be open, input files must be sorted from smallest to largest.
Postcondition: None
How to call: CompareNumbers(fileOne,fileTwo,outputFile);
Note: Input files must be from smallest to largest to work, most only hvae intigers */

int CompareNumbers (ifstream &fileOne, ifstream &fileTwo, ofstream &outputFile) 
{
	int tempNum1, tempNum2, tempNum3; //Creates three temporay varables to store input from file, so they can be compared
	fileOne >> tempNum1; // Puts the first number from the first input into a temporay varable
	fileTwo >> tempNum2;  // Puts the first number from the second input into a temporay varable

	//Puts numbers from input files into output files in order until one of the input files ends
		while (! fileOne.eof() && ! fileTwo.eof())
	{
		if (tempNum1 > tempNum2)
		{
			outputFile << tempNum2 << endl;
			//tempNum3=tempNum2;//Used in if statement below
			fileTwo >> tempNum2;
		}
		else
		{
			outputFile << tempNum1 << endl;
			//tempNum3=tempNum1;//Used in  if statement below
			fileOne >> tempNum1;
		}
	}
	

//Place last numbers in tempoary varables into text file
	if (fileOne.eof()==1 && fileTwo.eof()!=1 && tempNum1 > tempNum2)
	{
		outputFile << tempNum1 << endl;
	}
	else if (fileTwo.eof()==1 && fileOne.eof()!=1 &&tempNum2 > tempNum1)
	{
		outputFile << tempNum2 << endl;
	}
	else
	{
		if (tempNum1 > tempNum2)
		{
			outputFile << tempNum2 << endl;
			outputFile << tempNum1 << endl;
		}
		else
		{
			outputFile << tempNum1 << endl;
			outputFile << tempNum2 << endl;
		}
	}
	

	//Puts rest of numbers from input 1 into the output if input 1 has not made it to the end of file
	while (fileOne.eof()!=1)
	{
		fileOne >> tempNum1;
		outputFile << tempNum1 << endl;
		
	}
	
	//Puts rest of numbers from input 2 into the output if input 2 has not made it to the end of file
	while (fileTwo.eof()!=1)
	{
		fileOne >> tempNum2;
		outputFile << tempNum2 << endl;
		
	}	
	return 0;
}