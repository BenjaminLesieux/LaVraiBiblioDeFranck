//
// Created by Benjamin Lesieux on 05/05/2020.
//

#ifndef LABIBLIODEFRANCK_DB_CLIENTS_H
#define LABIBLIODEFRANCK_DB_CLIENTS_H

#include "Client.h"
#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    Node *clients;
    unsigned int numClients;
} DBClients;


void addClientToDB(Client *client, DBClients *database);
int isClientInDB(Client *client, DBClients *database);
void removeClientFromDB(Client *client, DBClients *database);
void sortByName(DBClients *database);
void sortByBooksBorrowed(DBClients *database);

#endif //LABIBLIODEFRANCK_DB_CLIENTS_H