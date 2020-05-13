//
// Created by Benjamin Lesieux on 08/05/2020.
//

#include "LinkedList.h"

/**
 * @def - Créé une liste chaîne, plus précisément créé le premier noeud de cette liste
 * @param - @void value : la valeur du type choisi
 * */
Node *createLinkedList(void *value) {
    Node *head = NULL;
    head = (Node*) malloc(sizeof(Node));

    if (head == NULL) printf("Erreur lors de l'allocation mémoire d'un Noeud");

    head->next = NULL;
    head->value = value;

    return head;
}

/**
 * @def - Même fonction qu'au dessus mais avec un nom différent, cela permet
 * de ne pas se perdre entre la tête et les autres noeuds
 * */
Node *createNewNode(void *value) {
    return createLinkedList(value);
}

/**
 * @def - Ajoute un noeud après le dernier noeud connu
 * @param - headNode, la tête de liste ; newNode, le noeud à mettre en bout de liste
 * */
void add(Node *headNode, Node *newNode) {

    Node *lastNode = headNode;

    if (find(headNode, newNode->value) != -1) {
        printf("\nElement déjà présent dans la liste ");
        return;
    }

    while (lastNode->next != NULL) {
        lastNode = lastNode->next;
    }

    lastNode->next = newNode;
}

/**
 * @def - Ajoute un noeud à l'index souhaité et décale ceux d'après
 * Si index supérieur à taille de la liste, alors il sera placé en dernier
 * @param - headNode, la tête de liste ; newNode, le noeud à mettre en bout de liste ; index
 * */
void addAt(Node **headNode, Node *newNode, int index) {

    Node *nodeAtIndex = *headNode;
    Node *nextNode = NULL;

    if (find(*headNode, newNode->value) != -1) {
        printf("\nElement déjà présent dans la liste ");
    }

    else if (index == 0) { // Si l'user veut une nouvelle tête
        newNode->next = *headNode;
        *headNode = newNode;
    }

    else {
        int i = 0;
        while (i < (index-1) && nodeAtIndex->next != NULL) {
            nodeAtIndex = nodeAtIndex->next;
            i++;
        }

        nextNode = nodeAtIndex->next;
        newNode->next = nextNode;
        nodeAtIndex->next = newNode;
    }
}

unsigned int getSize(Node *head) {
    unsigned int num = 0;
    Node *node = head;

    while (node != NULL) {
        node = node->next;
        num++;
    }

    return num;
}

void removeAt(Node **head, int index) {
    Node *current = *head;

    if (index >= getSize(*head)) {
       printf("\nVotre index est en dehors de la liste");
    }

    else if (index == 0) {
        current = (*head)->next;
        free(head);
        *head = current;
    }

    else {
        int i = 0;


        while (i < (index - 1) && current->next != NULL) {
            current = current->next;
            i++;
        }

        Node *toDelete = current->next;
        current->next = toDelete->next;
        free(toDelete);
    }
}

void printLinkedList(Node *linkedList) {

    Node *list = linkedList;

    while (list != NULL) {
        printf("\n%d", list->value);
        list = list->next;
    }
}

int find(Node *head, void *toFind) {
    Node *current = head;
    int i = 0;
    int index = -1;
    unsigned int size = getSize(head);

    while (current->next != NULL && i < size) {

        if (current->value == toFind) index = i;

        current = current->next;
        i++;
    }

    return index;
}

Node *getFrom(Node *head, void *value) {
    Node *current = head;

    int i = 0;
    unsigned int index = find(head, value);

    while (i < (index - 1) && current->next != NULL) {
        current = current->next;
        i++;
    }

    return current;
}
