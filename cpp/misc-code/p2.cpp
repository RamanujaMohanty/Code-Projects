#include <iostream>
using namespace std;
#define log(x) cout << x << endl;

int main()
{
    int* pCount = nullptr;
    int num = 5;
    pCount = &num;
    //-----------------------
    log(pCount);  // Original memory address
    *pCount++;    // Changed to point at a memory location
                  // one memory unit larger than it used to be.
    log(pCount);  // New memory address
    log(*pCount); // Random
    //-----------------------
    pCount = &num;
    log(*pCount);
}
