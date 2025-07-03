/****************************************************************
 *
 * File: [credit_validator.cpp]
 * By: [Ramanuja Mohanty]
 * Date: [07/02/25]
 *
 * Description: [Based on a provided list of Credit Card numbers
 *		 find if the numbers are valid.]
 * ****************************************************************/

#include <iostream> // For input-output handling
#include <iomanip>  // For 'setw' in main
#include <string>   // For length method
#include <vector>   // For vector methods in main
using namespace std;


bool isvalidcc(const string& card_num)
{
	int card_len = card_num.length(); // Length of string being fed into method.
	// First logic block: If card_len is 13-16 AND first digit is 3-6
	if ((card_len > 12 && card_len < 17) && (card_num[0] > '2' && card_num[0] < '7'))
	{
		// Second logic statement: If first digit is 3 and second digit is NOT 7
		// return false; made to handle AmEx Credit Card Requirement (37)
        	if (card_num[0] == '3' && card_num[1] != '7') return false;
		// Sum of ints in even places
        	int even_sum = 0;
		// Sum of ints in odd places
        	int odd_sum = 0;
		// Starts at last digit, works its way back to final digit, adds digit to odd_sum
	    	for (int ii = card_len - 1; ii > -1; ii -= 2)
		{
			// Doubles integer produced by subtraction of ASCII value of card_num[jj]
			// from '0' (48)
			odd_sum += card_num[ii] - '0';
		}
		// Starts at last digit, works its way back to final digit
		for (int jj = card_len - 2; jj > -1; jj -= 2)
		{
			// Doubles integer produced by subtraction of ASCII value of card_num[jj]
			// from '0' (48)
			int twice_num = (card_num[jj] - '0') * 2;
			// Handles double digit numbers
			if (twice_num > 9)
			{
				// Adds the quotient and remainder together.
				int twice_sum = (twice_num / 10) + (twice_num % 10);
				// Adds to even_sum
				even_sum += twice_sum;
			}
			// Otherwise adds to even_sum normally
			else even_sum += twice_num;
		}
		// Final check: If sum of even_sum and odd_sum is divisible by 10
		// Return true -> "is valid."
		if ((even_sum + odd_sum) % 10 == 0) return true;
	}
	// Base case: return false -> "is not valid."
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
