#include <stdio.h>
#define PI 3.14159

int main (void)
{
    double r;
    printf("Enter radius: ");
    scanf("%lf", &r);
    double volume = (4 * PI * (r * r * r))/3;
    printf("volume is : %lf \n\n", volume);
    return 0;
}
