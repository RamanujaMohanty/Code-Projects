#include <stdio.h> // Included header file for standard functions.
#include <math.h> // Included header file for all math-based functions.

int main(void) // Main function.
{
    // For loop. Starts at 0.0, ends at 1.0, iterates by 0.10.
    for (double ii = 0.0; ii < 1.0; ii += 0.1)
    {
        // Every iteration will start with number | sin of number: result | cosine of number: result
        printf("Number: %.2lf | sin(%.2lf): %lf | cos(%.2lf): %lf.\n", ii, ii, sin(ii), ii, cos(ii));
    }
    return 0;
}
