#include "om_vector.h"
using namespace omlib;

int main()
{
	OmVector<int> vec1;
	vec1.push_back(1);
	vec1.push_back(2);
	vec1.push_back(3);
	vec1.push_back(4);
	vec1.push_back(5);
	vec1.push_back(6);
	vec1.push_back(7);
	vec1.push_back(8);
	vec1.push_back(9);
	vec1.push_back(10);
	vec1.print();
	return 0;
}
