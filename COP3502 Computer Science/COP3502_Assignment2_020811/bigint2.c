/*
Name: Chet Michals
Date: Febuary 8th, 2011
Class: Computer Science I, COP3502
Purpose: To read in large inteigers from a text file, and ether add or subtract them, then output them to anther text file
*/

#include <stdio.h>
#include <string.h>

struct integer{
int digit;
struct integer *next;
};

//Preconditions: the first parameter is string that stores
//               only contains digits, doesn't start with
//               0, and is 200 or fewer characters long.
//Postconditions: The function will read the digits of the
// large integer character by character, 
// convert them into integers and place them in 
// nodes of a linked list. The pointer to the 
// head of the list is returned.
struct integer* read_integer(char* stringInt);


//Preconditions: p is a pointer to a big integer, stored in
//               order, most to least significant 
//               digit, with no leading zeros.
//Postconditions: The big integer pointed to by p is 
//                printed out.
void print(struct integer *p);


//Preconditions: p and q are pointers to big integers, 
//               stored in reverse order, least to most 
//               significant digit, with no leading zeros.
//Postconditions: A new big integer is created that stores
//                the sum of the integers pointed to by p
//                and q and a pointer to it is returned.
struct integer* add(struct integer *p, struct integer *q);


//Preconditions: p and q are pointers to big integers, 
//               stored in reverse order, least to most 
//               significant digit, with no leading zeros.
//Postconditions: A new big integer is created that stores
//                the absolute value of the difference 
//                between the two and a pointer to this is
//                returned.
struct integer* subtract(struct integer *p, struct integer *q);



//Preconditions: Both parameters of the function are 
// pointers to struct integer. 
//Postconditions: The function compares the digits of two 
// numbers recursively and returns: 
//    -1 if the first number is smaller than the second, 
//     0 if the first number is equal to the second number,
//   1 if the first number is greater than the second.  
int compare(struct integer *p, struct integer *q);

//Preconditions: The parameter is a pointer to the input File
//Postconditions: The function will read the first line 
//                of the input file and return the number
//                as an intiger
int OppNumber(FILE *inputFile);

//Preconditions: The first two paramaters are character arrays containing 
//               the large intigers, the third contains the opperation number
//               and the forth a pointer to the output file
//Postconditions: A file is made containing the results               
void ProcessInts(char* longIntA, char* longIntB, int oppType, FILE *outputFile);

//Preconditions: None
//Postconditions: A pointer to a linked list contaning a single node 
//                with zero as the digit and NULL for next will be 
//                returned.
struct integer* BlankInt();

//Preconditions: The first two paramaters are character arrays containing 
//               the large intigers, the third contains the linked list 
//               with the result of the opperation between the two
//               intigers, the fourth a character for the opperation
//               carrayed out, and the final being a pointer to the output file
//Postconditions: A file is made containing the results   
void printAll(char* longIntA, char* longIntB, struct integer *final, char tempchar, FILE *outputFile);

int main()
{
    int oppNum=0,i=0,oppType=0;
    char tempString[1024], *longIntA, *longIntB, *c_oppType;
    FILE *inputFile=NULL;//make file pointer for reading in
    FILE *outputFile = NULL;//makes file pointer for output
    inputFile=fopen("input.txt", "r");//open file
    outputFile=fopen("out.txt", "w");//create/open file
    oppNum=OppNumber(inputFile);//Get number of opperations
    
    for(i=0;i<oppNum;i++)
    {
           fgets(tempString, 1024, inputFile);//Gets the string to be tokenized
           c_oppType = strtok(tempString, " ");//Grabs the first token and assigns it to c_oppType
           longIntA = strtok(NULL, " ");//Grabs the second token and puts it on longIntA
           longIntB = strtok(NULL, " \n");//Grabs the last token and puts it on longIntB
           oppType = atoi(c_oppType);//Changes c_oppType to a intiger
           ProcessInts(longIntA,longIntB,oppType,outputFile);//Sends it to the function to process the numbers
    }
    //Closes the files
    fclose(inputFile);
    fclose(outputFile);
    return 0;

}


int OppNumber(FILE *inputFile)
{
   char cOppNum[5];//makes a 5 character array to hold the number of opperations
   fgets(cOppNum, 5, inputFile);//Grabs upto 5 characters for then number of opperations
   int oppnum = atoi(cOppNum); //Changes the char array to an intiger
   if (oppnum==0)//Text files sometimes start with a hidden new line character, a quick fix for such a thing
   {
         fgets(cOppNum, 5, inputFile);
         oppnum =atoi(cOppNum);
   }
   return (oppnum);
}


struct integer* read_integer(char* stringInt)
{
       struct integer *first;
       struct integer *tempStruct;
       int length = 0;
       int i = 0;
       char tempChar[1];//atoi only works with arrays
       length = strlen(stringInt); //Get and store the number of character in the string
       first=NULL;
       for (i=0; i<length; i++) 
       {
           tempStruct = (struct integer *)malloc(sizeof(struct integer));//makes a new integer structer
           tempChar[0]=stringInt[i]; //Grabs character at i
           tempStruct->digit = atoi(tempChar);//Chagnes char to int
           if (tempStruct->digit > 9)
           {
                 tempStruct->digit = (tempStruct->digit/10); //Fixes strange glitch where atoi(tempChar) somehow returns a value higher then 9
           }
           tempStruct->next = first;
           first = tempStruct;
           tempChar[0] = ' ';
       }
       return first;
}
           
           
           
void ProcessInts(char* longIntA, char* longIntB, int oppType, FILE *outputFile)
{
     struct integer *s_longIntA, *s_longIntB, *final;
     int compResult = 0;
     char tempchar = ' ', *printSwap;
     s_longIntA = read_integer(longIntA); //Process the string and puts in a linked list
     s_longIntB = read_integer(longIntB);
     
     
     if (oppType == 1) //add
     {
          final = add(s_longIntA, s_longIntB); 
          tempchar = '+';
          //print(final);
          printAll(longIntA, longIntB, final, tempchar, outputFile);
     }
            
     else if (oppType == 2) //subtract
     {
          compResult = compare(s_longIntA, s_longIntB);
          if (compResult == 1) final = subtract(s_longIntA, s_longIntB);
          if (compResult == 0) final = BlankInt();
          if (compResult == -1)//Swaps the values of longIntA and lonIntB to print out correctly
          {
               final = subtract(s_longIntB, s_longIntA);
               printSwap = longIntA;
               longIntA = longIntB;
               longIntB=printSwap;
          }
          tempchar = '-';
          //print(final);
          printAll(longIntA, longIntB, final, tempchar, outputFile);
     }
     else
     {
         printf("Error, invalid opperation");
     }
}




struct integer* add(struct integer *p, struct integer *q)
{      
       int tempNum = 0;
       int overflow = 0;//Holds digit if A and B add up to more then 9
       struct integer *tempStruct, *final;
       final = NULL;
       while (p != NULL || q != NULL || overflow != 0)
       {
           tempStruct = (struct integer *)malloc(sizeof(struct integer));//makes a new integer structer
           
           if (p != NULL && q != NULL)
           {
               tempNum = p->digit + q ->digit + overflow; 
               p = p->next;
               q = q->next;

           }
           else if (p != NULL && q == NULL)
           {
               
               tempNum = p->digit + overflow;
               p = p->next;
           }
           else if (p == NULL && q != NULL)
           {
               
               tempNum = q->digit + overflow;
               q = q->next;
           }
           else //In event overflow is 1 while both p and q are null, adds the 1 onto the list
           {
               tempNum = overflow;
           }
           
               tempStruct->digit = (tempNum%10); 
               overflow = tempNum/10; //Makes uses of intiger division properties
               tempStruct->next = final;
               final = tempStruct;
       }
}     
     
     
     
struct integer* subtract(struct integer *p, struct integer *q)
{
       int tempNum = 0;
       int overflow = 0;//Holds digit if B is bigger then A
       struct integer *tempStruct, *final;
       final = NULL;
       while (p != NULL || q != NULL || overflow != 0)
       {
           tempStruct = (struct integer *)malloc(sizeof(struct integer));//makes a new integer structer
           
           if (p != NULL && q != NULL)
           {
               tempNum = p->digit - q ->digit - overflow;
               overflow = 0;
               if (tempNum<0){
                              tempNum+=10;overflow=1;}
               p = p->next;
               q = q->next;

           }
           else if (p != NULL && q == NULL)
           {
               
               tempNum = p->digit - overflow;
               if (tempNum<0){tempNum+=10;overflow=1;}
               p = p->next;
           }
           else if (p == NULL && q != NULL)
           {
               
               tempNum = q->digit - overflow;
               if (tempNum<0){tempNum+=10;overflow=1;}
               q = q->next;
           }
           else
           {
               overflow = 0;
           }        
               tempStruct->digit = (tempNum%10); 
               tempStruct->next = final;
               final = tempStruct;
       }
       while (final->digit == 0 && final != NULL) //Removes any zeroes at the start
       {
             final = final->next;
       }
       if (final == NULL){return BlankInt();}
       return final;
}     


int compare(struct integer *p, struct integer *q)
{
    int temp[500];//Hold upto 500 comparsons between 2 numbers
    int i = 0;
    while (p != NULL && q != NULL) //Keeps advanceing lists till one or both reach last entry
    {
          temp[i] = p->digit - q->digit; //Stores the diffrence between each number in temp[i]
          p = p->next;
          q = q->next;
          i++;
    }
    if (p == NULL && q == NULL) //If both have equal number of entires
    {
          for (i--; i >= 0; i--)//Goes though all values of i
          {
                    if (temp[i] > 0) return 1;
                    if (temp[i] < 0) return -1;
          }
          return 0;//if all entires of temp[i]=0, will get called
                    
    }
    else if (p == NULL) return -1;
    else return 1;
}     

void print(struct integer *p)
{
     while (p != NULL){printf("%d",p->digit);p=p->next;}
     printf("\n");
}

struct integer* BlankInt()
{
       //Creates and returns an entry with a digit of 0 and a null pointer
       struct integer* tempStruct;
       tempStruct = (struct integer *)malloc(sizeof(struct integer));//makes a new integer structer
       tempStruct->digit = 0;
       tempStruct->next = NULL;
       return tempStruct;
}

void printAll(char* longIntA, char* longIntB, struct integer *final, char tempchar, FILE *outputFile)
{
       int length = 0;
       int i = 0;
       
       length = strlen(longIntA); //Get and store the number of character in the string
       for (i=0; i<length; i++)fprintf(outputFile, "%c", longIntA[i]);
       
       fprintf(outputFile, " %c ", tempchar);
       
       length = strlen(longIntB); //Get and store the number of character in the string
       for (i=0; i<length; i++)fprintf(outputFile, "%c",  longIntB[i]);
       
       fprintf(outputFile, " = ", tempchar);
       
       while (final != NULL){fprintf(outputFile,"%d",final->digit);final=final->next;}
       fprintf(outputFile, "\n");
}
