//Student NAME: Chet Michals

// file rational.h
#ifndef RATIONAL_H_
#define RATIONAL_H_

#include <iostream>
using namespace std;


class Rational
{
public:
  Rational(int numerator, int denominator);
  Rational(int numerator); // sets denominator to 1
  Rational(); // sets numerator to 0, denominator to 1

  friend Rational operator+(const Rational&, const Rational&);   //overaloading function for + operator
  friend Rational operator-(const Rational&, const Rational&);       //overaloading function for - operator
  friend Rational operator*(const Rational&, const Rational&);     //overaloading function for * operator
  friend Rational operator/(const Rational&, const Rational&);    //overaloading function for / operator
  friend bool operator<(const Rational&, const Rational&);          //overaloading function for < operator
  friend bool operator<=(const Rational&, const Rational&);       //overaloading function for <= operator
  friend bool operator>(const Rational&, const Rational&);       //overaloading function for > operator
  friend bool operator >=(const Rational&, const Rational& );   //overaloading function for >= operator
  friend bool operator ==(const Rational&, const Rational& );   //overaloading function for == operator
  friend ostream& operator <<(ostream&, const Rational&);     //overaloading function for << operator
  friend istream& operator >>(istream&, Rational&);              //overaloading function for >> operator

private:
  int n;   //Numerator
  int d;  //Denominator
};
  void normalize(int &n, int &d);    //Normalization function
#endif
//end file Rational.h

