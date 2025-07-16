#include <iostream>
using namespace std;

int main() 
{
	int first;
	int second;
	char oper;
	double result;
	cout << "Enter the first number: ";
	cin >> first;
	cout << "Enter the second number: ";
	cin >> second;
	cout << "Enter an operator (+, -, *, /): ";
	cin >> oper;
	switch(oper) 
	{
	case '+':
		result = first + second;
		break;
	case '-':
		result = first - second;
		break;
	case '*':
		result = first * second;
		break;
	case '/':
		if (second != 0)
		{
			result = static_cast<double>(first) / second;
		}
		else 
		{
			cout << "Cannot divide by zero. Goodbye." << endl;
		}
		break;
	default:
		cout << "Invalid operator." << endl;
	}
	cout << "Result: " << result << endl;
	return 0;
}