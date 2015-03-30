/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 5, Program 1
Due Time and Date: Novermber 29th, 2010 at 11 PM EST
Last Changed: Novermber 29th, 2010 at 8:40 PM EST
Instructor: Ingrid Buckley
Objective: To revese the content of a linked list
Total Points: 100 For Entire Assignment, 50 for this program
*/

#include <iostream>
using namespace std;

struct node
  { 
     int number;          // Number stored in node
     node *nextNode;        // Pointer to next node
  };


void reverseList(node* head)
{
node* newList = NULL; //pointer for new list
node* oldList = head; //pointer for old list

while (oldList != NULL)
	{
		//Loops Reverses the list
		node* nextNode = oldList->nextNode;
		oldList->nextNode = newList;
		newList = oldList;
		oldList = nextNode;
	}
}

int main()
{
	int i=1;
while (i == 1)
{
	cout <<"Please input the integers you wish to be in the list." << endl <<"To stop input please put in a negitive number." << endl;
	int input=0;
	node *start; 
	node *head = NULL;    
	
	start = new node;
	start->nextNode=0;
	head = start;
	 
	if ( head != 0 ) 
	{
    while ( head->nextNode != 0)
      head = head->nextNode;
	}

	while (input >=0)
	{
	cin >> input; 
	if (input >=0)
	{
		head->nextNode = new node;
		head = head->nextNode;
		head->nextNode=NULL;
		head->number=input;
	}
	}
	head->nextNode=NULL;
	reverseList(start);
	cout << endl << "The list reversed: " << endl;
	 while ( head->nextNode != 0)
	 {
		 cout << head->number << endl;
		 head = head->nextNode;
	 }
	 cout << endl << "Would you like to do this again? Type 1 to do so, any other number if you do not" << endl;
	 cin >> i;
}

	return 0;
}

