//
// Created by Benjamin Lesieux on 21/05/2020.
//

#ifndef LABIBLIODEFRANCK_MENU_H
#define LABIBLIODEFRANCK_MENU_H

#endif //LABIBLIODEFRANCK_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "DBBooks.h"
#include "DBClients.h"
#include "LinkedList.h"

void welcome(DBClients *dbc, DBBooks *dbb);

void borrowMenu(DBClients *db, DBBooks *dbb);

void clientMenu(DBClients *db, DBBooks *dbb);

void removeClientMenu(DBClients *db);

void removeBookMenu(DBBooks *db, DBClients *dbc);

void bibliMenu(DBClients *dbc, DBBooks *dbb);

void bookMenu(DBBooks *db, DBClients *dbc);

void searchMenu(DBBooks *DB);

void giveMenu(DBClients *dbc, DBBooks *dbb);