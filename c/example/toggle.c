#include <stdio.h>
#include <stdbool.h>

int main()
{
    int ii = 0;
    int increment = 1;
    int value = 0;
    while (true) {
        // in real world, you would use for loops
        // this just shows how you may toggle
        if (value < -8 || value > 8) {
            increment = -increment;
            printf("\n");
        }
        value += increment;
        printf("%2d ", value);
    }

    return 0;
}
