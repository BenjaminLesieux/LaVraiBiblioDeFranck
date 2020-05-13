//
// Created by Benjamin Lesieux on 05/05/2020.
//

#ifndef LABIBLIODEFRANCK_CLIENT_H
#define LABIBLIODEFRANCK_CLIENT_H

#include "book.h"
#include <stdlib.h>
#include <stdio.h>
#include "DB_Clients.h"
#include "LinkedList.h"

typedef struct {

    char *name;
    char *surname;
    char *home;
    char *email;
    char *job;
    int borrowed;
    char *books;

} Client;

Node* createClient(DB_Clients *db);
void borrow(Book *book, Client *client);
void bringBack(Book *book, Client *client);



#endif //LABIBLIODEFRANCK_CLIENT_H