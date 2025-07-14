#include <iostream>
#define log(x) std::cout << x << std::endl;

int main()
{
	int num = 5;
	void* pNum = &num;
	log(typeid(pNum).name());
    log(pNum);
	log(&pNum);

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
    // ------------
    *pCount++;
    log(pCount);
    log(*pCount);
    // ------------
    pCount = &count;
    log(*pCount);
    (*pCount)++;
    log(*pCount);
}
