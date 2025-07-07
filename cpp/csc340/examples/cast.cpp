#include <iostream>
using namespace std;

int main()
{
	double purchaseAmount;
	cout << "Enter purchase amount: ";
	cin >> purchaseAmount;

	double tax = purchaseAmount * 0.06;
	cout << "Sales tax is " << tax << endl;

	cout << "Sales tax is " << static_cast<int>(tax) << endl;

	return 0;
}
