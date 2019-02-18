/* Apache License
Version 2.0, January 2004
http://www.apache.org/licenses/

This sample file explains how strcut is used in c++.
Its similar to class in most ways since it can also have 
data members, member functions and access specifiers like
public, private.

Key difference is that inside a struct if the public: is the
default access specifier compared to private: in a class

In c++ a strcut and class are same except for the default
access specifier, struct can be used in place of a class



Static members of a class/struct
# They dont belong to an object they belong to the class
# Static member functions have no *this pointer, since they dont bind to any object
# Static member functions can access other static functions and variables but not
non static members, because non-static members belong to an object.
#C++ does not support static constructors. This is why we initialize static members 
outside the class
#Even private static variables can be initialized in global scope
#non static member functions can access static member functions but not vice-versa
#static members have the golbal scope or more specifically the class scope

#Uses a) Store and print class/struct metadata
      b) Include object agnostic utility functions in the class/struct	
*/

#include<iostream>

struct Point {
	int x;
	int y;

	/*Added userdefined constrcutor since count needs to monitored for 
	  cases when default constructer gets called*/
	Point() : x(0), y(0) {count++; std::cout << "Default constructor count:" << count << std::endl; }; 

	Point(int X, int Y);

	int& getxcoord() {return x;};
	int& getycoord() {return y;};
	int& getpriv_nonstatic() {return priv;};
	/*Static function*/
	static int getstatic();/* Cannot return int& error: binding ‘const int’ to reference of type ‘int&’ discards qualifiers*/
	/*Public Static member*/
	static int count /* = 0*/; /*Cannot initialize non const static members in class def*/

	private:
	/*static const, hence defined inside struct*/
	static const int METADATA = 1234;
	static int priv;
};

Point::Point(int X, int Y) : x(X), y(Y)
{
	count++;
	std::cout << "Parameterised constructor x=" << x << " y=" << y << " count:" << count << std::endl;
}

/*Declare count as public to do this, also dont forget the "int"*/
int Point::count = 0; /*Define the static member, else get compilation error undefined reference to `Point::count'*/

int Point::priv = 15;

int Point::getstatic() /*Definition of static function. DONOT use static keyword again*/
{	
	return METADATA;
}

int main ()
{
	Point A;
	Point B(22, 49);
	std::cout << "Count: " << Point::count << std::endl;
	std::cout << "METADATA: " << Point::getstatic() << std::endl;
	std::cout << "Non Static member fn, fetch priv static member: " << A.getpriv_nonstatic() << std::endl; 
	return 0;
}
