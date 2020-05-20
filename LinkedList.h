//
// Created by Benjamin Lesieux on 08/05/2020.
//

#ifndef LABIBLIODEFRANCK_LINKEDLIST_H
#define LABIBLIODEFRANCK_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include "DBBooks.h"

typedef struct Node_type{
    void *value;
    struct Node_type *next;
} Node;


void pushFirst(Node *node);
void add(Node *head, Node *newNode);
void addAt(Node **head, Node *newNode, int index);
void removeAt(Node **head, int index);
int find(Node *head, void *toFind);
Node *getFrom(Node *head, void *value);
Node *createLinkedList(void *value);
Node *createNewNode(void *value);
void printLinkedList(Node *linkedList);
unsigned int getSize(Node *head);
void *get(Node *head, int index);
void sortAlphaBooks(DBBooks *db);
void swap(Node *n1, Node *n2);

#endif //LABIBLIODEFRANCK_LINKEDLIST_H