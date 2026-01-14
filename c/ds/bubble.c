#include <stdio.h>
#define SIZE 5

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(int count, int data[], char *str)
{
    int ii;
    printf("%s", str);
    for (ii = 0; ii < count; ii++)
    {
        printf("%d\t", data[ii]);
    }
}

void bubble(int data[], int count)
{
    int ii, jj;
    int keep_going;
    for (ii = 0; ii < count; ii++)
    {
        print_array(count, data, "\ninside bubble\n");
        printf("ii = %d, input any int to keep_going: ", ii);
        scanf("%d", &keep_going);
        for (jj = count - 1; jj > ii; jj--)
        {
            if (data[jj - 1] > data[jj])
            {
                swap(&data[jj - 1], &data[jj]);
            }
        }
    }
}

int main(void)
{
    int grades[SIZE] = {78, 67, 92, 83, 88};
    print_array(SIZE, grades, "My grades\n");
    printf("\n\n");
    bubble(grades, SIZE);
    print_array(SIZE, grades, "My sorted grades\n");
    printf("\n\n");
    return 0;
}
