//
// Created by Benjamin Lesieux on 13/05/2020.
//

#ifndef LABIBLIODEFRANCK_DBBOOKS_H
#define LABIBLIODEFRANCK_DBBOOKS_H

#include "LinkedList.h"

typedef struct Book_type {
    char *title;
    char *author;
    char code[7];
    int num;
    int disp;
} Book;

typedef struct DBBooks_type {
    Node *books;
} DBBooks;

Book *readBook();
void addBook(DBBooks *db, Book *book);
void removeBook(DBBooks *db, Book *book);

int isBorrowed(Book *book); // Retourne le nombre de fois qu'il est emprunté


#endif //LABIBLIODEFRANCK_DBBOOKS_H
