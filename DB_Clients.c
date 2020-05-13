//
// Created by Benjamin Lesieux on 05/05/2020.
//

#include "DB_Clients.h"

void sortByName(DBClients *db) {
    Node *list = db->clients;
    unsigned int size = db->numClients;
}

DBClients *initDBC() {
    DBClients *db = NULL;
    db = (DBClients*) malloc(sizeof(DBClients));

    if(db == NULL) printf("\nErreur d'allocation de la DB Client");

    return db;
}

Node *fillDB() {

    char *line = NULL;
    FILE *db = fopen("db_clients.txt", "r");

    if (db == NULL) db = fopen("db_clients.txt", "c");
    int i = 0;

    Client *current = NULL;
    current = (Client*) malloc(sizeof(Client));

    while (fgets(line, 100, db) != NULL) {
        if (line == "---") {
            current = (Client*) malloc(sizeof(Client));
            i = 0;
        }

        switch(i) {
            case 0:
                current->name = line;
                break;
            case 1:
                current->surname = line;
                break;
            case 2:
                current->home = line;
                break;
            case 3:
                current->email = line;
                break;
            case 4:
                current->job = line;
                break;
        }

        i++;
    }
}


