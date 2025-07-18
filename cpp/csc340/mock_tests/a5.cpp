// Please see README.txt
// We will go over the answers in class.
// Thank you.
#include <iostream>
using namespace std;

int main()
{
	string cs = "CSC340";
	string& csRef = cs;
	string* const csPtr = &csRef;
	// Please use csPtr to code a pointer which points to cs.
	// Change the value of cs through this new pointer.
	string* newPtr = csPtr;
	*newPtr = "new" + *newPtr;
	cout << "cs: " << cs << endl; // cs: newCSC340
	// Please code an lvalue reference to reference csPtr
	string* const& csPtrRef = csPtr;
	cout << "csPtrRef: " << csPtrRef << endl;
	cout << "*csPtrRef: " << *csPtrRef << endl;
	cout << "*csPtr: " << *csPtr << endl;
	cout << "cs: " << cs << endl;
	/*
	csPtrRef: 00000075BD0FFA88
	* csPtrRef : newCSC340
	* csPtr : newCSC340
	cs : newCSC340
	*/
	// Please code an rvalue reference to reference csRef
	string&& csRef_rValueRef = move(csRef);
	cout << "csRef_rValueRef: " << csRef_rValueRef << endl;
	cout << "cs: " << cs << endl;
	cout << "csRef: " << csRef << endl;
	/*
	csRef_rValueRef: newCSC340
	cs: newCSC340
	csRef: newCSC340
	*/
	// List at least 3 ways to change the value of cs.
	cs = "CS1";
	csRef = "CS2";
	*csPtr = "CS3";
	cout << "cs: " << cs << endl;
	cout << "csRef: " << csRef << endl;
	cout << "*csPtr: " << *csPtr << endl;
	/*
	cs: CS3
	csRef: CS3
	*csPtr: CS3
	*/
	return 0;
}
