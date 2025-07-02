#include <iostream>
#include <string>

int main()
{
	std::string test_string = "0123456789";
	int str_len = test_string.length();
	for (int ii = 0; ii < str_len; ++ii)
	{
		int char_int = (static_cast<int>(test_string.at(ii)) - 48);
		std::cout << "Char value: " << char_int << std::endl;
	}
	return 0;
}
