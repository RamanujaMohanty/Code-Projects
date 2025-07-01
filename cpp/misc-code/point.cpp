#include <iostream>
using namespace std;

int main()
{
	int num = 5;
	void* pNum = &num;
	cout << "Type of pNum: " << typeid(pNum).name() << endl;
	cout << "pNum value: " << pNum << endl;
	cout << "&pNum value: " << &pNum << endl;
	return 0;
}
