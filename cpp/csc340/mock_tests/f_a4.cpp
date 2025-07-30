#include <iostream>
using namespace std;

int funcB(int);

int funcA(int n)
{
    if (n <= 1) return 1;
    else return n + funcB(n - 2);
}

int funcB(int n)
{
    if (n <= 3) return 1;
    else return n * funcA(n - 3);
}

int main()
{
    int num = 11;
    cout << funcA(num) << endl;
    return 0;
}
