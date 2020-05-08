//
// Created by Benjamin Lesieux on 08/05/2020.
//

#include "LinkedList.h"

Node *createLinkedList(void *value) {
    Node *head = NULL;
    head = (Node*) malloc(sizeof(Node));

    if (head == NULL) printf("Erreur lors de l'allocation mémoire d'un Noeud");

    head->next = NULL;
    head->value = value;

    return head;
}

Node *createNewNode(void *value) {
    return createLinkedList(value);
}

void add(Node *headNode, Node *newNode) {

    Node *lastNode = headNode;

    while (lastNode != NULL) {
        lastNode = headNode->next;
    }

    lastNode->next = newNode;
}

void addAt(Node *headNode, Node *newNode, int index) {

    Node *previousNode = headNode;
    Node *nodeAtIndex = headNode;

    int i = 0;

    while (i < index && previousNode->next != NULL) {
        previousNode = nodeAtIndex;
        i++;
        nodeAtIndex = previousNode->next;
    }

    previousNode->next = newNode;
    newNode->next = nodeAtIndex;
}