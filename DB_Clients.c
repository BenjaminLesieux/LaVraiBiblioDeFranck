//
// Created by Benjamin Lesieux on 05/05/2020.
//

#include "DB_Clients.h"

void addClientToDB(Client *client, DBClients *database) {

    if (isClientInDB(client, database) == TRUE) {
        printf("\n%s %s est déjà un de nos client !", client->name, client->surname);
        return;
    }

    Client *oldClients = database->clients;
    free(database->clients);
    database->clients = malloc(sizeof(Client) * (database->numClients + 1));
}