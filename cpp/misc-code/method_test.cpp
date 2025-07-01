#include <iostream>
#include <string>
using namespace std;

int main()
{
	bool is_valid_cc = false;
	string card_num = "1234567";
	int len = card_num.length();
	int o_sum = 0;
	for (int ii = len - 1; ii > 0; ii -= 2)
	{
		o_sum = (static_cast<int>(card_num.at(ii)) - 50);
		cout << o_sum << endl;
	}
	return 0;
}
