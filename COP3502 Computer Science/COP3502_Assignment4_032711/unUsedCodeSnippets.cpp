//int main(){	
////struct LaptopStack *LaptopPile;
//	//struct StudentQueue *LaptopLine;
//	//struct StudentQueue *TALine;
//	//struct teachingAssistant *TA;
//
//	//LaptopPile = MakeStack(100);
//	//LaptopLine = TestStudents();
//	//TALine = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));
//	//TA = (struct teachingAssistant *)malloc(sizeof(struct teachingAssistant));
//
//	//TALine->next = TALine;
//
//	//HandoutLaptop(LaptopLine, TALine, LaptopPile);
//	//HandoutLaptop(LaptopLine, TALine, LaptopPile);
//	//HandoutLaptop(LaptopLine, TALine, LaptopPile);
//
//	//TATakeStudent(TALine, TA);
//	//TAFinishStuden(LaptopLine, TALine, TA);
//	//StudentLeaving(LaptopLine, LaptopPile);
//
//	//return 0;
//}

//struct LaptopStack *MakeStack(int x)
//{
//
//	int i;
//	struct LaptopStack *Top;
//	struct LaptopStack *Laptop;
//	Laptop = (struct LaptopStack *)malloc(sizeof(struct LaptopStack));
//	Top = (struct LaptopStack *)malloc(sizeof(struct LaptopStack));
//	Top = Laptop;
//	for(i = 1; i <= x; i++)
//	{
//		Laptop->next = MakeLaptop(i);
//		Laptop = Laptop->next;
//	}
//	Top = Top->next;
//	return Top;
//}

//(struct teachingAssistant **)malloc(sizeof(struct teachingAssistant*)*TANum);
//	for (i = 0; i < TANum; i++) {TA[i] = MakeTA("Name", Start , End );}

//struct StudentQueue *TestStudents()
//{
//	struct student *k1;
//	struct student *k2;
//	struct student *k3;
//	struct StudentQueue *Linetop;
//	struct StudentQueue *two;
//	struct StudentQueue *three;
//	k1 = (struct student *)malloc(sizeof(struct student));
//	k2 = (struct student *)malloc(sizeof(struct student));
//	k3 = (struct student *)malloc(sizeof(struct student));
//	Linetop = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));
//	two = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));
//	three = (struct StudentQueue *)malloc(sizeof(struct StudentQueue));
//
//	k1->enterTime = 0;
//	strcpy(k1->firstName,"TestFirstOne");
//	strcpy(k1->lastName,"TestLastOne");
//	k1->numQuestions = 100;
//	k1->numAnswered = 0;
//
//	k2->enterTime = 15;
//	strcpy(k2->firstName,"TestFirstTwo");
//	strcpy(k2->lastName,"TestLastTwo");
//	k2->numQuestions = 3;
//	k2->numAnswered = 0;
//	
//
//	k3->enterTime = 16;
//	strcpy(k3->firstName,"TestFirstThree");
//	strcpy(k3->lastName,"TestLastThree");
//	k3->numQuestions = 2;
//	k3->numAnswered = 0;
//
//	Linetop->kid = *k1;
//	two->kid = *k2;
//	three->kid = *k3;
//
//	Linetop->next = two;
//	two->next = three;
//	three ->next = NULL;
//	return Linetop;
//}