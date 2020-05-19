//
// Created by Benjamin Lesieux on 13/05/2020.
//

#ifndef LABIBLIODEFRANCK_DBCLIENTS_H
#define LABIBLIODEFRANCK_DBCLIENTS_H

#include "DBBooks.h"
#include "LinkedList.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlwriter.h>
#include <string.h>

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
    int numClients;
} DBClients;

/** Fonctions clients */
Client *readClient();
void addClient(DBClients *db, Client *client);
void removeClient(DBClients *db, Client *client);
void borrow(Client *client, Book *book);
void give(Client *client, Book *book);

void sortAlph(DBClients *db);
void sortNum(DBClients *db);

int isLate(Client *client);
void printDB(DBClients *db);

void updateXmlDB(DBClients *db);
void *getClients(DBClients *db);

#endif //LABIBLIODEFRANCK_DBCLIENTS_H
