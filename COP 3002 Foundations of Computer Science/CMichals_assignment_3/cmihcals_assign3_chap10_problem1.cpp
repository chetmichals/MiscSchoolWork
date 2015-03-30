/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 3, Program 1
Due Time and Date: October 6, 2010 at 11:00 PM 
Last Changed: October 6, 2010 at 3:54 AM
Instructor: Ingrid Buckley
Objective: 
Total Points: 100 For Entire Assignment, 25 for this program
*/

#include <iostream>
#include <fstream>

using namespace std;

struct StudentRecord {
  int number;
  double quizOne;
  double quizTwo;
  double midterm;
  double finalTest;
  double finalGrade;
  char letterGrade;
};

void finalGrade(struct StudentRecord &record);
void letterGrade(struct StudentRecord &record);
void processFile(ifstream &input);
void makeOutput(ofstream &output, struct StudentRecord record);

int main()
{
	StudentRecord record;
	record.quizOne=0;record.quizTwo=0;record.midterm=100;record.finalTest=1;
	ifstream input ("chap10-Q1-input.txt");
	processFile(input);
	input.close();
	return 0;
}
void finalGrade(struct StudentRecord &record)
{
	double tempNumberQuiz=0;
	tempNumberQuiz=((record.quizOne+record.quizTwo)/20);
	record.finalGrade=((.5*record.finalTest)+(.25*record.midterm)+(25*tempNumberQuiz));
	letterGrade(record);
}

void letterGrade(struct StudentRecord &record)
{
	if (record.finalGrade>=90) 
		record.letterGrade='A';
	else if (record.finalGrade>=80) 
		record.letterGrade='B';
	else if (record.finalGrade>=70) 
		record.letterGrade='C';
	else if (record.finalGrade>=60) 
		record.letterGrade='D';
	else
		record.letterGrade='F';
}

void processFile(ifstream &input)
{
	int i = 0;
	char tempValue[6];
	StudentRecord record[100];
	ofstream output("outputGrades.txt");
	input.seekg(0, ios::beg);
	while (!input.eof())
	{
		input.getline(tempValue, 4);	
		record[i].number=atoi(tempValue);
		input.clear();

		input.getline(tempValue, 4);	
		record[i].quizOne=atof(tempValue);
		input.clear();

		input.getline(tempValue, 5);	
		record[i].quizTwo=atof(tempValue);
		input.clear();

		input.getline(tempValue, 4);	
		record[i].midterm=atof(tempValue);
		input.clear();

		input.getline(tempValue, 4, '\n');	
		record[i].finalTest=atof(tempValue);
		
		 
		finalGrade(record[i]);
		makeOutput(output,record[i]);

		i++;
//		input.getline(tempValue, 100, '\n');
	}

}



void makeOutput(ofstream &output, struct StudentRecord record)
{
	output << record.number << " " << record.quizOne << " " << record.quizTwo << " " 
		<< record.midterm << " " << record.finalTest << " " << record.finalGrade << " " << record.letterGrade << endl;
}