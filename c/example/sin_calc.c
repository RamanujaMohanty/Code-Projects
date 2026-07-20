#include <stdio.h>
// Included header file for advanced math-based functions.
// sin function.
#include <math.h>

int main (void)
{
    // Variables for input (input) & output (result).
    double input;
    double result;
    // Use of scanf to read input.
    printf("Enter input: ");
    scanf("%lf", &input);
    // Uses if-else block to ensure that input is within bounds (0 < input < 1).
    if (input > 0.0 && input < 1.0)
    {
        result = sin(input);
        printf("result for sin of %lf: %lf.\n", input, result);
    }
    else
    {
        printf("%lf not within acceptable range\n.", input);
    }
    return 0;
}
