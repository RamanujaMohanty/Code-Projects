#include <iostream>
#include <string>
using namespace std;

string * func {
	string message = "Hello CSC340";
	string *ptr = &message;
	cout << "Value in func(): " << *ptr << endl;
	return ptr;
}

int main()
{
	string *ptr = func();
	cout << "Value in main:   " < *ptr << endl; 
}
