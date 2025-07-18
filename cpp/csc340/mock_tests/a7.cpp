#include <iostream>
using namespace std;

int x = 3, y = 2;

void swapplus1(int n1, int n2) {
    int temp = n1;
    n1 = n2;
    n2 = temp;
}
void swapplus2(int& n1, int& n2) {
    int temp = n1;
    n1 = n2;
    n2 = temp;
}
void swapplus3(const int& n1, const int& n2) {
    int temp1 = n1;
    int temp2 = n2;
    temp2 = temp1;
}
void swapplus4(int* p1, int* p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
void swapplus5(int* &p1, int* &p2) {
    int* temp = p1;
    p1 = p2;
    p2 = temp;
}
void print(const int& x, const int& y) {
    cout << "\n x: " << x << " |y: " << y;
}
int main() {
    int arr[] {0,2,4,6,8,10,12,14};
    y = arr[4]/size(arr);
    cout << "arr[4]: " << arr[4] << " | size(arr): "
        << size(arr) << " | y: " << y << endl;
    swapplus1(x,y);     print(x,y);
    swapplus2(x,y);     print(x,y);
    swapplus3(x,y);     print(x,y);
    swapplus4(&x,&y);   print(x,y);
    int *px = &x, *py = &y;
    swapplus5(px,py);   print(x,y);
    cout << endl;
    return 0;
}
