//
// Created by Benjamin Lesieux on 13/05/2020.
//

#include "DBClients.h"
#include "DBBooks.h"

Client *readClient() {
    Client *client = (Client*) malloc(sizeof(Client));

    client->name = malloc(100 * sizeof(char));
    client->surname = malloc(100 * sizeof(char));
    client->adress = malloc(200 * sizeof(char));
    client->email = malloc(100 * sizeof(char));
    client->job = malloc(100 * sizeof(char));

    if (client == NULL) printf("\nErreur lors de la création d'un client.");

    printf("\nPrénom : ");
    fgets(client->name, 100, stdin);
    strtok(client->name, "\n");
    printf("\nNom : ");
    fgets(client->surname, 100, stdin);
    strtok(client->surname, "\n");
    printf("\nAdresse : ");
    fgets(client->adress, 200, stdin);
    strtok(client->adress, "\n");
    printf("\nEmail : ");
    fgets(client->email, 100, stdin);
    strtok(client->email, "\n");
    printf("\nJob : ");
    fgets(client->job, 150, stdin);
    strtok(client->job, "\n");

    client->borrowed = NULL;
    client->numBooks = 0;

    return client;
}

void addClient(DBClients *db, Client *client) {

    if (db->numClients == 0) {
        db->clients = createLinkedList(client);
        db->numClients++;
    }

    else {
        Node *nc = createNewNode(client);
        add(db->clients, nc);
        db->numClients++;
    }

    if (client == NULL) {
        printf("\nErreur client");
        exit(1);
    }
}

void updateXmlDB(DBClients *db) {
    Client *current;
    FILE *file = fopen("dbclients.xml", "w");

    if (file == NULL) {
        file = fopen("dbclients.xml", "c");
    }

    fprintf(file, "<clients>\n");

    for (int i = 0; i < db->numClients; i++) {
        current = get(db->clients, i);

        fprintf(file, "    <client id = '%d'>\n"
                      "        <name>%s</name>\n"
                      "        <surname>%s</surname>\n"
                      "        <adress>%s</adress>\n"
                      "        <email>%s</email>\n"
                      "        <job>%s</job>\n"
                      "    </client>\n", i, current->name, current->surname, current->adress, current->email,
                current->job);
    }

    fprintf(file, "</clients>");
    fclose(file);
}

void *getClients(DBClients *db) {

    xmlDocPtr doc = xmlParseFile("dbclients.xml");
    xmlNodePtr root = xmlDocGetRootElement(doc);
    xmlNodePtr currentChild = NULL;
    Client *client = NULL;
    int numClients;

    int childs = xmlChildElementCount(root);

    printf("\n%d childs", childs);

    for (currentChild = xmlFirstElementChild(root); currentChild != NULL;
        currentChild = xmlNextElementSibling(currentChild)) {

        client = (Client*) malloc(sizeof(Client));


        for (xmlNodePtr content = xmlFirstElementChild(currentChild); content != NULL;
            content = xmlNextElementSibling(content)) {

            char *val = (char*) xmlNodeGetContent(content);

            if (strcmp((char*)content->name, "name") == 0) {
                printf("\n Found a name");
                client->name = val;
            }

            else if (strcmp((char*)content->name, "surname") == 0) {
                printf("\n Found a surname");
                client->surname = val;
            }

            else if (strcmp((char*)content->name, "adress") == 0) {
                printf("\n Found an adress");
                client->adress = val;
            }

            else if (strcmp((char*)content->name, "email") == 0) {
                printf("\n Found a email");
                client->email = val;
            }

            else if (strcmp((char*)content->name, "job") == 0) {
                printf("\n Found a job");
                client->job = val;
            }
        }

        addClient(db, client);
    }
}


