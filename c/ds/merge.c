#include <stdio.h>
#define SIZE 5

void arr_print(int count, int data[], char *str)
{
    int ii;
    printf("%s", str);
    for (ii = 0; ii < count; ii++)
    {
        printf("%d\t", data[ii]);
    }
}

void merge(int a[], int b[], int c[], int count)
{
    int ii = 0, jj = 0, kk = 0;
    while (ii < count && jj < count)
    {
        if (a[ii] < b[jj])
        {
            c[kk++] = a[ii++];
        }
        else
        {
            c[kk++] = b[jj++];
        }
    }
    while (ii < count) c[kk++] = a[ii++];
    while (jj < count) c[kk++] = b[jj++];
}

int main(void)
{
    int a[SIZE] = {67, 82, 83, 88, 89};
    int b[SIZE] = {58,69, 72, 81, 88};
    int c[2 * SIZE];
    arr_print(SIZE, a, "My grades\n");
    printf("\n\n");
    arr_print(SIZE, b, "More of my grades\n");
    printf("\n\n");
    merge(a, b, c, SIZE);
    arr_print(2 * SIZE, c, "My sorted grades\n");
    printf("\n\n");
    return 0;
}
