#include <iostream>
#include <string>
using namespace std;

int main()
{
	string test_cc = "4388576018402626";
	int len = test_cc.length();
	int odd_sum = 0, even_sum = 0;
	for (int ii = len - 1; ii > 0; ii -= 2)
	{
		cout << "Odd number " << ii << ": " << 
			(static_cast<int>(test_cc.at(ii)) - 48) << endl;
	}
	for (int jj = len - 2; jj > -1; jj -= 2)
	{
		int twice_even_num = (static_cast<int>(test_cc.at(jj)) - 48) * 2;
		if (twice_even_num > 9)
		{
			twice_even_num = (twice_even_num / 10) + (twice_even_num % 10);
		}
		cout << "Even number " << jj << ": " << twice_even_num << endl;
	}
	return 0;
}
