/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 4, Program 2
Due Time and Date: Novermber 18th, 2010 at 11 PM EST
Last Changed: Novermber 18th, 2010 at 9:20 AM EST
Instructor: Ingrid Buckley
Objective: To work with Dynamic Arrays to make them simulate the function of Vectors
Total Points: 100 For Entire Assignment, 25 for this program
*/
#include <iostream>
#include <new>
#include <string>

using namespace std;

string* addEntry(string *dynamicArray, int &size, string newEntry);
string* deleteEntry(string *dynamicArray, int &size, int removed);
void printArray(string dynamicArray[], int size);

int main()
{
	int size=5; //Holds the size of the array, which we are starting at 5.
	string *dynamicArray; //Pointer to dynamic array
	dynamicArray= new (nothrow) string[size]; //Creates the array

	//Initializes Array with the 5 elements
	dynamicArray[0] = "Frink";
	dynamicArray[1] = "Wiggum";
	dynamicArray[2] = "Nahasapeemapetilon";
	dynamicArray[3] = "Quimby";
	dynamicArray[4] = "Flanders";

	cout << "Current List:" << endl;
	printArray(dynamicArray, size);

	cout << endl << "List after adding new element: " << endl;
	dynamicArray=addEntry(dynamicArray,size,"NEW NAME!");
	printArray(dynamicArray, size);

	cout << endl << "List after delete an element: " << endl;
	dynamicArray=deleteEntry(dynamicArray,size,3);
	printArray(dynamicArray, size);

	cout << endl << "List after deleting all elements: " << endl;
	for(int i=size;i>0;i--) //Removes all elements of the array no matter the size
	{
		dynamicArray=deleteEntry(dynamicArray,size,(size-1));
	}
	printArray(dynamicArray, size);
	

	cout << endl << "List after adding new element: " << endl;
	dynamicArray=addEntry(dynamicArray,size,"ANTHER NEW NAME!");
	printArray(dynamicArray, size);

	return 0;

}



// Adds an entry to the dynamic array, returning a pointer to the
// expanded array. size should contain the size of the array. It
// will be updated when the array is expanded.

string* addEntry(string *dynamicArray, int &size, string newEntry)
{
 // Create a new array, copy the contents of the old array, then
 // delete it
 string *newArray = new string[size + 1];
 for (int i = 0; i < size; i++)
 {
 newArray[i] = dynamicArray[i];
 }
 delete[] dynamicArray;
 
 // Add the new entry and increment the size
 newArray[size++] = newEntry;
 
 return newArray;
}


//Prints elements of an array upto the the index at size
void printArray(string dynamicArray[], int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		printf(" %d: ",(i+1));
		cout << dynamicArray[i] <<  endl;
	}
}


// Deletes an entry to the dynamic array, returning a pointer to the
// smaller array. size should contain the size of the array. It
// will be updated when the array is expanded.

string* deleteEntry(string *dynamicArray, int &size, int removed)
{
 // Create a new array, copy the contents of the old array, then
 // delete it, skipping the removed index
	
	int i2=0;
	string *newArray = new string[size - 1];
	for (int i = 0; i < size; i++)
	{
	 if(i != removed)
	 {
		 newArray[i2] = dynamicArray[i];
		 i2++;
	 }
	}
	delete[] dynamicArray;
	size--;
	return newArray;
}