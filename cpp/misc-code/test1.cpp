#include <iostream>
#include <cstdint>

using namespace std;

/*
    [ptr1] -> [address of memory location of a]
*/

int main()
{
    // using test_type = int64_t;
    // using test_type = int16_t;
    using test_type = int32_t;
    test_type *ptr1, *ptr2;
    test_type a = 5;
    ptr1 = &a;
    cout << "initial value of a = " << *ptr1 << endl;
    *ptr1 = 7;
    cout << "value of a after assignment = " << *ptr1 << endl;
    ptr2 = ptr1;
    cout << "value of a via ptr2 = " << *ptr2 << endl;
    cout << "address of a, stored in ptr1: " << ptr1 << endl;
    cout << "address of a, stored in ptr2: " << ptr2 << endl;
    ++ptr2;
    cout << "new address stored in ptr2 after increment: " << ptr2 << endl;
    cout << "ptr2 is now ahead of ptr1 by " << (char *)ptr2 - (char *)ptr1 << " bytes\n";
    cout << "value of a using ptr1, in array notation: " << ptr1[0] << endl;
    cout << "value of a using ptr1, in alternative notation: " << *(ptr1 + 0) << endl;
    test_type arr[] = { 1, 2 };
    cout << "printing 2nd element of arr using normal notation: " << arr[1] << endl;
    cout << "printing 2nd element of arr using ptr notation: " << *(arr + 1) << endl;
    return 0;
}
