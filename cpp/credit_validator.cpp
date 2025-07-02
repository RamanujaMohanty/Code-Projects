#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;


bool isvalidcc(const string& card_num)
{
	int card_len = card_num.length();
	if ((card_len > 12 && card_len < 17) && (card_num.at(0) == '4' || card_num.at(0) == '5' || card_num.at(0) == '6'))
    {
        int even_sum = 0;
        int odd_sum = 0;
        int total_sum = even_sum + odd_sum;
	for (int ii = card_len - 2; ii > 0; ii -= 2)
        {
             odd_sum += (static_cast<int>(card_num.at(ii)) - 48);
        }
        for (int jj = card_len - 1; jj > -1; jj -= 2)
        {
            int twice_num = (static_cast<int>(card_num.at(jj)) - 48) * 2;
            if (twice_num > 9)
            {
		    int twice_sum = (twice_num / 10) + (twice_num % 10);
		    even_sum += twice_sum;
            }
            else
            {
                even_sum += twice_num;
            }
        }
	if (total_sum % 10 == 0)
	{
		return true;
	}
    }
	return false;
}

int main()
{
	//
	// PLEASE DO NOT CHANGE function main
	//
	vector<string> cardnumbers = {
		 "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
		"4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
		"5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
		"4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
		"5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
		 "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
		"4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
		"5556551555555557", "6011316011016011"
	};

	int i;
	vector<string>::iterator itr;

	for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
		cout << setw(2)  << i << " "
			 << setw(17) << *itr
			 << ((isvalidcc(*itr)) ? " is valid" : " is not valid") << endl;
	}

	return 0;
}
