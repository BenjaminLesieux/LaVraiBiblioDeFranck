//
// Created by Benjamin Lesieux on 13/05/2020.
//

#ifndef LABIBLIODEFRANCK_DBBOOKS_H
#define LABIBLIODEFRANCK_DBBOOKS_H

typedef struct Book_type {
    char *title;
    char *author;
    char code[7];
    int num;
    int disp;
} Book;

#endif //LABIBLIODEFRANCK_DBBOOKS_H
