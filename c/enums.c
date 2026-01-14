#include <stdio.h>

enum day {mon, tue, wed, thu, fri, sat, sun};

void print_day(enum day d)
{
    switch(d)
    {
        case mon:
        case tue:
        case wed:
        case thu:
        case fri:
            printf(" weekday ");
            break;
        case sat:
        case sun:
            printf(" weekend ");
            break;
        default: printf("%d is an error", d);
    }
}

enum day next_day(enum day d)
{
    return (d + 1 % 7);
}

int main()
{
    enum day today = fri;
    print_day(today);
    printf("\n\n");
    print_day(7);
    printf("\n\n");
    print_day(next_day(today));
    printf("\n\n");
    return 0;
}
