#include <stdio.h>

long fibonacci(int n)
{
    long f2 = 0, f1 = 1, f_old;
    int ii;

    for (ii = 0; ii < n; ii++)
    {
        f_old = f2;
        f2 = f2 + f1;
        f1 = f_old;
    };

    return f2;
}

long recursive_fibonacci(int n)
{
    if (n <= 1) return n;
    else return (recursive_fibonacci(n - 1) + recursive_fibonacci (n - 2));
}

int main(void)
{
    int how_many = 0, ii;
    printf("I want table of fibonacci up to n: ");
    scanf("%d", &how_many);
    printf("\n fibonacci\n");
    for (ii = 0; ii < how_many; ii++)
    {
        printf("\n%d\t %ld %ld\n", ii, fibonacci(ii), recursive_fibonacci(ii));
    }
}
