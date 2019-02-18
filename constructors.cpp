/* Apache License
Version 2.0, January 2004
http://www.apache.org/licenses/

This is a sample file to explore the different types of constructors
Constructors are used for initialization, have no return type but has 
arguments which means they can be overloaded

1) Default constuctors: No arguments, automatically created by the compiler
done so only if no other user defined constructors are present eg Car obj1;

2) Parameterized Constructor: Takes in one or more arguments. Default construtor 
is not created by compiler if this is defined

3) Copy Constructor: Used to initialize an object with values contained in another
pre-existing object of the same class.

Shallow copy bug: Occurs when there are pointers in a class and default copy constructor is invoked
Shallow copy is when the only the pointer address / reference of a member variable is copied 
between objects using a copy constructor.
Deep copy is when seperate memory is allocated for the pointer member and then the data copied to it
from the pre-existing object. We need a user defined copy constructor for this purpose
Rule: If some form of memory is dynamically allocated to a member variable, implement deep copy
copy constructor, destructor which frees this memory, copy assignment operator overloading with deep copy

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
	<<" y=" << y << std::endl;
	ptr = new int(10);
	};

	Test(int a, int b ) : x(a), y(b) {std::cout << "Parameterized constructor called, x=" \
		<< x << " y=" << y << std::endl;
	ptr = new int(20);
	};
	
	/*Leave commented to use default copy constuctor. Or explicity define it as below*/
	/*Copy constructor is invoked when a) args passed by value, b) return by value, c) instantiating a new obj*/
	/*The argument of a copy constructor is pass by reference to otherwise avoid a recursive call to the copy constructor due to pass by value*/

#if 1   /*If 0 addr value in  ptr is same due to shallow copy, if 1 they are different due to deep copy*/
	Test(const Test& rhs) : x(rhs.x), y(rhs.y) 
	{
		std::cout << "user defined copy constructor, ptr:" << ptr << std::endl;
		ptr = new int(*rhs.ptr);
		
	};
#endif
	~Test() {std::cout << "Destructor invoked" << std::endl;
		delete ptr;
		};

	int& getx() {return x;}; /*Return reference to avoid additional memory usage in main()*/
	int& gety() {return y;};
	int*& getptr() {return ptr;};
	private:	
	int x, y;
	int *ptr;
};

typedef Test Test;

int main () 
{
	Test A(1,2), C;
	Test B = A;
	std::cout << "B.x: " << B.getx() << " B.y: " << B.gety() << std::endl; 
	std::cout << "C.x: " << C.getx() << " C.y: " << C.gety() << std::endl;
	std::cout << "A.ptr(address value in ptr) = " << A.getptr() << std::endl;
	std::cout << "B.ptr(address value in ptr) = " << B.getptr() << std::endl;
	return 0;
}
