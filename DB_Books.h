//
// Created by Benjamin Lesieux on 05/05/2020.
//

#ifndef LABIBLIODEFRANCK_DB_BOOKS_H
#define LABIBLIODEFRANCK_DB_BOOKS_H

#include "Book.h"

typedef struct {
    Book *books;
    char file[30];
} DBBooks;

void addBookToDB(Book *book, DBBooks *database);
void removeBookFromDB(Book *book, DBBooks *database);

#endif //LABIBLIODEFRANCK_DB_BOOKS_H