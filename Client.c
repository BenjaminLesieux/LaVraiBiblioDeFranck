//
// Created by Benjamin Lesieux on 05/05/2020.
//

#include "Client.h"

Node* createClient(DBClients *db) { // Créer un client et le rentrer dans la base de donnée
    Client *client = NULL;
    client = malloc(sizeof(Client));

    if (client == NULL) {
        printf("\nErreur d'allocation mémoire...");
        return NULL;
    }

    printf("\nEntrez le prénom du nouveau client :");
    fgets(client->name, 100, stdin);
    printf("\nEntrez son nom de famille : ");
    fgets(client->surname, 100, stdin);
    printf("\nQuelle est son adresse ? ");
    fgets(client->home, 100, stdin);
    printf("\nEmail : ");
    fgets(client->email, 50, stdin);
    printf("\nEmploi : ");
    fgets(client->job, 50, stdin);

    client->books = NULL;
    client->borrowed = 0;

    Node *node = createNewNode(client);

    if (find(db->clients, client) == -1) { // Il faudra changer de fonction
        add(db->clients, node);
    }

    else {
        printf("\nVous avez entré un client qui est déjà dans la db ");
        free(client);
    }

    return node;
}