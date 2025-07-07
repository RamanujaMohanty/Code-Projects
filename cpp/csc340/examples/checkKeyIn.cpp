#include <iostream>
#include <string>
using namespace std;

int main()
{
	int number = 0;
	string prompt = "Please enter an integer then press Enter key: ";
	cout << prompt;

	while (!(cin >> number))
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << prompt;
	}

	cout << "Your integer:\t" << number << endl;
	cout << "Thank you." << endl;
	return 0;
}
