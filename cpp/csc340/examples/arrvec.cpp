#include <iostream>
#include <vector>
using namespace std;

int main()
{
	// Program Title & Description
	cout << "CSC 340 - Example 8 - Arrays & Vectors\n" << endl;
	// ARRAYS
	// C/C++ Array Declaration
	int arr[] = {1,2,3,4,5};
	// Array Length Steps; No built-in function
	cout << "sizeof(arr): " << sizeof(arr) << endl;
	cout << "sizeof(arr[0]): " << sizeof(arr[0]) << endl;
	cout << "Length of arr: " << (sizeof(arr) / sizeof(arr[0])) << endl;
	// Out-of-bounds (Unsafe) Array Access
	cout << "\nNo index range checking: " << endl;
	cout << "arr[17]: " << arr[17] << endl;
	//
	cout << "\nIterate primitive array 1: " << endl;
	for (unsigned int ii = 0; ii < (sizeof(arr) / sizeof(arr[0])); ++ii)
	{
		cout << arr[ii] << " ";
	}
	//
	cout << "\nIterate primitive array 2: " << endl;
	for (const int &arrEntry : arr)
	{
		cout << arrEntry << " ";
	}
	// VECTORS
	cout << "\nVector, iterate vector 1" << endl;
	vector<int> vec = {1,2,3,4,5};
	for (int ii = 0; ii < vec.size(); ++ii)
	{
		cout << vec[ii] << " ";
	}
	cout << "\n" << endl;
}
