//
// Created by Benjamin Lesieux on 05/05/2020.
//

#ifndef LABIBLIODEFRANCK_CLIENT_H
#define LABIBLIODEFRANCK_CLIENT_H

#include "book.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {

    char name[30];
    char surname[30];
    char home[100];
    char email[40];
    char job[30];
    int borrowed;
    char *books;

} Client;

Client* createClient();
void borrow(Book *book, Client *client);
void bringBack(Book *book, Client *client);



#endif //LABIBLIODEFRANCK_CLIENT_H