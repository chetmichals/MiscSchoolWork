#include <iostream>
using namespace std;

struct Object
  {  
     int age;          // D.O.B. would be better
     Object *next;        // Pointer to next node
  };




int main()
{
  cout << "Hello World!" << endl;   cout << "Welcome to C++ Programming" << endl;
  Object *Start = NULL, *Next = NULL, *Current = NULL;
  Start = new Object;
  Next = new Object;
  Current = new Object;
  Start->age=1 ;
  Start->next=Current;
  int i=2;
  while (i<10)
  {
         Next = new Object;
         Current->age=i ;
         Current->next=Next;
         Current=Next;
         i++;
  }
Next->next=NULL;
cout << Start->age;
Current=Start->next;
while (Current->next!=NULL)
{
cout << Current->age;
Current=Current->next;
}
          
  
  cin.get();
  
  return 0;
}
