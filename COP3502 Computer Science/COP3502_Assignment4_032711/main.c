// Chet Michals
// Program 4,  TA Lab
// March 27th, 2011

// Note about General Convention, if the Queues next points to the same node, it means the line is empty.



//Header Files
#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Structer for Student
struct student {
char firstName[40];
char lastName[40];
int enterTime;
int numQuestions;
int numAnswered;
int laptopSerialNum;
};
//Structer of TA
struct teachingAssistant {
char name[40];  // only use first names for the TAs
int startTimes[3];
int endTimes[3];
struct student studentWithTA;
int minute;
};
//Structer for the Nodes to the Queues to TALine and Laptop Line
struct StudentQueue
  {  
     struct student kid;
     struct StudentQueue *next;
  };
//Structer to Laptop Stack Nodes
struct LaptopStack
  {  
     int laptopID;
     struct LaptopStack *next;
  }; 

//Global Varables, used to quickly fix some bugs
int FirstRun = 1;
int empty = 1;
int emptyLeave = 1;
static struct StudentQueue *Burnbox;
static struct StudentQueue *BurnboxLeave;
int boxflag = 0;
int boxflag2 = 100;

//Function Prototypes for Queues, stacks, and functions related to them
void HandoutLaptop(struct StudentQueue *LaptopLine, struct StudentQueue *TALine, struct LaptopStack *LaptopPile, int time, FILE *output); 
void TATakeStudent(struct StudentQueue *TALine, struct teachingAssistant *TA, int time, FILE *output);
void TAFinishStudent(struct StudentQueue *LaptopLine, struct StudentQueue *TALine, struct teachingAssistant *TA, int EndTime, int day, int time, FILE *output);
void StudentLeaving(struct StudentQueue *LaptopLine, struct LaptopStack *LaptopPile, int time, FILE *output);
void RunLoop();
void StepLaptopLine(struct StudentQueue *LaptopLine, struct StudentQueue *TALine, struct LaptopStack *LaptopPile, int time, FILE *output, int *HelpedKids);
void StepTALine(struct StudentQueue *LaptopLine, struct StudentQueue *TALine, struct LaptopStack *LaptopPile, struct teachingAssistant **TA, int TANum, int Time, int Day, int EndTime, FILE *output);
void burnBoxEnter(struct StudentQueue *TALine, int time, FILE *outputFile);

//Fuction Prototypes for printing to output files
void PrintDay(int day, FILE *output);
void PrintTime(int time, FILE *output);
void PrintStartTA(int Time, struct teachingAssistant *TA, FILE *output);
void PrintStudentAction(int Time, struct student *kid, FILE *output, int MessageType);
void PrintSummary(int day, int time, int visited, int helped, FILE *output);
void PrintTAWithStud(struct teachingAssistant *TA, int time, FILE *output);
void PrintEndTA(int Time, struct teachingAssistant *TA, FILE *output);
void PrintClose(int Time, FILE *output);
void PrintProgramNum(int x, FILE *output);

//Functions dealing with reading in the input file
struct LaptopStack *MakeStack(FILE *input);
struct LaptopStack *MakeLaptop(int x);
struct teachingAssistant *MakeTA(char * Name, int TimeStart[3], int TimeEnd[3]);
struct teachingAssistant **MakeAllTA(FILE *inputFile, int *TANum);
struct student *GetKid(FILE *inputFile);
int GetPorSNumber(FILE *inputFile); //PorS is "Program Number or Student Number", both functions used same code
int CalcEndTime(int day, int TAnum, struct teachingAssistant **TA);

//Functions to hold students, to try and make timing better
void StudentBox(int time, struct StudentQueue *LaptopLine, int TotalKids, FILE *inputFile, FILE *outputFile);
void burnBoxClear(int time, struct LaptopStack *LaptopPile, FILE *outputFile);
void burnBoxLeave(struct StudentQueue *LaptopLine, int time, FILE *outputFile);



//Pops a student off the Laptop line if they are just coming in, and put them into Incoming Burn Box
void HandoutLaptop(struct StudentQueue *LaptopLine, struct StudentQueue *TALine, struct LaptopStack *LaptopPile, int time, FILE *output)
{
		int debug; //Used to allow for breakpoints during Debug
		struct StudentQueue *NewNode; //Local StudentQueue objects
		struct StudentQueue *LocalTALine = TALine;

		if(TALine!=TALine->next) while (LocalTALine->next != NULL) LocalTALine = LocalTALine->next; //Makes local Temp pointer point to the last node in the TA line


		NewNode = (struct StudentQueue *)malloc(sizeof(struct StudentQueue)); //Creates the new node
		NewNode->kid = LaptopLine->kid;
		NewNode->kid.laptopSerialNum = LaptopPile->laptopID;

		NewNode->next = NULL;
		if (boxflag2 == -2) //Flag to fix timing, will only put dirrectly on TA Line if anther student has come in
		{
		PrintStudentAction(time, &(NewNode->kid), output, 2);	
		if(TALine != TALine->next)LocalTALine->next = NewNode;
		else *TALine = *NewNode;
		}
		else//Puts the new node into the burnbox to simulate 1 minute laptop handout
		{
		empty = 0;
		Burnbox = NewNode;
		}

		if(LaptopLine->next != NULL) *LaptopLine = *LaptopLine->next; //Set Line to next node if not empty
		else {*LaptopLine = *(struct StudentQueue *)malloc(sizeof(struct StudentQueue));LaptopLine->next = LaptopLine;} //If no one else is in line, make new node and set next to its self


		if(LaptopPile->laptopID != -1 && LaptopPile->next != NULL) //If Statement Stops program from crashing if laptops run out, handsout laptop -1 if there is no laptops left
		*LaptopPile = *LaptopPile->next;
		else //Should only get tripped if more students take laptop then there are laptops, or if there is a leak in the laptops
			debug = 1;
}

//Pops a student off the TA Line and gives it to the passed in TA
void TATakeStudent(struct StudentQueue *TALine, struct teachingAssistant *TA, int time, FILE *output)
{
	TA->studentWithTA = TALine->kid; //Takes student from TA Line
	TA->minute = 0; //Sets Minute to 0 (Never resets till TA takes a student)
	PrintTAWithStud(TA, time, output); //Prints notice that TA has taken studnet 
	if (TALine->next != NULL) *TALine = *TALine->next; //Increments line if not empty
	else TALine->next = TALine;//Sets line to empty
}

//Puts a TA ether back in the TA line, or in the Leaving Burn Box, which will go the Laptop Line, depending on the number of questions asked and the time
void TAFinishStudent(struct StudentQueue *LaptopLine, struct StudentQueue *TALine, struct teachingAssistant *TA, int EndTime, int day, int time, FILE *output)
{
	int MessageNum;
	struct StudentQueue *LocalLine;
	struct student *Kid; 
	TA->studentWithTA.numAnswered++; //Increments number of questions anwsered
	Kid = (struct student *)malloc(sizeof(struct student)); //Makes new student node
	*Kid = TA->studentWithTA;
	
	if (Kid->numQuestions - Kid->numAnswered == 0){ //Puts student into burn box 

		if(emptyLeave == 0 && boxflag == 0)
		{
			//Fixes error of two people finishing right after each other and someone entering at the same time as the first person leaves, causing laptops to go missing. Can cause timing problem though.
			//Emptys burnbox so next studnet can go in
			burnBoxLeave(LaptopLine,time,output); 
		}

		LocalLine = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));
		LocalLine->kid = TA->studentWithTA;
		LocalLine->next = NULL;
		BurnboxLeave = LocalLine;
		emptyLeave = 0; //Flag to set notice that burnbox is not empty
		PrintStudentAction(time,&(LocalLine->kid), output, 4); //Prints that they are done with TA and returing laptop
		return;
	}
	else
	{
		LocalLine = TALine;
		MessageNum = 3;
	}

	if (LocalLine != LocalLine->next) //TA line is not empty
	{
		while (LocalLine->next != NULL) LocalLine = LocalLine->next;
		LocalLine->next = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));
		LocalLine = LocalLine->next;
	}
	else *LocalLine = *(struct StudentQueue *)malloc(sizeof(struct StudentQueue)); //If TA Line is empty, make new line
	LocalLine->kid = *Kid;
	LocalLine->next = NULL;
	if(EndTime <= time && Kid->numAnswered != Kid->numQuestions) MessageNum = 7; //Changes message to one about having more questions, but lab is closed
	PrintStudentAction(time,Kid,output,MessageNum); //Prints applicable message message 

}
	
//Pops off a studnet from the laptop line and returns their laptop to the laptop stack
void StudentLeaving(struct StudentQueue *LaptopLine, struct LaptopStack *LaptopPile, int time, FILE *output)
{
	struct student *Kid;
	struct LaptopStack *Laptop;
	struct LaptopStack *LaptopTempPointer;

	boxflag2++; //Used for timing
	//Creates new nodes
	Kid = (struct student *)malloc(sizeof(struct student));
	Laptop = (struct LaptopStack *)malloc(sizeof(struct LaptopStack));
	LaptopTempPointer = (struct LaptopStack *)malloc(sizeof(struct LaptopStack));

	*Kid = LaptopLine->kid;
	if (Kid->laptopSerialNum == -1) {PrintStudentAction(time,Kid,output,6);} //SerialNum will be -1 if never got a laptop, prints messages about so, and doesn't put onto stack
	else{ //Puts laptop back on stack
	Laptop->laptopID = Kid->laptopSerialNum;
	Laptop->next = LaptopPile;
	*LaptopTempPointer = *Laptop->next;
	*LaptopPile = *Laptop;
	LaptopPile->next = LaptopTempPointer;
	PrintStudentAction(time,Kid,output,5);
	}
	if(LaptopLine->next != NULL) *LaptopLine = *LaptopLine->next;  //Increment Laptop Line
	else {*LaptopLine = *(struct StudentQueue *)malloc(sizeof(struct StudentQueue)); LaptopLine->next = LaptopLine;} //Set line to empty
}

//Makes a Laptop Stack node with the passed in ID number
struct LaptopStack *MakeLaptop(int x)
{
	struct LaptopStack *Laptop; 
	Laptop = (struct LaptopStack *)malloc(sizeof(struct LaptopStack)); //Makes laptop node
	Laptop->laptopID = x; //Sets ID
	Laptop->next = NULL; //Sets pointer to null
	return Laptop; //Returns the new Laptop 
}

//Takes the next student in from the Laptop Queue and ether gives them or takes a laptop from the stack
void StepLaptopLine(struct StudentQueue *LaptopLine, struct StudentQueue *TALine, struct LaptopStack *LaptopPile, int time, FILE *output, int *HelpedKids)
{
	if (LaptopLine->kid.numQuestions == LaptopLine->kid.numAnswered) //If Studnet is returning laptop
	{
		StudentLeaving(LaptopLine, LaptopPile, time, output);
		*HelpedKids+=1;
		boxflag2=-3;//For timing
		return;
	}
	else {HandoutLaptop(LaptopLine, TALine, LaptopPile, time, output);boxflag = 0;} //If Studnet is getting laptop
}

//Handles functions related to TA. Annouces when the come and go, or if the lab is closed. Takes new students in, a puts them back into the propper queue once finished with the TA
void StepTALine(struct StudentQueue *LaptopLine, struct StudentQueue *TALine, struct LaptopStack *LaptopPile, struct teachingAssistant **TA, int TANum, int Time, int Day, int EndTime, FILE *output)
{
	int i, j, k; //Counters
	int TALineAction = 0; //Flag to make sure a only one only takes student this minute
	int flag = 0, flag2 = 0; //Flags to insure Lab is closed message only prints once.
	for (i = 0; i < TANum; i++)//Go though all the TAs
	{
		if (TA[i]->minute == 5) //Puts Student back into propper line
		{TAFinishStudent(LaptopLine, TALine, TA[i], EndTime, Day ,Time,output);}
		//If the TA is on the clock, and they don't have a studnet (Minutes is set to 6 by defalut and not reset till they get a studnet), AND No other TA has taken a student, Take a Student from the TA Line
		if (TA[i]->startTimes[Day] <= Time && TA[i]->endTimes[Day] > Time) if (TA[i]->minute >= 5 && TALine != TALine->next  && TALineAction == 0){ TATakeStudent(TALine, TA[i], Time, output);TALineAction=1;}
		//If TA Has ended for the day, print message 
		if (TA[i]->endTimes[Day] == Time && TA[i]->endTimes[Day]!=TA[i]->startTimes[Day]) {PrintEndTA(Time, TA[i], output); flag2 = 1;}
		//if TA has started, print message
		if (TA[i]->startTimes[Day] == Time && TA[i]->endTimes[Day]!=TA[i]->startTimes[Day]) PrintStartTA(Time,TA[i],output);
		TA[i]->minute++; //Incremante the Minute a TA has been with a student
	}

	if (flag2 == 1) //If A TA Has finished this minute, check if any other TA is working
	{
		k = 0;
		for (j = 0; j < TANum; j++) 
		{
			if (TA[j]->endTimes[Day] <= Time) 
				k++;
			if (k == TANum && flag == 0) 
			{
				PrintClose(Time,output);
				flag = 1; //Makes sure message only prints once
			}
		}
	}
}

//Main Loop. Should likely be broken up into more functions
void RunLoop()
{
	FILE *outputFile = NULL;
	FILE *inputFile=NULL;
	//Makes the headers to the Queaes, stacks, TA Array
	struct LaptopStack *LaptopPile;
	struct StudentQueue *LaptopLine;
	struct StudentQueue *LocalLine;
	struct StudentQueue *TALine;
	struct teachingAssistant **TA = NULL;
	//For Counters
	int i;
	int k;
	int l;
	int j;
	//For Timing
	int EndTime;
	int OverTime = 0;
	int flag = 0;//Flag used to check if any TA has a student
	int TANum; //Number of TAs in the lab, used for index
	int totalKids = 0; 
	int helpedKids = 0;
	int ProgramRun; //Number of "programs" run
	
	//Used for debuging
	int debug; 
	int debugcount = 0;
	struct LaptopStack *LaptopTempPointer;
	
	LaptopTempPointer = (struct LaptopStack *)malloc(sizeof(struct LaptopStack));

	inputFile=fopen("input.txt", "r");//open file
	outputFile=fopen("out.txt", "w");//create/open file

	LaptopPile = MakeStack(inputFile); //Makes Laptop stack
	LaptopLine = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));//Makes empty Laptop line
	LaptopLine->next=LaptopLine;
	TALine = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));//Makes empty TA Line
	TALine->next = TALine;

	TA = MakeAllTA(inputFile, &TANum);//Makes TAs, and sets TANum
	
	
	ProgramRun = GetPorSNumber(inputFile); //Sets number of programs to run
	

	for (k = 0; k < ProgramRun; k++)
	{
		PrintProgramNum(k+1,outputFile);
		for (j = 0; j < 3; j++) //Loops though 3 days
		{
			totalKids = GetPorSNumber(inputFile); //Gets the total number of kids for day
			PrintDay(j,outputFile);
			EndTime = CalcEndTime(j,TANum,TA); //gets end time for day (Could of likely been calculated once and put into an array, but eh)
			for(l=0;l<TANum;l++)TA[l]->minute = 6;//Sets all TAs to 6 minutes, so they are all looking for students
			OverTime = 0; //Resets overtime
			for (i = 0; i <= EndTime; i++) //Loops though day
			{
				boxflag = 1; //For timing

				if (i == 275) //Debug code
				debug = 1;


				burnBoxEnter(TALine, i, outputFile);  //Pops person out of burnbox
				
				if (LaptopLine != LaptopLine->next) StepLaptopLine(LaptopLine, TALine, LaptopPile, i, outputFile, &helpedKids); //Takes person from laptop line
				if (boxflag == 1) burnBoxLeave(LaptopLine,i,outputFile); //Pops person out of exiting burnbox
				if (i==EndTime) //Has all the kids who never got laptops leave if closed
				{burnBoxClear(i,LaptopPile,outputFile);while (LaptopLine->kid.laptopSerialNum == -1 && LaptopLine != LaptopLine->next) StudentLeaving(LaptopLine, LaptopPile, i, outputFile);}
				StepTALine(LaptopLine, TALine, LaptopPile, TA, TANum, i, j, EndTime, outputFile); //Increment the TA line
				boxflag2+=2; //for timing
				StudentBox(i,LaptopLine,totalKids,inputFile,outputFile); //Checks if new person has arrived, puts them in line
				if (i==EndTime) 
					burnBoxLeave(LaptopLine,i,outputFile); //Insures person in exit burn box is put into laptop line
			}

			LocalLine = LaptopLine; //Used to allow putting people on back of Laptop line
			while (TALine != TALine->next || LaptopLine != LaptopLine->next || flag < TANum) //If TALine or LaptopLine are Not Emtpy or Every TA is not done, do loop to flush all students
			{
				//Debug code, used to check for leaking laptops
					if (k == 0 && j == 0)
				{
					LaptopTempPointer = LaptopPile;
					while (LaptopTempPointer->next != NULL)
					{LaptopTempPointer = LaptopTempPointer->next; debugcount++;}
					if (debugcount > 195)
					debug = 1;
					debugcount = 0;
				}

				LocalLine = LaptopLine;
				if(k == 1)
					debug = 1;

				OverTime++; //Increments overtime
				LocalLine = LaptopLine; 
				flag = 0; //Resets number of TA done
				while(TALine != TALine->next) //Clears TA Line
				{
					if (LocalLine != LocalLine->next) 
					{
						while (LocalLine->next != NULL) LocalLine = LocalLine->next;
						LocalLine->next = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));
						LocalLine = LocalLine->next;
					}
					else *LocalLine = *(struct StudentQueue *)malloc(sizeof(struct StudentQueue));
					LocalLine->kid = TALine->kid;
					LocalLine->next = NULL;
					if (TALine->next != NULL) *TALine = *TALine->next;
					else TALine->next = TALine;
				}

				if (LaptopLine != LaptopLine->next) // Pops student off Laptop Line if not empty
				{
					if((double)LaptopLine->kid.numAnswered / (double)LaptopLine->kid.numQuestions>= .75) helpedKids++;
					StudentLeaving(LaptopLine, LaptopPile, EndTime+OverTime, outputFile);
				}
				for (i = 0; i < TANum; i++)
				{
					if (TA[i]->minute+OverTime-1 == 5) //Checks for TAs and pops student off if being helped
					{
						TAFinishStudent(LaptopLine, TALine, TA[i],EndTime,j,EndTime+OverTime,outputFile);
						if (boxflag == 1) burnBoxLeave(LaptopLine,i,outputFile);
					}
					if (TA[i]->minute+OverTime-1 > 5) flag++;

				}
			}
			PrintSummary(j, EndTime+OverTime, totalKids, helpedKids, outputFile); 
			totalKids = 0;
			helpedKids = 0;
		}
	}
	//closes flies
	fclose(inputFile);
	fclose(outputFile);
}

//Takes in the Name, Start Time and End Time of a TA, and Creates a TA Object, and returns it
struct teachingAssistant *MakeTA(char * Name, int TimeStart[3], int TimeEnd[3])
{
	int i; //For counter
	struct teachingAssistant *TA;
	TA = (struct teachingAssistant *)malloc(sizeof(struct teachingAssistant));
	strcpy(TA->name, Name); //Sets local name to passed in name
	for ( i = 0; i < 3; i++) //Sets start and end times
	{
		TA->startTimes[i] = TimeStart[i]; 
		TA->endTimes[i] = TimeEnd[i];
	}
	TA->minute = 6;	//Initlizes time
	return TA;
}

//Takes in the array of TAs, and calculates the time the Lab closes
int CalcEndTime(int day, int TAnum, struct teachingAssistant **TA)
{
	int i; 
	int temp = 0; //Holdes highest endtime
	for (i = 0; i < TAnum; i++)	if(TA[i]->endTimes[day] > temp) temp = TA[i]->endTimes[day]; //If TA Endtime is greater then temp, set temp to it
	return temp; 
}

//Prints what day it is
void PrintDay(int day, FILE *output)
{
	if (day == 0) fprintf(output,"Monday:\n\n");
	if (day == 1) fprintf(output,"Tuesday:\n\n");
	if (day == 2) fprintf(output,"Wednesday:\n\n");
}

//Prints what time it is via passed in minute. Goes from Noon till 11:59PM
void PrintTime(int time, FILE *output)
{
	int hour;
	int minute;
	hour = time / 60;
	minute = time % 60;
	if (hour == 0) hour = 12;
	fprintf(output,"%d:%02d PM:  ",hour,minute);
}

//Prints that a TA Starts lab hours
void PrintStartTA(int Time, struct teachingAssistant *TA, FILE *output)
{
	PrintTime(Time, output);
	fprintf(output,"%s has begun lab hours.\n",TA->name);
}

//Prints the varrius actions that a student could do, depending on the passed in message type
void PrintStudentAction(int Time, struct student *kid, FILE *output, int MessageType)
{
	double percent;
	PrintTime(Time, output);
	if (MessageType == 1) fprintf(output,"%s %s has arrived in the Cave.\n",kid->firstName, kid->lastName);
	if (MessageType == 2) fprintf(output,"%s %s has borrowed laptop %d and moved to the TA line.\n",kid->firstName, kid->lastName, kid->laptopSerialNum);
	if (MessageType == 3) fprintf(output,"%s %s has had one question answered and gotten back in line.\n",kid->firstName, kid->lastName);
	if (MessageType == 4) fprintf(output,"%s %s has no more questions and will now return the laptop.\n",kid->firstName, kid->lastName);
	if (MessageType == 5) 
	{
		percent = (double)kid->numAnswered/(double)kid->numQuestions;
		fprintf(output,"%s %s has returned laptop %d and went home",kid->firstName, kid->lastName, kid->laptopSerialNum);
		if (percent >= .75) fprintf(output," HAPPY.\n");
		else fprintf(output," FRUSTRATED.\n");
	}
	if (MessageType == 6) fprintf(output,"%s %s never even got a laptop and went home FRUSTRATED.\n",kid->firstName, kid->lastName);
	if (MessageType == 7) fprintf(output,"%s %s has had one question answered, but must now return the laptop and exit the lab.\n",kid->firstName, kid->lastName);
}

//Prints end of Day Summery
void PrintSummary(int day, int time, int visited, int helped, FILE *output)
{
	if (day == 0) fprintf(output,"\nMonday");
	if (day == 1) fprintf(output,"\nTuesday");
	if (day == 2) fprintf(output,"\nWednesday");
	fprintf(output,"\'s Lab Summary:\n");
	fprintf(output,"The TA Lab was open for %d hours and %d minutes.\n",time/60,time%60);
	fprintf(output,"%d students visited the lab.  Out of those students, only %d left happy.\n", visited, helped);
	fprintf(output,"The remaining left frustrated.\n\n");
	fprintf(output,"Lesson Learned:  Do not procrastinate!  Start programs early!\n\n\n");
	FirstRun = 1;
}

//Prints when a TA takes a Student
void PrintTAWithStud(struct teachingAssistant *TA, int time, FILE *output)
{
	PrintTime(time, output);
	fprintf(output,"%s %s is getting help from %s.\n",TA->studentWithTA.firstName, TA->studentWithTA.lastName, TA->name);
}

//Prints that a TA has ended lab hours
void PrintEndTA(int Time, struct teachingAssistant *TA, FILE *output)
{
	PrintTime(Time, output);
	fprintf(output,"%s has finished lab hours.\n",TA->name);
}

//Prints that the lab has closed
void PrintClose(int Time, FILE *output)
{
	PrintTime(Time, output);
	fprintf(output,"There are no TAs on duty.  The Cave is now closed.\n");
}

//Prints the itteration of the program
void PrintProgramNum(int x, FILE *output)
{
	fprintf(output,"**********\n");
	fprintf(output,"Program %d:\n",x);
	fprintf(output,"**********\n\n");
}

//Reads in the Laptop IDs and makes the stack
struct LaptopStack *MakeStack(FILE *inputFile)
{
	int i;
	int LaptopNum;
	int LaptopID;
	char tempString[1024];
	struct LaptopStack *Top;
	struct LaptopStack *Laptop;
	struct LaptopStack *Laptoplast;


	Laptop = (struct LaptopStack *)malloc(sizeof(struct LaptopStack));
	Top = (struct LaptopStack *)malloc(sizeof(struct LaptopStack));
	Laptoplast = (struct LaptopStack *)malloc(sizeof(struct LaptopStack));
	Top = Laptop;
	Laptoplast->next=NULL;
	Laptoplast->laptopID = -1;

	fgets(tempString, 1024, inputFile);//Gets first line of text, which has the total number of laptops
	LaptopNum = atoi(tempString);

	//Puts new laptop on top of last
	for(i = 0; i < LaptopNum; i++)
	{
		fgets(tempString, 1024, inputFile);//Gets first line of text, which has the total number of laptops
		LaptopID = atoi(tempString);
		Laptop = MakeLaptop(LaptopID);
		Laptop->next = Laptoplast;
		Laptoplast = Laptop;
	}
	Top = Top->next;
	return Laptop;
}

//Makes the TA Array from the file
struct teachingAssistant **MakeAllTA(FILE *inputFile, int *TANum)
{
	int i;
	int j;
	int Start[3];
	int End[3];
	char tempString[1024];
	char *name;
	char *number;
	struct teachingAssistant **TA;

	fgets(tempString, 1024, inputFile);//Gets line with number of TAs
	*TANum = atoi(tempString);
	TA = (struct teachingAssistant **)malloc(sizeof(struct teachingAssistant*)*(*TANum));
	for (i = 0; i < *TANum; i++)
	{
		fgets(tempString, 1024, inputFile);//Gets line with number of TAs
		for (j = 0; j < 7; j++)//Tokenizes Line, puts token into right spots
			{
				if (j == 0) name = strtok(tempString, " \n"); 
				else 
				{
					number = strtok(NULL, " \n");
					if (j%2 == 1) Start[j/2] = atoi(number);
					else End[j/2-1] = atoi(number);
				}
			}
		 TA[i] = MakeTA(name, Start , End);
	}
	return TA;
}

//Gets the number of Programs or number of students, uses same code for both so combined
int GetPorSNumber(FILE *inputFile) 
{
	char tempString[1024];
	fgets(tempString, 1024, inputFile);//Gets line with number of programs run
	return atoi(tempString);
}

//Read in the next student from the file
struct student *GetKid(FILE *inputFile)
{
	struct student *Kid;
	char tempString[1024];
	char *number;

	Kid = (struct student *)malloc(sizeof(struct student));
	fgets(tempString, 1024, inputFile);//Gets line with kid

	//Copies the strings to the tokens or uses atoi to get number
	number = strtok(tempString, " \n");
	Kid->enterTime = atoi(number);
	strcpy(Kid->firstName, strtok(NULL, " \n"));
	strcpy(Kid->lastName, strtok(NULL, " \n"));
	number = strtok(NULL, " \n");
	Kid->numQuestions = atoi(number);
	Kid->numAnswered = 0;
	Kid->laptopSerialNum = -1;

	return Kid;
}

//Holds a student until it is their propper start time. Recusivly calls its self if more then one student enters at the same time
void StudentBox(int time, struct StudentQueue *LaptopLine, int TotalKids, FILE *inputFile, FILE *outputFile)
{
	static struct student *Kid;
	static int Counter = 0;
	struct StudentQueue *LocalLine;
	boxflag2--;
	LocalLine = LaptopLine;
	if (FirstRun == 1) {
		Kid = (struct student *)malloc(sizeof(struct student));
		Kid = GetKid(inputFile);
		FirstRun=0;
		Counter = 1;
	}
	if (time == Kid->enterTime)
	{
		PrintStudentAction(time,Kid,outputFile,1);
		boxflag2 = 1;
		//if (emptyLeave == 0 && boxflag == 1)
		//{
		//	burnBoxLeave(LaptopLine,time,outputFile);
		//}
		if (LaptopLine==LaptopLine->next)
		{
			*LaptopLine=*(struct StudentQueue *)malloc(sizeof(struct StudentQueue));
			LaptopLine->kid=*Kid;
			LaptopLine->next=NULL;
		}
		else
		{
			while(LocalLine->next != NULL) LocalLine = LocalLine->next;
			LocalLine->next = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));
			LocalLine = LocalLine->next;
			LocalLine->kid=*Kid;
			LocalLine->next=NULL;
		}
		if (Counter < TotalKids){
			Kid = GetKid(inputFile);
			Counter++;
			if (Kid->enterTime == time && Counter == TotalKids) 
				StudentBox(time, LaptopLine, TotalKids, inputFile, outputFile);
		}
	}
	if (Kid->enterTime == time && Counter < TotalKids) 
		StudentBox(time, LaptopLine, TotalKids, inputFile, outputFile);
}

//Holds a student between start of laptop handing out and finishing it
 void burnBoxEnter(struct StudentQueue *TALine, int time, FILE *outputFile)
 {
	 struct StudentQueue *Kid;
	 struct StudentQueue *LocalTALine = TALine;
	 if (empty==0)
	 {
		if(TALine!=TALine->next) while (LocalTALine->next != NULL) LocalTALine = LocalTALine->next;
		Kid = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));
		Kid = Burnbox;
		if(TALine != TALine->next)LocalTALine->next = Kid;
		else *TALine = *Kid;
		PrintStudentAction(time, &(Kid->kid), outputFile, 2);
		empty = 1;
	 }
 }

//Holds a student between transition between TA Line and Laptop Line
 void burnBoxLeave(struct StudentQueue *LaptopLine, int time, FILE *outputFile)
 {
	 struct StudentQueue *Kid;
	 struct StudentQueue *LocalTALine = LaptopLine;
	 if (emptyLeave==0)
	 {
		if(LaptopLine!=LaptopLine->next) while (LocalTALine->next != NULL) LocalTALine = LocalTALine->next;
		Kid = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));
		Kid = BurnboxLeave;
		if(LaptopLine != LaptopLine->next)LocalTALine->next = Kid;
		else *LaptopLine = *Kid;
		emptyLeave = 1;
	 }
 }

//Handles the sitation where a Student has started getting a Laptop but not reaceaved one yet. Puts Laptop back on stack, and prints message about not receaving one
void burnBoxClear(int time, struct LaptopStack *LaptopPile, FILE *outputFile)
{
	struct student *Kid;
	struct LaptopStack *Laptop;
	struct LaptopStack *Laptoplast;
	struct LaptopStack *LaptopTempPointer;
	if (empty == 0)
	{
		Kid = (struct student *)malloc(sizeof(struct student));
		Laptop = (struct LaptopStack *)malloc(sizeof(struct LaptopStack));
		Laptoplast = (struct LaptopStack *)malloc(sizeof(struct LaptopStack));
		LaptopTempPointer = (struct LaptopStack *)malloc(sizeof(struct LaptopStack));

		//Laptop->next = LaptopPile;
		//Laptop->laptopID = .laptopSerialNum;
		//*LaptopPile = *Laptop;
		

		*Kid = Burnbox->kid;
		Laptop->laptopID = Kid->laptopSerialNum;
		Laptop->next = LaptopPile;
		*LaptopTempPointer = *Laptop->next;
		*LaptopPile = *Laptop;
		LaptopPile->next = LaptopTempPointer;
		PrintStudentAction(time, &(Burnbox->kid), outputFile, 6);
		empty = 1;
	}
}


int main()
{
	RunLoop();
}