//
// Created by Benjamin Lesieux on 13/05/2020.
//

#ifndef LABIBLIODEFRANCK_DBCLIENTS_H
#define LABIBLIODEFRANCK_DBCLIENTS_H

#include "DBBooks.h"
#include "LinkedList.h"

typedef struct Client_type {
    char *name;
    char *surname;
    char *adress;
    char *email;
    char *job;
    Book *borrowed;
    int numBooks;

}Client;

typedef struct DBClients_type {
    Node *clients;
} DBClients;

#endif //LABIBLIODEFRANCK_DBCLIENTS_H
