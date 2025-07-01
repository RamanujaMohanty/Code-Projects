#include <iostream>            // For input & output.
using namespace std;           // Use standard namespace.
const int N = 40;              // Define constant array size.

// Inline function to compute the sum of an array.
inline void sum (int& p, int n, int d[])
{
    int i;
    p = 0;                     // Initializes sum to 0.
    for (i = 0; i < n; ++i)    // Loops through elements in array.
    {
        p += d[i];             // Accumulates each value into p.
    }
}

int main()
{
    int i;                     
    int accum = 0;  // Variable to hold the final sum.
    int data[N];   // Declares an array of size N (40).

    for (i = 0; i < N; ++i) // Initialize array with values 0 to (N - 1).
    {
        data[i] = i;
    }
    sum(accum, N, data);  // Call sum to compute total and store in accum.
    cout << "sum is "<< accum << endl;  // Prints the result.
    
    return 0;  // Indicates successful program termination. 
}
