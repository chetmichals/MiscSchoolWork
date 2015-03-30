/*
Name: Chet Michals
User ID: CMichals
Email Adreess: cmichals@fau.edu
Assignment Number: 4, Program 3
Due Time and Date: Novermber 18th, 2010 at 11 PM EST
Last Changed: Novermber 18th, 2010 at 12:20 PM EST
Instructor: Ingrid Buckley
Objective: To work with classes in expermenting with Over Riding Opperators
Total Points: 100 For Entire Assignment, 25 for this program
*/

#include <iostream>
#include "cmichals_assign4_chap11_prob5_Rational.h"
using namespace std;

int gcd(int m, int n);


Rational::Rational(int numer, int denom)
{ 
  normalize(numer, denom);
  n = numer;
  d = denom;
}

Rational::Rational(int numer)
{ 
  n = numer;
  d = 1;
}

Rational::Rational()
{ 
  n = 0;
  d = 1;
}

void normalize(int& n, int& d)
{
  // remove common factors:
  int g = gcd(n, d);
  n = n/g; 
  d = d/g;

  //fix things so that if the fraction is 'negative'
  //it is n that carries the sign. If both n and d are 
  //negative, each is made positive.
  if(n > 0 && d < 0 || n < 0 && d < 0)
  {
    n = -n;
    d = -d;
  }
  // assert:  d > 0
}


int gcd(int m, int n)
{
  int t; 
  m = abs (m); // don't care about signs.
  n = abs (n);
  if(n < m)    // make m >= n so algorithm will work!
  {
    t = m;
    m = n;
    n = t;
  }
  int r;
  r = m % n;
  while(r != 0)
  {
    r = m%n;
    m = n;
    n = r;
  }
  return m;
}

Rational operator +(const Rational& left, const Rational& right)
{
  int numer = left.n * right.d + left.d * right.n;
  int denom = left.d * right.d;
  normalize(numer, denom);
  Rational local(numer, denom);
  return local;
}

Rational operator -(const Rational& left, const Rational& right)
{
  int numer = left.n * right.d - left.d * right.n;
  int denom = left.d * right.d;
  normalize(numer, denom);
  Rational local(numer, denom);
  return local;
}

Rational operator *(const Rational& left, const Rational& right)
{
  int numer = left.n * right.n;
  int denom = left.d * right.d;
  normalize(numer, denom);
  Rational local(numer, denom);
  return local;
}

Rational operator /(const Rational& left, const Rational& right)
{
  int numer = left.n * right.d;
  int denom = left.d * right.n;
  normalize(numer, denom);
  Rational local(numer, denom);
  return local;
}



//precondition: all relational operators require  d > 0
bool operator <(const Rational& left, const Rational& right)
{
  return left.n * right.d < right.n * left.d;
}


bool operator >(const Rational& left, const Rational& right)
{
  return left.n * right.d > right.n * left.d;
}

ostream& operator <<(ostream& stream, const Rational& number)
{
	stream << number.n <<"/" << number.d;
	return stream;
}

istream& operator >>(istream& stream, Rational& number)
{
	stream >> number.n;
	cout << "/";
	stream >> number.d;
	return stream;
}
bool operator <=(const Rational& left, 
                 const Rational& right)
{
  return left.n * right.d <= right.n * left.d;
}

bool operator >=(const Rational& left, 
                 const Rational& right)
{
  return left.n * right.d >= right.n * left.d;
}


int main()
{
  cout << "Testing declarations" << endl;
  cout << "Rational x, y(2), z(-5,-6), w(1,-3);" << endl;
  Rational x, y(2), z(-5,-6), w(1,-3);
  cout << "z = " << z << ", y = " << y << ",  z = " << z
       << ", w = " << w << endl;

  cout << "Testing >> overloading: \nEnter "
       << "a fraction in the format "
       << "integer_numerator/integer_denominator" 
       << endl;
  cin >> x;
  cout << "You entered the equivalent of: " << x << endl;
  cout << z << " -  (" << w << ") = " << z - w << endl;

  cout << "Testing the constructor and normalization routines: " << endl;
  y =Rational(-128, -48);
  cout << "y =Rational(-128, -48) outputs as " << y << endl;
  y =Rational(-128, 48);
  cout << "y =Rational(-128, 48)outputs as " << y << endl;
  y = Rational(128,-48);
  cout << "y = Rational(128, -48) outputs as " << y << endl;
  Rational a(1,1);
  cout << "Rational a(1,1); a outputs as: " << a << endl;
  Rational ww = y*a;
  cout <<  y << " * " << a << " = " << ww << endl;

  w = Rational(25,9);
  z = Rational(3,5);
  cout << "Testing arithmetic and relational " 
       << " operator overloading" << endl;
  cout << w << " * " << z << " = " << w * z << endl;
  cout << w << " + " << z << " = " << w + z << endl;
  cout << w << " - " << z << " = " << w - z << endl;
  cout << w << " / " << z << " = " << w / z << endl;
	
  cout << w << " <  " << z << " = " << (w < z) << endl;
  cout << w << " < " << w << " = " << (w < w) << endl;
  cout << w << " <= " << z << " = " << (w <= z) << endl;
  cout << w << " <= " << w << " = " << (w <= w) << endl;

  cout << w << " >  " << z << " = " << (w > z) << endl;
  cout << w << " > " << w << " = " << (w > w) << endl;
  cout << w << " >= " << z << " = " << (w >= z) << endl;
  cout << w << " >= " << w << " = " << (w >= w) << endl;

  w = Rational(-21,9);
  z = Rational(3,5);
  cout << w << " * " << z << " = " << w * z << endl;
  cout << w << " + " << z << " = " << w + z << endl;
  cout << w << " - " << z << " = " << w - z << endl;
  cout << w << " / " << z << " = " << w / z << endl;
  cout << w << " <  " << z << " = " << (w < z) << endl;
  cout << w << " < " << w << " = " << (w < w) << endl;
  cout << w << " <= " << z << " = " << (w <= z) << endl;
  cout << w << " <= " << w << " = " << (w <= w) << endl;

  cout << w << " >  " << z << " = " << (w > z) << endl;
  cout << w << " > " << w << " = " << (w > w) << endl;
  cout << w << " >= " << z << " = " << (w >= z) << endl;
  cout << w << " >= " << w << " = " << (w >= w) << endl;
  return 0;
}
// end file ch11prb4.tst.cc
