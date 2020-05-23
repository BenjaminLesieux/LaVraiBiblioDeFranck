//
// Created by Benjamin Lesieux on 13/05/2020.
//

#include "DBClients.h"
#include "DBBooks.h"

Client *readClient() {
    Client *client = (Client*) malloc(sizeof(Client));
    Date **dates = (Date**) malloc(sizeof(Date*));

    for (int j = 0; j < 3; j++) {
        dates[j] = (Date*) malloc(sizeof(Date));
        dates[j]->day = 0;
        dates[j]->month = 0;
        dates[j]->year = 0;
    }

    client->name = malloc(100 * sizeof(char));
    client->surname = malloc(100 * sizeof(char));
    client->adress = malloc(200 * sizeof(char));
    client->email = malloc(100 * sizeof(char));
    client->job = malloc(100 * sizeof(char));

    char **borrowed = (char**) malloc(3 * sizeof(char*));

    for (int i = 0; i < client->numBooks; i++) {
        borrowed[i] = (char*) malloc(7 * sizeof(char));
    }

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

    client->borrowed = borrowed;
    client->borrowed[0] = "AUCUNLI";
    client->borrowed[1] = "AUCUNLI";
    client->borrowed[2] = "AUCUNLI";

    client->dates = dates;

    client->numBooks = 0;

    return client;
}

void addClient(DBClients *db, Client *client) {

    Client *verif;


    if (client == NULL) {
        printf("\nErreur client");
        exit(1);
    }

    if (db->numClients == 0) {
        db->clients = createLinkedList(client);
        db->numClients++;
    }

    else {
        Node *nc = createNewNode(client);
        add(db->clients, nc);
        db->numClients++;
    }
}

void removeClient(DBClients *db, Client *client) {
    Node *head = db->clients;
    Client *c;


    for (int i = 0; i < db->numClients; i++) {
        c = get(head, i);

        if (c != NULL && c == client) {
            db->numClients--;
            removeAt(&head, i);
            free(client->name);
            free(client->surname);
            free(client->adress);
            free(client->email);
            free(client->job);
            free(client->borrowed);
            free(client->dates);
            free(client);
        }
    }
}

void borrow(Client *client, Book *book) {

    if (client->numBooks < 3) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(client->borrowed[i], "AUCUNLI") == 0) {
                client->borrowed[i] = book->code;
                client->numBooks++;
                book->disp--;
                break;
            }
        }
    }

    else {
        printf("\nCe client a déjà atteint son quota maximum de 3 livres"
               "\nVous pouvez cependant lui faire rendre un livre pour pouvoir en prêter ");
    }
}

void give(Client *client, Book *book) {

    for (int i = 0; i < 3; i++) {
        if (strcmp(client->borrowed[i], book->code) == 0) {
            printf("\nOK");

            if (i < 2) {
                client->borrowed[i] = client->borrowed[i+1];
                client->dates[i]->day = client->dates[i+1]->day;
                client->dates[i]->month = client->dates[i+1]->month;
                client->dates[i]->year = client->dates[i+1]->year;
            }

            else {
                client->borrowed[i] = "AUCUNLI";
                client->dates[i]->day = 0;
                client->dates[i]->month = 0;
                client->dates[i]->year = 0;
            }
            book->disp++;
            client->numBooks--;
        }
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
                      "        <emprunts>\n"
                      "            <emprunt date = '%d/%d/%d'>%s</emprunt>\n"
                      "            <emprunt date = '%d/%d/%d'>%s</emprunt>\n"
                      "            <emprunt date = '%d/%d/%d'>%s</emprunt>\n"
                      "        </emprunts>\n"
                      "    </client>\n", i, current->name, current->surname, current->adress, current->email,
                current->job, current->dates[0]->day, current->dates[0]->month, current->dates[0]->year,
                current->borrowed[0], current->dates[1]->day, current->dates[1]->month, current->dates[1]->year,
                current->borrowed[1],current->dates[2]->day, current->dates[2]->month, current->dates[2]->year,
                current->borrowed[2]);
    }

    fprintf(file, "</clients>");
    fclose(file);
}

void *getClients(DBClients *db) {

    xmlDocPtr doc = xmlParseFile("dbclients.xml");
    xmlNodePtr root = xmlDocGetRootElement(doc);
    xmlNodePtr currentChild = NULL;
    Client *client = NULL;
    char *val;
    int numClients;
    char **borrowed;
    char *br;
    char *attribute;
    Date **dates;
    int i = 0;

    int childs = (int) xmlChildElementCount(root);

    printf("\n%d childs", childs);

    for (currentChild = xmlFirstElementChild(root); currentChild != NULL;
        currentChild = xmlNextElementSibling(currentChild)) {

        client = (Client*) malloc(sizeof(Client));
        borrowed  = (char**) malloc(3 * sizeof(char*));
        dates = (Date**) malloc(3 * sizeof(Date*));
        client->numBooks = 0;
        i = 0;

        for (xmlNodePtr content = xmlFirstElementChild(currentChild); content != NULL;
            content = xmlNextElementSibling(content)) {

            val = (char*) xmlNodeGetContent(content);

            for (int j = 0; j < 3; j++) {
                borrowed[j] = (char*) malloc(7 * sizeof(char));
                dates[j] = (Date*) malloc(sizeof(Date));
            }

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

            else if (strcmp((char*)content->name, "emprunts") == 0) {
                for (xmlNodePtr book = xmlFirstElementChild(content); book != NULL;
                    book = xmlNextElementSibling(book)) {

                    br = (char*) xmlNodeGetContent(book);
                    attribute = (char*) xmlGetProp(book, "date");

                    printf("\n%s", br);

                    if (strcmp((char*)book->name, "emprunt") == 0) {
                        if (i < 3) {
                            borrowed[i] = br;
                            dates[i] = readFromString(attribute);

                            if (strcmp((char*)br, "AUCUNLI") != 0) {
                                client->numBooks++;
                            }
                        }
                    }

                    i++;
                }

                client->borrowed = borrowed;
                client->dates = dates;
            }
        }

        addClient(db, client);
    }

    free(val);
}

void sortAlphaClients(Node *head) {

    for (Node *n = head; n->next != NULL; n = n->next) {
        for (Node *next = head->next; next->next != NULL; next = next->next) {
            Client *c = n->value;
            Client *cn = n->next->value;

            if (strcmp(c->name, cn->name) > 0) {
                swap(n, n->next);
            }

            sortAlphaClients(next);
        }
    }
}

void showClients(DBClients *db) {
    Node *head = db->clients;
    Client *c = NULL;

    if (head == NULL) {
        printf("\nDatabase empty");
        exit(1);
    }

    for (Node *current = head; current != NULL; current = current->next) {
        c = current->value;

        printf("\n%s %s, domicilié à %s, contact:  %s, travail : %s "
               "{%s, %s, %s} emprunte %d livres",
                   c->name, c->surname, c->adress, c->email, c->job,
                   c->borrowed[0], c->borrowed[1], c->borrowed[2], c->numBooks);
        showDate(c->dates);
    }
}

void showBorrowedBooks(DBClients *dbc, DBBooks *dbb) {
    Node *headc = dbc->clients;
    Node *headb = dbb->books;
    Client *c;
    Book *b;

    for (Node *current = headc; current != NULL; current = current->next) {
        for (Node *currentBook = headb; currentBook != NULL; currentBook = currentBook->next) {
            c = current->value;
            b = currentBook->value;

            for (int i = 0; i < 3; i++) {
                if (strcmp(c->borrowed[i], b->code) == 0) {
                    printf("\n %s est emprunté par %s %s", b->title, c->name, c->surname);
                    break;
                }
            }
        }
    }
}

void updateCode(DBBooks *db, DBClients *dbc, Book *book) {
    Book *current;
    Client *c;
    Node *head = dbc->clients;
    int val = -1;
    char *sval = (char*) malloc(sizeof(char) * 3);
    char *style = (char*) malloc(sizeof(char) * 3);
    int hasToChange;
    style = book->code;

    style[3] = '\0';

    printf("\n%s", style);

    for (int i = 0; i < db->numBooks && current != book; i++) {
        current = get(db->books, i);
        if (strstr(current->code, book->code)) {
            val++;
        }
    }

    if (val < 10 && val >= 0) {
        sprintf(sval, "%s-00%d", style, val);
    }

    else if (val < 100 && val > 10 && val > 0) {
        sprintf(sval, "%s-0%d", style, val);
    }

    else if (val > 100){
        sprintf(sval, "%s-%d", style, val);
    }

    for (Node *node = head; node != NULL; node = node->next) {
        c = node->value;

        for (int i = 0; i < 3; i++) {
            if (strcmp(c->borrowed[i], book->code) == 0) c->borrowed[i] = sval;
        }
    }

    book->code = sval;
}


