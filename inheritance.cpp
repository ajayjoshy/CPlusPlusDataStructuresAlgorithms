/* Apache License
Version 2.0, January 2004
http://www.apache.org/licenses/


The child class can inherit the base class using
any one of the public, private and protected access
specifiers


Types of inheritance:
#private: members of a base class is NOT inheritted. Any attempt
to print them in base class member functions will cause compilation error.
When a Base class is privately inheritted by the Child, the public and
protected elements of the base become the private elements of the child. 
The private elements of the Base remain un-inheritted by the Child

#protected elements are always inheritted either as protected or private depending on the
inheritance access specifier and accessible inside the Child.
protected  access specifier is needed if certain members must be inheritable but their
access must be restricted from non class member functions.
When the access specifier of Base is protected, the public and protected elements of the Base class becomes protected
members of the Child class. Private elements of the Base remains un-inheritted by the 
Child


#public elements are always inheritted and is accessible in non class member functions using 
the '.' operator.
When base class is publically inheriitted by the child both the public and protected 
memebers of the Base are inheritted as public and protected of the Child. As usual
the protected members of the Base is not inheritted

#constructor is invoked from base to child
#destructor is invoked from child to base

FIXME:NB: the private members are actually inheritted(but not accessible), we can tell from the 
size of the Child class objects. Only data members add to the size of object in the heap/stack





Polymorphism : implemented using virtual keyword
The Base class is used to represent the behavious of all its children.
Which means a base class object can point to any of its child classes but that base class object
MUST BE a POINTER or REFERENCE.

*/


#include<iostream>


class Base {
private:

	/*Dont do this, warning: extended initializer lists only available with -std=c++11 or -std=gnu++11*/
	int a{1};
/*	char test[100] = {0};*/ /*NB: uncomment to see the sizes of the class objects rise by 100 bytes, in all the 
Child classes and the Base*/
public:
	Base(): b(1), c(3) {
	std::cout << "The Base class default constructor called, a=" \
	<< a << " b=" << b << " c=" << c << "sizeof(*this)" << sizeof(*this) << std::endl;};
	int b;
protected:
	int c;
};




/*Child1, inherts the class Base with private access*/
class Child1: private Base {
private:
        int a1;

public:
        int b1;
	Child1();/*Just the declaration, define it outside*/
	void printprivate () {
		std::cout << "a1=" << a1 << std::endl;
//		std::cout << "a=" << a; /*error: within this context*/
	};
	void printprotected () {
		std::cout << "b=" << b << std::endl;
	}
protected:
        int c1;
};

Child1::Child1(): a1(11), b1(22), c1(33) {
	 std::cout << "The Child1 class default constructor called,\na1=" \
        << a1 << " b1=" << b1 << " c1=" << c1 << "sizeof(*this)" << sizeof(*this)  << std::endl;
	}



/*Child2, inherits the class Child1 with public access*/
class Child2: public Child1 {
private:
	int a2;
public:
	int b2;

	Child2(): a2(111), b2(222), c2(333) {
         std::cout << "The Child2 class default constructor called,\na2=" \
        << a2 << " b2=" << b2 << " c2=" << c2 << "sizeof(*this)" << sizeof(*this)  << std::endl;};

	void printBase() {
	/*Following statements are private or not inheritted by Child1, hence they 
	are not avaialble in Child2*/
	//	std::cout << "a=" <<a <<std::endl;
	//	std::cout << "b=" <<b <<std::endl;
	//	std::cout << "c=" <<c <<std::endl;
	}
	void printprotected () {
		std::cout << "c1=" << c1 << std::endl;
	}
protected: 
	int c2;
};


/*Inherits the Base class with protected access*/
class Child3: protected Base {
	
	/*Dont do this, warning: non-static data member initializers only available with -std=c++11 or -std=gnu++11*/
	int a3 = -1;
	protected: 
	int b3;
	public:
	 Child3(): a3(1111), b3(2222), c3(3333) {
         std::cout << "The Child3 class default constructor called,\na3=" \
        << a3 << " b3=" << b3 << " c3=" << c3 << "sizeof(*this)" << sizeof(*this) << std::endl;};
	int c3;
};


class Child4: public Child3, public Child2 {
	int z;
};


int main () 
{
	std::cout << "\nCreating Child1 C1, Base--(private)-->Child1 ..." << std::endl;
	Child1 C1;
//	C1.printprivate();
//	C1.printprotected();


	std::cout << "\nCreating Child2 C2, Base--(private)-->Child1--(protected)-->Child2 ..." << std::endl;
	Child2 C2;
//	C2.printBase();
//	C2.printprotected();


	std::cout << "\nCreating Child3 C3, Base--(public)-->Child3 ..." << std::endl;
	Child3 C3;
//	std::cout << "In main C3.c3: "  << C3.c3 << std::endl;

	std::cout << "\nCreating Child4 C4, Base--(public)-->Child3--(public)-->Child4 and \
	Base--(private)-->Child1--(protected)-->Child2--(public)-->Child4 ..." << std::endl;
	Child4 C4;/*sizeof(C4) = sizeof()*/ 
	std::cout << "There is overlapping of inheritted members in Child4 objects, sizeof(C4):" << sizeof(C4) \
	<< " = sizeof(C3):" << sizeof(C3) << " + sizeof(C2):" << sizeof(C2) << " + sizeof(C4.z):"<<  sizeof(int) \
	<< std::endl;
}
