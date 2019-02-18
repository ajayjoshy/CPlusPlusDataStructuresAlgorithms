/* Apache License
Version 2.0, January 2004

This is a sample file to explore the different types of constructors
Constructors are used for initialization, have no return type but has 
arguments which means they can be overloaded

1) Default constuctors: No arguments, automatically created by the compiler
done so only if no other user defined constructors are present eg Car obj1;

2) Parameterized Constructor: Takes in one or more arguments. Default construtor 
is not created by compiler if this is defined

3) Copy Constructor: Used to initialize an object with values contained in another
pre-existing object of the same class.

Destructor: used to release the resources allocatred by the constructor
eg: any memory allocaled explicitly using new, malloc.
Destructor has no arguments, which means it cannot be overloaded
Default destructor is synthesized if user has not defined one
*/

#include<iostream>

class Test 
{
	public:
	Test() : x(-1), y(-2) {std::cout << "Default constructor called " << "x=" << x \
	<<" y=" << y << std::endl;};

	Test(int a, int b ) : x(a), y(b) {std::cout << "Parameterized constructor called, x=" \
		<< x << " y=" << y << std::endl;};
	
	/*Leave commented to use default copy constuctor. Or explicity define it as below*/
	Test(const Test& rhs) : x(rhs.x), y(rhs.y) {std::cout << "user defined copy constructor" << std::endl;};

	~Test() {std::cout << "Destructor invoked" << std::endl;};

	int& getx() {return x;}; /*Return reference to avoid additional memory usage in main()*/
	int& gety() {return y;};

	private:	
	int x, y;
};

typedef Test Test;

int main () 
{
	Test A(1,2), C;
	Test B = A;
	std::cout << "B.x: " << B.getx() << " B.y: " << B.gety() << std::endl; 
	std::cout << "C.x: " << C.getx() << " C.y: " << C.gety() << std::endl;
	return 0;
}
