/*
Name: Chet Michals
Date: Febuary 23rd, 2011
Class: Computer Science I, COP3502
Assignment #3, Match-Making
Purpose: To read in a file containing a list of names and how they score each other, and find the max compatibilty via a recursive function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pairs{
int score;// Hold the indexSize score
int indexNumber; //Holds the number of pairs there are
int *caseNumX; //Pointer for dynamically alloticated array that will hold the IDs of the males in order they will be printed to screen
int *caseNumY; //Pointer for dynamically alloticated array that will hold the IDs of the females in order they will be printed to screen
}Storage;

//Linked List to store 
struct ScoreData{
	int *localScores; //Pointer for array that will by dynamically alloticated, which holds the scores for the oppiset sex
	int ID; //Hold ID of particaller element
	char name[256]; //Holds person's name
	struct ScoreData *next;
};


//Function Defintions

int Smaller(int x, int y);
int CompareNumbers(int x, int y, struct ScoreData *Data, int indexSize);

struct ScoreData* AppendName(struct ScoreData* Head, char * Name);
struct ScoreData* MakeEmptySet();

void Permutation(struct ScoreData *Data, int indexSize, int countup, int score, int indexX[], int indexY[]);
void CheckAndStore(int score, int indexNumber, int indexX[], int indexY[]);
void ProcessFile(FILE *inputFile, FILE *output);
void AppendScores(struct ScoreData* Head, int Scores[], int ID, int indexSize);
void InitalizeStorage();
void PrintInfo(int matchNum, struct ScoreData* Data, FILE *output);



int main()
{
	FILE *inputFile=NULL;//make file pointer for reading in
	FILE *outputFile = NULL;//makes file pointer for output
	inputFile=fopen("input.txt", "r");//open file
	outputFile=fopen("out.txt", "w");//create/open file
	
	ProcessFile(inputFile, outputFile);


	fclose(inputFile);
	fclose(outputFile);

	return 0;
}

//Main driver for the Permutation of the data. It is a recursive function that takes in the linked list storing the data
//indexSize, The number of pairs, countup, an entry to note how many Permutations have been done 
//on the leaf (When first callikng should be 0), the score of the prevous entires (Should also be zero when first called),
//and two entires for the arraies containing the IDs of the people
void Permutation(struct ScoreData *Data, int indexSize, int countup, int score, int indexX[], int indexY[])
{
	//Pointers for Local Arrays sets
	int* LocalXIndex;
	int* LocalYIndex;

	int SmallerNumber = 0, tempXIndex = 0, tempYIndex = 0;
	int i = 0, j = 0; //Used for For Loops

	//Dyamically size local arrays
	LocalXIndex = (int*) malloc(indexSize*sizeof(int));
	LocalYIndex = (int*) malloc(indexSize*sizeof(int));

	//Copy passed in array to Local version of array
	for (i = 0; i < indexSize; i++)
	{
		LocalXIndex[i] = indexX[i];
		LocalYIndex[i] = indexY[i];
	}

	for (i = countup; i < indexSize; i++)
	{
		//Copy element at i to element at countup
		tempXIndex = LocalXIndex[i];
		LocalXIndex[i] = LocalXIndex[countup];
		LocalXIndex[countup] = tempXIndex;

		for (j = countup; j < indexSize; j++)
		{
			//Copy element at i to element at countup
			tempYIndex = LocalYIndex[j];
			LocalYIndex[j] = LocalYIndex[countup];
			LocalYIndex[countup] = tempYIndex;

			//Get the score for the current two people being tested, and pass it to the next Permutation function call
			SmallerNumber = CompareNumbers(LocalXIndex[countup], LocalYIndex[countup], Data, indexSize);
			Permutation(Data, indexSize, (countup+1), (SmallerNumber+score) , LocalXIndex, LocalYIndex);

			//Restore local array to way it was passed in
			LocalYIndex[countup]= LocalYIndex[j];
			LocalYIndex[j]=tempYIndex;
		}

		//Restore local array to way it was passed in
		LocalXIndex[0] = LocalXIndex[i];
		LocalXIndex[i] = tempXIndex;
	}
	//When count up and indexSize are equel, that means it has gone though every pair for that leaf, and needs to compare and save away information on the leaf
	if (countup == indexSize){CheckAndStore(score, indexSize, LocalXIndex, LocalYIndex);}

}

//A simple function to return the small of two passed in ints
int Smaller(int x, int y)
{
	if (x > y) return y;
	return x;
}

//Identify the correct numbers at indexes X and Y in the Data ScoreData linked list to pass to the Smaller function 
int CompareNumbers(int x, int y, struct ScoreData *Data, int indexSize)
{
	
	int i=0; //Used for loop
	int returnNumber;//Stores number that is returned from Smaller Function to be returend
		
	//Pointers for Dynamic Arrays
	int* LocalArrayX;
	int* LocalArrayY;

	struct ScoreData *Temp; //Pointer for local linked list element

	//Creates Dynamic Arrays and linked list element
	LocalArrayX = (int*) malloc(indexSize*sizeof(int));
	LocalArrayY = (int*) malloc(indexSize*sizeof(int));
	Temp = (struct ScoreData *)malloc(sizeof(struct ScoreData));
	
	Temp = Data; //Sets the pointer at Temp to the pointer at Data
	while(Temp->ID != x) {Temp=Temp->next;} //Advances pointer till the ID matches index x
	for (i = 0; i < indexSize; i++)	{LocalArrayX[i] = Temp->localScores[i];} //Copies the array at the linked list entry to the local array

	Temp = Data;
	while(Temp->ID != y) {Temp=Temp->next;}//Advances pointer till the ID matches index y
	for (i = 0; i < indexSize; i++)	{LocalArrayY[i] = Temp->localScores[i];}//Copies the array at the linked list entry to the local array

	returnNumber=Smaller(LocalArrayX[(y-1)%indexSize],LocalArrayY[(x-1)%indexSize]);//Passes in the two relivant array entires

	return returnNumber;
}

//Checks the score of a finished leaf with the current highest known score.
//If higher, store the info
void CheckAndStore(int score, int indexNumber, int indexX[], int indexY[])
{
	int i = 0; //Used in loop
	if (score > Storage.score) //Checks if the score is higher if current highest score
	{
		Storage.score = score; //Save new score
		Storage.indexNumber = indexNumber;//Writes index number size
		Storage.caseNumX = (int*) malloc(indexNumber*sizeof(int)); //Makes new dynamic array for males
		Storage.caseNumY = (int*) malloc(indexNumber*sizeof(int)); //Makes new dynamic array for females
		for (i = 0; i < indexNumber; i++) //copies the passed in arrays to the Storagd arraies
		{
			Storage.caseNumX[i] = indexX[i];
			Storage.caseNumY[i] = indexY[i];
		}
	}
}

//Makes a ScoreData linked list with only a single entry, containing the unused ID 0.
struct ScoreData* MakeEmptySet()
{
	struct ScoreData *First;
	First = (struct ScoreData *)malloc(sizeof(struct ScoreData));
	First->ID = 0;
	First->next = NULL;
	return First;
}

//Adds a new entires to the passed in scoreData linked list, and stores the passed in name to it, along with an ID value
struct ScoreData* AppendName(struct ScoreData* Head, char * Name)
{
	int localID=(Head->ID + 1);
	struct ScoreData *Local;
	Local = (struct ScoreData *)malloc(sizeof(struct ScoreData));
	strcpy(Local->name,Name);
	Local->ID = localID;
	Local->next=Head;
	Head = Local;
	return Head;
}

//Appends the array of scores to the element with the passed in ID. 
void AppendScores(struct ScoreData* Head, int Scores[], int ID, int indexSize)
{
	int i;
	struct ScoreData *Local;
	//Makes new local elment for indexing passed in linked list
	Local = (struct ScoreData *)malloc(sizeof(struct ScoreData));
	Local = Head;

	while (Local->ID != ID){Local = Local->next;}//Advances local list till the ID values match
	Local->localScores = (int*) malloc(indexSize*sizeof(int));//Dynamically alloticate new array

	//Used to copy the passed in array to the array in the linked list entry
	for (i = 0; i < indexSize; i++)
	{
		Local->localScores[i] = Scores[i];
	}
}

//Takes the input files and output file pointer and process them
void ProcessFile(FILE *inputFile, FILE *output)
{
	
	int indexSize, datasets, i, j, k; //Used for the loops
	int *tempArray, *indexX, *indexY; //Pointers for dynamic arrays
	char tempString[1024]; //Stores a line from the input file to be tokenized
	char * name;//pointer used for tokens
	struct ScoreData *First;//Creates Main Linked List Entry
	

	fgets(tempString, 1024, inputFile);//Gets first line of text, which has the total number of sets of data to process
	datasets = atoi(tempString);//Chagnes string to int

	for (k = 0; k < datasets; k++) //Loops though total number of data sets
	{
		First = MakeEmptySet(); //Creates a new Linked List Element
		fgets(tempString, 1024, inputFile); //Gets line of text containing number of pairs of people
		indexSize = atoi(tempString);//Sets text to an int
	
		for (j = 0; j < 2; j++) //There will be one set of males, and one set of females
		{
			fgets(tempString, 1024, inputFile); //Gets the line of text which contains the names
			for (i = 0; i < indexSize; i++)//Tokenizes names
			{
				if (i == 0) {name = strtok(tempString, " \n");}
				else {name = strtok(NULL, " \n");}
				First = AppendName(First, name); //Pushes the names onto the linked list
			}
		}


		for (i = 0; i < (indexSize*2); i++) //Gets lines of text which contains the scores
		{
			tempArray = (int*) malloc(indexSize*sizeof(int)); //Creates new dynamic array for holding current score entires
			fgets(tempString, 1024, inputFile); //Gets next line of text
			for (j = 0; j < indexSize; j++) //Puts entries from line of text onto array
			{
				if (j == 0) {name = strtok(tempString, " \n");}
				else {name = strtok(NULL, " \n");}
				tempArray[j] = atoi(name);
			}
			AppendScores(First, tempArray, (i+1), indexSize); //Assigns array to propper linked list entires
		}

		indexX = (int*) malloc(indexSize*sizeof(int));
		indexY = (int*) malloc(indexSize*sizeof(int));

		for (i = 0; i < indexSize; i++)
		{
			indexX[i] = (i+1);
			indexY[i] = (i+1+indexSize);
		}
		InitalizeStorage();
		Permutation(First, indexSize, 0, 0, indexX, indexY);
		PrintInfo(k+1, First, output);
	}
}

//Resets the score entry in the storage object
void InitalizeStorage()
{
	Storage.score = 0;
}


//Prints out the data in the correct format to a file
void PrintInfo(int matchNum, struct ScoreData* Data, FILE *output)
{
	int i;
	struct ScoreData *Local;
	Local = (struct ScoreData *)malloc(sizeof(struct ScoreData));
	fprintf(output,"Matching #%d: Maximum Score = %d\n\n", matchNum, Storage.score);
	for (i = 0; i < Storage.indexNumber; i++)
	{
		Local = Data;
		while (Local->ID!=Storage.caseNumX[i]){Local=Local->next;}
		fprintf(output,"%s ",Local->name);

		Local = Data;
		while (Local->ID!=Storage.caseNumY[i]){Local=Local->next;}
		fprintf(output,"%s\n",Local->name);
	}
	fprintf(output,"\n\n");
}
