/* Apache License
Version 2.0, January 2004
http://www.apache.org/licenses/

const keyword can be applied to class memebers variables,
member functions and class object themselves

#const keyword is a qualifier that makes an object readonly
#a member function declared const cannot modify an member variables. const keyword is used both 
in declaration and definition.
#a class object declared const can only call member functions with const qualifier

Uses a) makes member functions unable to modify member variables
     b) Instantiate class objects which are exclusively used to access readonly data
*/

#include<iostream>

class Test { 
	private:
		const char a[10] = {'h','e','l','l','o'};
		/*C++11 supports this type of initializing, if userdefined constructors are
		  presnent those take precedence over this initialization*/
		int b{5};
	public:
		void printmembers() {std::cout << "a:" << a << " b:" << b << std::endl;};
		void printmembers_const() const;
};

void Test::printmembers_const() const
{
	//++b; /*error: increment of member ‘Test::b’ in read-only object*/
	std::cout << "Const a:" << a << " b:" << b << std::endl;
}

int main ()
{
	Test A;
	A.printmembers();
	A.printmembers_const(); /* a normal object can call const member functions */
	
	const Test B;
	//B.printmembers(); /*error: passing ‘const Test’ as ‘this’ argument discards qualifiers*/
	B.printmembers_const();
	return 0;
}
