//
// Created by Benjamin Lesieux on 05/05/2020.
//

#include "Client.h"

Client* createClient() { // Créer un client et le rentrer dans la base de donnée
    Client *client = NULL;
    client = malloc(sizeof(Client));
    FILE *db = fopen("db_clients.txt", "a+");

    if (db == NULL) db = fopen("db_clients.txt", "c");

    if (client == NULL) {
        printf("\nErreur d'allocation mémoire...");
        return NULL;
    }

    printf("\nEntrez le prénom et le nom du nouveau client (prénom nom) :");
    scanf("%s %s", client->name, client->surname);
    printf("\nQuelle est son adresse ? (entre [])");
    fgets(client->home, 50, stdin);
    printf("\nEmail : ");
    scanf(" %s", client->email);
    printf("\nEmploi : (entre []) ");
    scanf(" %s", client->job);

    fprintf(db, "%s %s %s %s %s \n"
            ,client->name, client->surname, client->home, client->email, client->job);

    client->books = NULL;
    client->borrowed = 0;
}