#include <iostream>
using namespace std;

int retValue() {
    int cs = 340;
    cout << "cs: " << &cs << endl;
    return cs;
}

int main()
{
    int x1 = retValue();
    cout << "x1: " << &x1 << endl << endl;

    // int & x2 = retValue(); // ERROR

    const int & x3 = retValue();
    cout << "x3: " << &x3 << endl << endl;

    int  && x4 = retValue();
    cout << "x4: " << &x4 << endl << endl;

    int && x5 = retValue();
    cout << "x5: " << &x5 << endl << endl;
}
