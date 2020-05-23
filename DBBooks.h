//
// Created by Benjamin Lesieux on 13/05/2020.
//

#ifndef LABIBLIODEFRANCK_DBBOOKS_H
#define LABIBLIODEFRANCK_DBBOOKS_H

#include "LinkedList.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Book_type {
    char *title;
    char *author;
    char *code;
    int num;
    int disp;
} Book;

typedef struct DBBooks_type {
    Node *books;
    int numBooks;
} DBBooks;

Book *readBook(DBBooks *db);
void addBook(DBBooks *db, Book *book);
void removeBook(DBBooks *db, Book *book, int howMany);
void *getStyle(DBBooks *db, char* value);
void searchBook(DBBooks *db, int criteria, char *string);
int isBorrowed(Book *book); // Retourne le nombre de fois qu'il est emprunté
void updateXmlDBBooks(DBBooks *db);
void *getBooks(DBBooks *db);
void showBooks(DBBooks *db);
void sortAlphaBooks(Node *head);
Book *byCode(DBBooks *db, char *code);
#endif //LABIBLIODEFRANCK_DBBOOKS_H
