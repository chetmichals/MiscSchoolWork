#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structer Prototypes
struct treenode;
struct buddyList;

typedef struct treenode {
	int ID;
	char firstName[21];
	char lastName[21];
	int age;
	struct buddyList *myBuddies;
	int numBuddies;
	struct treenode *left;
	struct treenode *right;
};

typedef struct buddyList {
	struct treenode *buddy;
	struct buddyList *next;
};


//Main Command Functions, all take in just the full line of text and tokenize it within the function to get the varrables
void cAdd(char *CommandLine, struct treenode *Head, FILE *output);
void cFindName(char *CommandLine, struct treenode *Head, FILE *output);
void cFindID(char *CommandLine, struct treenode *Head, FILE *output);
void cBuddy(char *CommandLine, struct treenode *Head, FILE *output);
void cUnbuddy(char *CommandLine, struct treenode *Head, FILE *output);
void cDelete(char *CommandLine, struct treenode *Head, FILE *output);
void cPrintBuddies(char *CommandLine, struct treenode *Head, FILE *output);
void cPrintTree(struct treenode *Head, FILE *output);

void DeleteUnbuddy(struct treenode *Caller, struct treenode *Head);
struct treenode *EmptyNode();
struct treenode *TreeTraversalAdd(struct treenode *Head, char *First, char *Last);
struct treenode *FindNode(struct treenode *Head, char *First, char *Last);
struct treenode *SmallestToRight(struct treenode *Local);
void AlreadyBuddy(char *firstA, char *lastA, char *firstB, char *lastB, FILE *output);
void RunLoop(FILE *input, FILE *output);
int CompareInts(const void * a, const void * b);
int *SortBuddies(struct treenode *local);

int main()
{
	FILE *inputFile=NULL;//make file pointer for reading in
	FILE *outputFile = NULL;//makes file pointer for output
	inputFile=fopen("buddyBook.in", "r");//open file
	outputFile=fopen("buddyBook.out", "w");//create/open file

	RunLoop(inputFile,outputFile);

	//closes file
	fclose(inputFile);
	fclose(outputFile);

	return 0;
}

//Add a new node to the correct spot
void cAdd(char *CommandLine, struct treenode *Head, FILE *output)
{
	//ID is set to -1 when the head is first initalized
	char *First;
	char *Last;
	int age;
	int ID;

	struct treenode *Local;
	Local = Head;

	//Tokenize CommandLine and extract the information from it. First token is the command, which gets tossed out
	strtok(CommandLine," \n");
	ID = atoi(strtok(NULL," \n"));
	First = strtok(NULL," \n");
	Last = strtok(NULL," \n");
	age = atoi(strtok(NULL," \n"));

	//Person must be over 13, prints error message if over age
	if(age < 13){fprintf(output,"%s %s rejected - You must be 13 or over to create a profile.\n",First,Last);return;}
	
	//Local ID will be -1 during inizalation
	if(Local->ID != -1) 
	{
		Local = TreeTraversalAdd(Local,First,Last);
		if (Local->ID == -1)  //If the person is already in the list
		{
			fprintf(output,"%s %s is already a member of Buddy Book.\n",First,Last);
			return;
		}
	}
	else //If inizalized, makes a new node
		Local = (struct treenode *)malloc(sizeof(struct treenode));

	

	//Copy data into the node and initzlizes the rest of the fields
	strcpy(Local->firstName, First);
	strcpy(Local->lastName, Last);
	Local->age = age;
	Local->ID = ID;
	Local->left = NULL;
	Local->right = NULL;
	Local->numBuddies = 0;
	Local->myBuddies = (struct buddyList *)malloc(sizeof(struct buddyList));

	//Prints that node was added
	fprintf(output,"Added %s %s, age %d\n",First,Last,age);
	//Set Head to Local if Head hasn't been inilized
	if(Head->ID == -1) *Head = *Local;
}

//Will return address of a new node in the correct spot to have data put into
struct treenode *TreeTraversalAdd(struct treenode *Head, char *First, char *Last)
{
	int Compare = 1;	
	struct treenode *Local;
	struct treenode *Next;
	Next = Local = Head;

	//Go to the bottom of the tree till the node pointer is in the right spot
	while(Next != NULL && Compare != 0)
	{
		Local = Next;
		Compare = strcmp(Last,Local->lastName);
		if(Compare == 0) //Compare First Names
			Compare = strcmp(First,Local->firstName);
		if(Compare < 0) Next = Next->left;
		else Next = Next->right;
	}
	//Makes a new node in the correct spot, and returns it
	if(Compare < 0)
	{
		Local->left = (struct treenode *)malloc(sizeof(struct treenode));
		return Local->left;
	}
	else if(Compare > 0)
	{
		Local->right =  (struct treenode *)malloc(sizeof(struct treenode));
		return Local->right;
	}
	else //If person is already in Tree
	{
		return EmptyNode();
	}
}

//Search the tree and print the info (If given name)
void cFindName(char *CommandLine, struct treenode *Head, FILE *output)
{
	char *First;
	char *Last;

	//Make and set a local treenode to head
	struct treenode *Local;
	Local = Head;

	//Tokenize CommandLine and extract the information from it. First token is the command, which gets tossed out
	strtok(CommandLine," \n");
	First = strtok(NULL," \n");
	Last = strtok(NULL," \n");

	//Set Local to the node with the passed in name
	Local = FindNode(Head,First,Last);
	//Name not found

	if(Local->ID == -1)
	{
		fprintf(output,"%s %s not found.\n",First,Last);
		return;
	}
	//Name found, print info
	else
	{
		fprintf(output,"Found:  %s %s, age %d, ",First,Last,Local->age);
		if (Local->numBuddies==1) fprintf(output,"1 Buddy\n");
		else fprintf(output,"%d Buddies\n",Local->numBuddies);
	}
}

//Search the tree and print the info (If given ID)
void cFindID(char *CommandLine, struct treenode *Head, FILE *output)
{
	int ID;
	int Compare = 1;
	struct treenode *Local;
	Local = Head;

	//Tokenize CommandLine and extract the information from it. First token is the command, which gets tossed out
	strtok(CommandLine," \n");
	ID = atoi(strtok(NULL," \n"));

	//Search the Tree for the ID
	while(Local != NULL && Compare!=0)
	{
		Compare = ID - Local->ID;
		if(Compare < 0) Local = Local->left;
		if(Compare > 0) Local = Local->right;
	}
	//Local will be null if ID is never found
	if(Local == NULL)
	{
		fprintf(output,"ID %d not found.\n",ID);
		return;
	}
	//Compare is 0, meaning ID was found, print info
	else
	{
		fprintf(output,"Found:  %s %s, age %d, ",Local->firstName,Local->lastName,Local->age);
		if (Local->numBuddies==1) fprintf(output,"1 Buddy\n");
		else fprintf(output,"%d Buddies\n",Local->numBuddies);
	}
}

//Add two people to each other's buddy lists
void cBuddy(char *CommandLine, struct treenode *Head, FILE *output)
{
	char *FirstA, *LastA;
	char *FirstB, *LastB;
	int i = 0;

	struct treenode *NodeA;
	struct treenode *NodeB;
	struct buddyList *tempBuddy;

	strtok(CommandLine," \n");
	FirstA = strtok(NULL," \n");
	LastA = strtok(NULL," \n");
	FirstB = strtok(NULL," \n");
	LastB = strtok(NULL," \n");

	//Sets the Local Nodes address to the address of the nodes containing the two people to buddy
	NodeA = FindNode(Head,FirstA,LastA);
	NodeB = FindNode(Head,FirstB,LastB);

	//If ether person doesn't exsist
	if (NodeA->ID == -1 || NodeB->ID == -1)
	{
		fprintf(output,"Cannot Perform BUDDY Command:\n");
		if (NodeA->ID == -1) fprintf(output,"   %s %s - This profile does not exist.\n",FirstA,LastA);
		if (NodeB->ID == -1) fprintf(output,"   %s %s - This profile does not exist.\n",FirstB,LastB);
		return;
	}
	
	
	//Adds the buddies to each others lists
	//Check if they are already buddies, check is also done again within loop
	if (NodeA->numBuddies != 0 && NodeA->myBuddies->buddy->ID == NodeB->ID){AlreadyBuddy(FirstA,LastA,FirstB,LastB,output);return;}

	tempBuddy = NodeA->myBuddies; //Keep track of heads orignal address
	//Since the number of buddies is kept track of, you can just use a for loop to cycle though the list
	for(i = 0; i < NodeA->numBuddies; i++)
	{
		if (NodeA->myBuddies->buddy->ID == NodeB->ID){AlreadyBuddy(FirstA,LastA,FirstB,LastB,output); NodeA->myBuddies=tempBuddy; return;}
		NodeA->myBuddies = NodeA->myBuddies->next;
		
	}
	NodeA->myBuddies->next = (struct buddyList *)malloc(sizeof(struct buddyList)); //Inilize next node
	NodeA->myBuddies->next->buddy = EmptyNode();

	NodeA->myBuddies->buddy = NodeB;
	NodeA->myBuddies = tempBuddy; //Puts orignal address of buddy book back
	
	tempBuddy = NodeB->myBuddies;
	//Since the number of buddies is kept track of, you can just use a for loop to cycle though the list
	for(i = 0; i < NodeB->numBuddies; i++) 
		NodeB->myBuddies = NodeB->myBuddies->next;
	NodeB->myBuddies->next = (struct buddyList *)malloc(sizeof(struct buddyList));
	NodeB->myBuddies->next->buddy = EmptyNode();
	NodeB->myBuddies->buddy = NodeA;
	NodeB->myBuddies = tempBuddy;
	//Increase the number of buddies
	NodeA->numBuddies++;
	NodeB->numBuddies++;
	fprintf(output,"%s %s and %s %s are now Buddies.\n",FirstA,LastA,FirstB,LastB);
}

//Returns the address of the node where the passed in name matches, or an empty node if not found
struct treenode *FindNode(struct treenode *Local, char *First, char *Last)
{
	int Compare = 1;

	//Search the Tree for a name
	while(Local != NULL && Compare!=0)
	{
		//Check last name first
		Compare = strcmp(Last,Local->lastName);
		if(Compare == 0) //Same last name, so check First Names
			Compare = strcmp(First,Local->firstName);
		if(Compare < 0) Local = Local->left;
		if(Compare > 0) Local = Local->right;
	}
	//Name not found, returns empty node
	if(Local == NULL)
	{
		return EmptyNode();
	}
	//Name found, return node
	else
	{
		return Local;
	}
}

//Makes a node with an ID of -1
struct treenode *EmptyNode()
{
	//A node with an ID of -1 is "Empty", this makes a new node and sets its ID to -1.
	struct treenode *Local;
	Local = (struct treenode *)malloc(sizeof(struct treenode));
	Local->ID = -1;
	Local->left = NULL;
	Local->right = NULL;
	return Local;
}

//Removes two people from each others buddy lists
void cUnbuddy(char *CommandLine, struct treenode *Head, FILE *output)
{
	char *FirstA, *LastA;
	char *FirstB, *LastB;
	int i = 0;
	int TempID;

	struct treenode *NodeA;
	struct treenode *NodeB;
	struct buddyList *tempBuddy;
	struct buddyList *tempLast;
	struct treenode *TempNode;

	strtok(CommandLine," \n");
	FirstA = strtok(NULL," \n");
	LastA = strtok(NULL," \n");
	FirstB = strtok(NULL," \n");
	LastB = strtok(NULL," \n");

	//Sets the Local Nodes address to the address of the nodes containing the two people to buddy
	NodeA = FindNode(Head,FirstA,LastA);
	NodeB = FindNode(Head,FirstB,LastB);
	
	//If ether names does not exsist
	if (NodeA->ID == -1 || NodeB->ID == -1)
	{
		fprintf(output,"Cannot Perform UNBUDDY Command:\n");
		if (NodeA->ID == -1) fprintf(output,"   %s %s - This profile does not exist.\n",FirstA,LastA);
		if (NodeB->ID == -1) fprintf(output,"   %s %s - This profile does not exist.\n",FirstB,LastB);
		return;
	}

//Start Unbudy of A

	TempID = NodeB->ID;
	tempBuddy = NodeA->myBuddies; //Keeps track of orignal Head Location
	//Go though the for loop looking for where the the ID of person B is in the budd
	for(i = 0; i < NodeA->numBuddies && TempID != NodeA->myBuddies->buddy->ID; i++)
	{
		tempLast = NodeA->myBuddies;
		NodeA->myBuddies = NodeA->myBuddies->next;
	}

	//If the two people are not buddies
	if (NodeA->numBuddies == 0 || NodeB->numBuddies == 0 || NodeA->myBuddies->buddy->ID != TempID)
	{
		fprintf(output,"Cannot Perform UNBUDDY Command:\n");
		fprintf(output,"   %s %s and %s %s are not currently Buddies.\n",FirstA,LastA, FirstB, LastB);
		NodeA->myBuddies = tempBuddy;
		return;
	}

	//If tempLast is not the first or last element
	if (i != 0 && i != NodeA->numBuddies)
	{
		tempLast->next = tempLast->next->next; 
		NodeA->myBuddies = tempBuddy;
	}
	else if (i == 0) //If buddy is in first node 
	{
		NodeA->myBuddies = NodeA->myBuddies->next;
	}
	else//If buddy is in last node
	{
		NodeA->myBuddies->next =  (struct buddyList *)malloc(sizeof(struct buddyList));
		NodeA->myBuddies = tempBuddy;
	}

//End Unbuddy of A, Start Unbuddy of B
	
	//Just switches the two nodes, so code doesn't have to be changed
	TempNode = NodeA;
	NodeA = NodeB;
	NodeB = TempNode;

	TempID = NodeB->ID;
	tempBuddy = NodeA->myBuddies; //Keeps track of orignal Head Location
	//Go though the for loop 
	for(i = 0; i < NodeA->numBuddies && TempID != NodeA->myBuddies->buddy->ID; i++)
	{
		tempLast = NodeA->myBuddies;
		NodeA->myBuddies = NodeA->myBuddies->next;
	}

	//If tempLast is not the first or last element
	if (i != 0 && i != NodeA->numBuddies)
	{
		tempLast->next = tempLast->next->next; 
		NodeA->myBuddies = tempBuddy;
	}
	else if (i == 0)
	{
		NodeA->myBuddies = NodeA->myBuddies->next;
	}
	else
	{
		NodeA->myBuddies->next =  (struct buddyList *)malloc(sizeof(struct buddyList));
		NodeA->myBuddies = tempBuddy;
	}

	NodeA->numBuddies--;
	NodeB->numBuddies--;

	fprintf(output,"%s %s and %s %s are no longer Buddies.\n",FirstA,LastA, FirstB, LastB);

}

//Rewriten version of Unbuddy, specally made to allow for unbuddying of all buddies of a Deleted Person
void DeleteUnbuddy(struct treenode *Caller, struct treenode *Head)
{
	int i = 0;
	int TempID;
	//char FirstA[22],LastA[22];

	struct treenode *NodeA;
	struct treenode *NodeB;
	struct treenode *TempNode;
	struct buddyList *tempBuddy;
	struct buddyList *tempLast;

	//strcpy(FirstA,Caller->myBuddies->buddy->firstName);
	//strcpy(LastA,Caller->myBuddies->buddy->lastName);


	//Sets the Local Nodes address to the address of the nodes containing the two people to unbuddy
	//NodeA = FindNode(Head,FirstA,LastA);
	NodeA = Caller->myBuddies->buddy;
	NodeB = Caller;

//Start Unbudy of A

	TempID = NodeB->ID;
	tempBuddy = NodeA->myBuddies; //Keeps track of orignal Head Location
	//Go though the for loop looking for where the the ID of person B is in the budd
	for(i = 0; i < NodeA->numBuddies && TempID != NodeA->myBuddies->buddy->ID; i++)
	{
		tempLast = NodeA->myBuddies;
		NodeA->myBuddies = NodeA->myBuddies->next;
	}

	//If tempLast is not the first or last element
	if (i != 0 && i != NodeA->numBuddies)
	{
		tempLast->next = tempLast->next->next; 
		NodeA->myBuddies = tempBuddy;
	}
	else if (i == 0) //If buddy is in first node 
	{
		NodeA->myBuddies = NodeA->myBuddies->next;
	}
	else//If buddy is in last node
	{
		NodeA->myBuddies->next =  (struct buddyList *)malloc(sizeof(struct buddyList));
		NodeA->myBuddies = tempBuddy;
	}

//End Unbuddy of A, Start Unbuddy of B
	
	//Just switches the two nodes, so code doesn't have to be changed
	TempNode = NodeA;
	NodeA = NodeB;
	NodeB = TempNode;

	TempID = NodeB->ID;
	tempBuddy = NodeA->myBuddies; //Keeps track of orignal Head Location
	//Go though the for loop 
	for(i = 0; i < NodeA->numBuddies && TempID != NodeA->myBuddies->buddy->ID; i++)
	{
		tempLast = NodeA->myBuddies;
		NodeA->myBuddies = NodeA->myBuddies->next;
	}

	//If tempLast is not the first or last element
	if (i != 0 && i != NodeA->numBuddies)
	{
		tempLast->next = tempLast->next->next; 
		NodeA->myBuddies = tempBuddy;
	}
	else if (i == 0)
	{
		NodeA->myBuddies = NodeA->myBuddies->next;
	}
	else
	{
		NodeA->myBuddies->next =  (struct buddyList *)malloc(sizeof(struct buddyList));
		NodeA->myBuddies = tempBuddy;
	}

	NodeA->numBuddies--;
	NodeB->numBuddies--;
}

void cDelete(char *CommandLine, struct treenode *Head, FILE *output)
{
	char *First;
	char *Last;
	int Compare = 1;
	int OldCompare = 1;
	struct treenode *Temp;
	struct treenode *Local;
	struct treenode *LastNode;
		
	//Tokenize CommandLine and extract the information from it. First token is the command, which gets tossed out
	strtok(CommandLine," \n");
	First = strtok(NULL," \n");
	Last = strtok(NULL," \n");

	Local = Head;
	LastNode = Local;
	Temp = Local;
	//Search the Tree for a name
	while(Temp != NULL && Compare!=0)
	{
		OldCompare = Compare;
		LastNode = Local;
		Local = Temp;
		//Check last name first
		Compare = strcmp(Last,Temp->lastName);
		if(Compare == 0) //Same last name, so check First Names
			Compare = strcmp(First,Temp->firstName);
		if(Compare < 0) Temp = Temp->left;
		if(Compare > 0) Temp = Temp->right;
	}
	//Name not found, returns error
	if(Temp  == NULL)
	{
		fprintf(output,"Cannot Perform DELETE Command:\n");
		fprintf(output,"   %s %s - This profile does not exist.\n",First,Last);
		return;
	}

	//Deletes all buddies
	while (Local->numBuddies != 0)
	{
		DeleteUnbuddy(Local,Head);
	}
	Compare = OldCompare;

	//If the node being deleted is the head and only node
	if(Temp->ID == Local->ID && Local->ID == LastNode->ID && Local->left == NULL && Local->right == NULL)
	{
		*Head = *EmptyNode();
	}
	//If the node being deleted is the head and has one kid
	else if(Temp->ID == Local->ID && Local->ID == LastNode->ID && !(Local->left!=NULL && Local->right != NULL))
	{
		if(Local->left != NULL) *Head = *Local->left;
		else *Head = *Local->right;

	}
	//If the node was a leaf
	else if(Local->left == NULL && Local->right == NULL)
	{
		if(Compare < 0) LastNode->left = NULL;
		else LastNode->right = NULL;
	}
	//Next two are if the node had one child
	else if(Local->left != NULL && Local->right == NULL)
	{
		if(Compare < 0) LastNode->left = Local->left;
		else LastNode->right = Local->left;
	}
	else if(Local->right != NULL && Local->left == NULL)
	{
		if(Compare < 0) LastNode->left = Local->right;
		else LastNode->right = Local->right;
	}
	//If the node had two childern
	else if (LastNode->ID != Local->ID)
	{
		if(Compare < 0)
		{
			LastNode->left = SmallestToRight(Local); //Get the node that will go in the place of the deleted node 
			//Make sure the next node set is not the node removed
			if (Local->left != NULL && Local->left->ID != LastNode->left->ID) LastNode->left->left = Local->left;
			if (Local->right != NULL && Local->right->ID != LastNode->left->ID) LastNode->left->right = Local->right;
		}
		else
		{
			LastNode->right = SmallestToRight(Local); //Get the node that will go in the place of the deleted node 
			//Make sure the next node set is not the node removed
			if (Local->right != NULL && Local->left->ID != LastNode->right->ID) LastNode->right->left = Local->left;
			if (Local->right != NULL && Local->right->ID != LastNode->right->ID) LastNode->right->right = Local->right;
		}
	}
	else //If the node removed was the head
	{
		LastNode = SmallestToRight(Local); //Get the node that will go in the place of the deleted node 
		//Make sure the next node set is not the node removed
		LastNode->left = Local->left;
		if (Local->right->ID != LastNode->ID) LastNode->right = Local->right;
		*Head = *LastNode;
	}
	fprintf(output,"Deleted %s %s.\n",First,Last);
}

//Gets the node that needs to be removed in a delete function if the deleted node has two kids
struct treenode *SmallestToRight(struct treenode *Local)
{
	struct treenode *tempNode;
	//The node to get is the smallest node in the right branch. As such, we first must go right once, then as far left as we can
	Local = Local->right;
	tempNode = EmptyNode();
	while (Local->left != NULL)
	{
		tempNode = Local;
		Local = Local->left;
	}
	tempNode->left = Local->right;
	return Local;
}

void RunLoop(FILE *input, FILE *output)
{
	struct treenode *BSTHead; //Pointer to head of Binary Search Tree
	char CommandLine[1024];
	char Command[1024];
	int i, j;
	//int debug;
	//char DebugLine[1024];
	//FILE *out2 = NULL;//makes file pointer for output
	BSTHead = EmptyNode();

	//First line of file has the number of commands to be run
	j = atoi(fgets(CommandLine, 1024, input));
	for (i=0;i<j;i++)
	{
//		DEBUG
		//if (i >= 2200 && i && i%100 == 0){
		//	debug = 1;
		//	//strcpy(DebugLine,"PRINTBUDDIES Vanesa Zingaro");
		//	//cPrintBuddies(DebugLine,BSTHead,out2);
		//	strcpy(DebugLine,"PRINTTREE");
		//	//cPrintBuddies(DebugLine,BSTHead,out2);
		//	fprintf(out2,"%d\n",i);
		//	cPrintTree(BSTHead,out2);
		//	if (i == 6100) return;
		//}
		//
		//if (i == 1098)
		//	debug =1;
		//END DEBUG

		fgets(CommandLine, 1024, input);
		strcpy(Command,CommandLine);
		strcpy(Command,strtok(Command," \n"));

		if (strcmp(Command,"ADD")==0) 
			cAdd(CommandLine,BSTHead,output);
		else if (strcmp(Command,"FINDNAME")==0) cFindName(CommandLine,BSTHead,output);
		else if (strcmp(Command,"FINDID")==0) cFindID(CommandLine,BSTHead,output);
		else if (strcmp(Command,"BUDDY")==0) 
			cBuddy(CommandLine,BSTHead,output);
		else if (strcmp(Command,"UNBUDDY")==0) 
			cUnbuddy(CommandLine,BSTHead,output);
		else if (strcmp(Command,"DELETE")==0) 
			cDelete(CommandLine,BSTHead,output);
		else if (strcmp(Command,"PRINTBUDDIES")==0) 
			cPrintBuddies(CommandLine,BSTHead,output);
		else if (strcmp(Command,"PRINTTREE")==0)
		{
			if (BSTHead->ID == -1)
			{
				fprintf(output,"Cannot Perform PRINTTREE Command: \n");
				fprintf(output,"   There are currently no members of Buddy Book\n");
			}
			else
			{
				fprintf(output,"Members of Buddy Book:\n");
				cPrintTree(BSTHead,output);
			}
		}
	}
}

void AlreadyBuddy(char *firstA, char *lastA, char *firstB, char *lastB, FILE *output)
{
	fprintf(output,"Cannot Perform BUDDY Command:\n");
	fprintf(output,"   %s %s and %s %s are already Buddies.\n",firstA,lastA,firstB,lastB);
}

void cPrintBuddies(char *CommandLine, struct treenode *Head, FILE *output)
{
	char *First;
	char *Last;
	int *BuddyArray;
	int i, j;
	//Make and set a local treenode to head
	struct treenode *Local;
	struct buddyList *tempList;
	Local = Head;

	//Tokenize CommandLine and extract the information from it. First token is the command, which gets tossed out
	strtok(CommandLine," \n");
	First = strtok(NULL," \n");
	Last = strtok(NULL," \n");
	Local = FindNode(Head,First,Last);
	//Name not found

	if(Local->ID == -1)
	{
		fprintf(output,"Cannot Perform PRINTBUDDIES Command:\n");
		fprintf(output,"   %s %s - This profile does not exist.\n",First,Last);
		return;
	}
	//Print the number of buddies
	fprintf(output,"%s %s has ",Local->firstName,Local->lastName);
	if (Local->numBuddies == 1) fprintf(output,"%d Buddy:\n",Local->numBuddies);
	else if (Local->numBuddies == 0)  fprintf(output,"no Buddies.\n");
	else fprintf(output,"%d Buddies:\n",Local->numBuddies);

	tempList = Local->myBuddies;

	//If Buddies is 1, just skip the sorting
	if (Local->numBuddies == 1){fprintf(output,"   %s %s\n",tempList->buddy->firstName,tempList->buddy->lastName);return;}
	else 
	{
		BuddyArray = SortBuddies(Local);
		//Print the buddies in order that they apper in the BuddyArray, which is sorted
		for(i = 0; i < Local->numBuddies; i++)
		{
			tempList = Local->myBuddies;
			//Go though each buddy till a match is found
			for(j = 0; j < Local->numBuddies; j++)
			{
				if(BuddyArray[i] == tempList->buddy->ID)
				{
					fprintf(output,"   %s %s\n",tempList->buddy->firstName,tempList->buddy->lastName);
					j = Local->numBuddies;
				}
				else
					tempList = tempList->next;
			}
		}
	}
}


int *SortBuddies(struct treenode *local)
{
	struct buddyList *tempList;
	int *NameArray;
	int i;
	tempList = local->myBuddies;
	//Dynamically makes array
	NameArray = malloc(local->numBuddies * sizeof(int));
	//Sets array entries
	for(i = 0; i < local->numBuddies; i++)
	{
		NameArray[i] = tempList->buddy->ID;
		tempList=tempList->next;
	}
	//Sorts array, using the CompareInts fucntion for comparason
	qsort (NameArray,local->numBuddies, sizeof(int), CompareInts);
	return NameArray;
}

//Function used by quick sort to compare two interger values
int CompareInts(const void * a, const void * b)
{
	//Typecasts the two passed in values as ints, then subtracts one from the other, and returns the value, like strcmp
	return ( *(int*)a - *(int*)b );
}

//A recursive formula to print the tree inorder
void cPrintTree(struct treenode *Head, FILE *output)
{
	//If there is a left child, call Print Tree for it
	if (Head->left != NULL) cPrintTree(Head->left, output);
	//Print info about root
	fprintf(output,"   %s %s, age %d, ",Head->firstName,Head->lastName,Head->age);
	if(Head->numBuddies == 1) fprintf(output,"1 Buddy\n");
	else fprintf(output,"%d Buddies\n",Head->numBuddies);

	//If there is a right child, call print tree for it
	if (Head->right != NULL) cPrintTree(Head->right, output);
}
