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
#include "Date.h"

typedef struct Client_type {
    char *name;
    char *surname;
    char *adress;
    char *email;
    char *job;
    char **borrowed;
    Date **dates;
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

void sortNum(DBClients *db);

void showClients(DBClients *db);

int isLate(Client *client);
void printDB(DBClients *db);
void updateXmlDB(DBClients *db);
void *getClients(DBClients *db);
void sortAlphaClients(Node *head);
void showBorrowedBooks(DBClients *dbc, DBBooks *dbb);
void updateCode(DBBooks *db, DBClients  *dbc, Book *book);

#endif //LABIBLIODEFRANCK_DBCLIENTS_H
