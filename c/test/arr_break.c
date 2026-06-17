#include <string.h>
#include <stdio.h>

int main()
{
    char test_str[] = "Hello I am under the water";
    char * test_ptr = strtok(test_str, " ");

    return 0;
}
