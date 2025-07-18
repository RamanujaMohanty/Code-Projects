#include <iostream>
#include <vector>
using namespace std;

// functions prototypes
void t1();
void t2();
void t3();
void t4();

static int x = 1; // x = 1
int y = x * 2;    // y = 2

int main()
{
    vector<int> vec1{1,3,5,7,9,11,13,15};
    vector<int> vec2{0,2,4,6,8,10};
    vec1.swap(vec2);
    int* ptr = &vec2[7];
    y = *(ptr - 2); // y = 11

    t1();
    t2();
    t3();
    t3();
    t4();
    return 0;
}

void t1(){
    cout << "x: " << x << " | y: " << y << endl;
    y -= 8;
    x += -1;
}
void t2(){
    int& x = y;
    x+= ::x++;
    cout << "x: " << x << " | y: " << y << endl;
}
void t3(){
    int y = x;
    static int x = 2;
    cout << "x: " << x + 1 << " | y: " << y + 2 << endl;
    x += y;
}
void t4(){
    int y = x + ::x;
    int& z = ::y;
    z += -1;
    cout << "x: " << x + z << " | y: " << y << endl;
}
