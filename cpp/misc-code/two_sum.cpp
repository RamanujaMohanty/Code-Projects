#include <iostream>

int main()
{
	int a;
	std::cout << "Enter number: ";
	std::cin >> a;
	int a_quo = a / 10;
	int a_rem = a % 10;
	int a_sum = a_quo + a_rem;
	std::cout << "The sum of " << a << " is " << a_sum << std::endl;
	return 0;
}
