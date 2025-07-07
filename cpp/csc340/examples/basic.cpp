#include <iostream>
using namespace std;

int main()
{
	const int FIRST_APPEARANCE = 1928;
	int thisYear;

	cout << "Enter this year: ";
	cin >> thisYear;

	int age = thisYear - FIRST_APPEARANCE;
	cout << "Mickey is " << age << " years old." << endl;
	
	return 0;
}
