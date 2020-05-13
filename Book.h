//
// Created by Benjamin Lesieux on 05/05/2020.
//

#ifndef LABIBLIODEFRANCK_BOOK_H
#define LABIBLIODEFRANCK_BOOK_H
#define TRUE 0
#define FALSE 1

typedef struct {
    char *title;
    char *author;
    char *code;
    int stock;
    int availableStock;
} Book;

#endif //LABIBLIODEFRANCK_BOOK_H