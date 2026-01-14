/*
 * File:    elephant_seal_average.c
 * Purpose: Read northern elephant seal weights from a text file into an array,
 *          then compute and display the average weight.
 *
 * Input:   A text file containing numeric weights (one per line or separated by whitespace).
 * Output:  Prints the number of weights read and the average weight.
 *
 * Notes:
 *  - This program uses a fixed-size array (as required by the assignment).
 *  - If the file contains more than MAX_WEIGHTS values, extra values are ignored.
 */

#include <stdio.h>

#define MAX_WEIGHTS 10000

/*
 * read_weights
 * Purpose:  Read weights from an input file into an array.
 * Inputs:   filename  - name of the input file to open
 *           weights   - array to store read weights
 *           capacity  - maximum number of elements that can be stored in weights
 * Output:   Returns the number of weights successfully read (0 if none),
 *           or -1 if the file could not be opened.
 */
int read_weights(const char *filename, double weights[], int capacity)
{
    FILE *file_ptr = fopen(filename, "r");
    int count = 0;

    if (file_ptr == NULL) {
        return -1;
    }

    while (count < capacity && fscanf(file_ptr, "%lf", &weights[count]) == 1) {
        count++;
    }

    fclose(file_ptr);
    return count;
}

/*
 * compute_average
 * Purpose:  Compute the arithmetic mean of values in an array.
 * Inputs:   values - array of numbers
 *           count  - number of valid elements in values
 * Output:   Returns the average. If count is 0, returns 0.0.
 */
double compute_average(const double values[], int count)
{
    double sum = 0.0;
    int i;

    if (count <= 0) {
        return 0.0;
    }

    for (i = 0; i < count; i++) {
        sum += values[i];
    }

    return sum / count;
}

int main(void)
{
    double weights[MAX_WEIGHTS];
    const char *filename = "elephant_seal_data.txt";
    int num_weights;
    double average_weight;

    num_weights = read_weights(filename, weights, MAX_WEIGHTS);
    if (num_weights == -1) {
        printf("Error: Could not open file '%s'.\n", filename);
        return 1;
    }

    if (num_weights == 0) {
        printf("Error: No valid weights found in '%s'.\n", filename);
        return 1;
    }

    average_weight = compute_average(weights, num_weights);

    printf("Number of elephant seal weights read: %d\n", num_weights);
    printf("Average elephant seal weight: %.2f\n", average_weight);

    return 0;
}
