/*
 * File: sc_calc.c
 * Purpose:
 *   Print a formatted table of sine and cosine values for x in (0, 1),
 *   using radians. This program demonstrates basic looping, formatting,
 *   and calling <math.h> functions.
 *
 * Build (example):
 *   gcc -Wall -Wextra -std=c11 sc_calc.c -lm -o sc_calc
 *
 * Run:
 *   ./sc_calc
 *
 * Output:
 *   A table with columns: x, sin(x), cos(x)
 */

#include <math.h>
#include <stdio.h>

/*
 * Function: print_sin_cos_table
 * Purpose:
 *   Print a table of sin(x) and cos(x) for values strictly between 0 and 1.
 *
 * Parameters:
 *   step - increment size (must be > 0 and < 1)
 *
 * Returns:
 *   Nothing (prints to stdout).
 */
static void print_sin_cos_table(double step)
{
    /* Use an integer loop to avoid floating-point accumulation drift. */
    const int rows = (int)(1.0 / step);

    printf("%8s  %14s  %14s\n", "x", "sin(x)", "cos(x)");
    printf("%8s  %14s  %14s\n", "--------", "--------------", "--------------");

    /* i = 1 .. rows-1 ensures 0 < x < 1 (exclusive endpoints). */
    for (int i = 1; i < rows; ++i)
    {
        double x = i * step;
        printf("%8.2f  %14.10f  %14.10f\n", x, sin(x), cos(x));
    }
}

int main(void)
{
    print_sin_cos_table(0.10);
    return 0;
}

