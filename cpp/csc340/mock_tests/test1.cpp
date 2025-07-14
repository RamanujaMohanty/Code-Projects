#include <iostream>
#include <vector>
using namespace std;

static int x = 1;
int y = x * 2;

void t1()
{
    y++;
    cout << x << " " << y << endl;
    y += 1;
    x -= -1;
}

void t2()
{
    int* x = &y;
    cout << x << " " << y << endl;
}

void t3()
{
    int y = x;
    static int x = 2;
    cout << x + 1 << " " << y + x << endl;
    x += y;
}

void t4()
{
    int y = x + 1;
    int &z = y;
    z += -1;
    cout << x + z << " " << y << endl;
}

int main()
{
    vector<int> vec1{1,3,5,7,9};
    vector<int> vec2{2,4,6,8,10};
    vec1.swap(vec2);
    int *ptr = &vec1[1];
    y = *(ptr + 2);

    t1();
    t2();
    t3();
    t3();
    t4();

    return 0;
}
