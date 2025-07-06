#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedListNodeTag
{
    struct LinkedListNodeTag *next;
    int val;
} LinkedListNode;

LinkedListNode *allocateNode(int val) 
{
    LinkedListNode *node = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    node->next = NULL;
    node->val = val;    
    return node;
}

// void showMenu(LinkedListNode **head)
void showMenu()
{
    fflush(stdin);
    printf("add node: a\n");
    printf("delete node: d\n");
    printf("find node: f\n");
    printf("print list: p\n");

    char input;
    scanf("%c", &input);
    fflush(stdin);
    switch (input) {
        case 'a':
            int val;
            printf("Enter value of new node: ");
            scanf("%d", &val);
            printf("User entered: %d\n", val);

            break;
        case 'd':
            break;
        case 'f':
            break;
        case 'p':
            break;
        default:
            break;
    }
}

int main()
{
    // LinkedListNode *head = NULL;
    while (1) {
        // showMenu(&head);
        showMenu();
    }
    return 0;
}