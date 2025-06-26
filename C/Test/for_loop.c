#include <stdio.h>

int main(void)
{
    int a = 0;
    for (int ii = 0; ii < 5; ii++)
    {
        a++;
    }
    printf("%d\n",a);

    for (int ii = 0; ii < 3; ii = ii + 1)
        printf("a\n");
        printf("b\n");
    printf("c\n");
    
    return 0;
}
