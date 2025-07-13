#include <iostream>
using namespace std;
#define log(x) cout << x << endl;

int main()
{
	int num = 5;
	void* pNum = &num;
	cout << "Type of pNum: " << typeid(pNum).name() << endl;
	cout << "pNum value: " << pNum << endl;
	cout << "&pNum value: " << &pNum << endl;

    int age = 21;
    int *pAge = &age;
    log(age);
    log(pAge);
    log(*pAge);
	return 0;

    int *pCount = nullptr;
    int count = 5;
    pCount = &count;
    log(pCount);
    *pCount++;
    log(pCount);
}
