/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 5, Program 2
Due Time and Date: Novermber 29th, 2010 at 11 PM EST
Last Changed: Novermber 29th, 2010 at 9:20 PM EST
Instructor: Ingrid Buckley
Objective: To combine to linked lists and sort them
Total Points: 100 For Entire Assignment, 50 for this program
*/

#include <iostream>
using namespace std;

struct node
  { 
     int number;          // Number stored in node
     node *nextNode;        // Pointer to next node
  };


void SortList(node* startOne) //Sorts list out
{
	node *head=NULL, *after=NULL; //Temp nodes
	int temp; //Temp numbe to store contents
	head=startOne; 
	after=head->nextNode;
	while (after->nextNode!= NULL)
	{
		if (head->number > after->number) //Sorts contents
		{
			temp=head->number;
			head->number=after->number;
			after->number=temp;
			SortList(startOne); //Function is recursive, as such it calls its self to fully sort list
		}
		head=head->nextNode;
		after=after->nextNode;
	}

}

int main()
{
	int i=1;
	while (i==1)
	{
	int input=0; //Stores user input
	node *startOne;  //first list
	node *headOne = NULL;    
	
	node *startTwo; //second lists
	node *headTwo = NULL;    
	
	//initlize first list
	startOne = new node;
	startOne->nextNode=0;
	headOne = startOne;

	//initlize second list
	startTwo = new node;
	startTwo->nextNode=0;
	headTwo = startTwo;
	 
	cout <<"Please input the integers you wish to go into the first list." << endl <<"End input with a negitive number:" << endl;

	//get data for first list
	while (input >=0)
	{

		cin >> input; 
		if (input >=0)
		{
			headOne->number=input;
			headOne->nextNode = new node;
			headOne = headOne->nextNode;
			headOne->nextNode=NULL;
		}
	}

	cout <<"Please input the integers you wish to go into the second list." << endl <<"End input with a negitive number:" << endl;
	input = 0;

	//gets data for second list
	while (input >=0)
	{

		cin >> input; 
		if (input >=0)
		{
			headTwo->number=input;
			headTwo->nextNode = new node;
			headTwo = headTwo->nextNode;
			headTwo->nextNode=NULL;
		}
	}


	//combines the lists
	headOne->nextNode=startTwo;
	headOne->number=0;
	SortList(startOne); //Sorts out the list
	//sets up list to be printed out
	node *printList;
	printList=startOne;
	printList = printList->nextNode;

	cout << endl << "The two lists combined and sorted: "<< endl;
	 while ( printList->nextNode != 0)
	 {
		 cout << printList->number << endl;
		 printList = printList->nextNode;
	 }
	 	cout << endl << "Would you like to do this again? Type 1 to do so, any other number if you do not" << endl;
	 cin >> i;
}
	return 0;
}

