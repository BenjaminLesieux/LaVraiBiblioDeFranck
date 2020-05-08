#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

int main() {

    Node *head = createLinkedList(3);
    Node *second = createNewNode(4);
    Node *third = createNewNode(2);
    Node *fourth = createNewNode(111);

    add(head, second);

    printLinkedList(head);

    addAt(&head, third, 0);
    add(head, fourth);
    printLinkedList(head);

    printf("\nThe size of your list is : %d\n", getSize(head));

    removeAt(&head, 4);
    printLinkedList(head);

    return 0;
}