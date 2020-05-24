//
// Created by Benjamin Lesieux on 21/05/2020.
//

#include "Menu.h"
#include "Date.h"

void welcome(DBClients *dbc, DBBooks *dbb) {

    int valid = 0;
    int onMenu = 1;
    int choice;

    do {
        printf("\n\n--------------- Bibliothèque de Franck -----------------"
               " \n1) Menu Bibliothécaire"
               " \n2) Afficher la liste des livres"
               " \n3) Afficher la liste des clients"
               " \n4) Rechercher un livre"
               " \n5) Voir livres empruntés"
               " \n6) Quitter"
               "\n\n Clients : %d                              Livres : %d"
               "\n Choix : ",
               dbc->numClients, dbb->numBooks);

        valid = scanf("%d", &choice);
        getchar();

        if (valid == 1) {
            switch(choice) {
                case 1:
                    bibliMenu(dbc, dbb);
                    break;
                case 2:
                    showBooks(dbb);
                    break;
                case 3:
                    showClients(dbc);
                    break;
                case 4:
                    searchMenu(dbb);
                    break;
                case 5:
                    showBorrowedBooks(dbc, dbb);
                    break;
                case 6:
                    onMenu = 0;
                    break;
                default:
                    break;
            }
        }

    } while (onMenu == 1 || valid == 0 || choice < 1 || choice > 6);
}

void clientMenu(DBClients *db, DBBooks *dbb) {
    int onMenu = 1;
    int valid = 0;
    int choice;

    do {
        printf("\n --------------- Menu Client -----------------"
               "\n  1) Ajouter un client "
               "\n  2) Retirer un client "
               "\n  3) Emprunter un livre "
               "\n  4) Rendre un livre "
               "\n  5) Quitter "
               "\n Votre choix : ");

        valid = scanf("%d", &choice);
        getchar();

        if (valid == 1) {
            switch(choice) {
                case 1:
                    addClient(db, readClient());
                    sortAlphaClients(db->clients); // SORT IN ALPHABETICAL ORDER
                    break;
                case 2:
                    removeClientMenu(db, dbb);
                    break;
                case 3:
                    borrowMenu(db, dbb);
                    break;
                case 4:
                    giveMenu(db, dbb);
                    break;
                case 5:
                    onMenu = 0;
                    break;
                default:
                    break;
            }
        }

    } while (onMenu == 1 || valid == 0 || choice < 1 || choice > 5);
}

void bibliMenu(DBClients *dbc, DBBooks *dbb) {
    int valid = 0;
    int onMenu = 1;
    int choice;

    do {
        printf("\n--------------- Bibliothèque de Franck -----------------"
               " \n1) Menu Client"
               " \n2) Menu Livres"
               " \n3) Quitter"
               " \nVotre choix : ");

        valid = scanf("%d", &choice);
        getchar();

        if (valid == 1) {
            switch(choice) {
                case 1:
                    clientMenu(dbc, dbb);
                    break;
                case 2:
                    bookMenu(dbb, dbc);
                    break;
                case 3:
                    onMenu = 0;
                    break;
                default:
                    break;
            }
        }

    } while (onMenu == 1 || valid == 0 || choice < 1 || choice > 3);
}

void removeClientMenu(DBClients *db, DBBooks *dbb) {
    int onMenu = 1;
    int valid = 0;
    int choice;
    int i;
    Client *c;

    do {
        printf("\n --------------- Retirer un client  -----------------");

        for (i = 0; i < db->numClients; i++) {
            c = get(db->clients, i);
            if (c->numBooks == 0)
                printf("\n %d - %s Supprimer %s %s (Aucun emprunt) %s ", i, RED, c->name, c->surname, WHITE);
            else
                printf("\n %d - Supprimer %s %s ", i, c->name, c->surname);
        }

        printf("\n %d - Quitter ", i);

        valid = scanf("%d", &choice);
        getchar();

        if (valid == 1 && choice > 0 && choice < db->numClients) {
            c = get(db->clients, choice);
            updateLogs(c, dbb);
            removeClient(db, c);
        }

        else if (valid == 1 && choice == i) {
            onMenu = 0;
        }

    } while (onMenu == 1 || valid == 0 || choice < 0 || choice > db->numClients);
}

void borrowMenu(DBClients *db, DBBooks *dbb) {
    int onMenu = 1;
    int valid = 0;
    int choice;
    int i;
    Client *c;
    Book *b;

    do {
        printf("\n --------------- Emprunt client  -----------------");

        for (i = 0; i < db->numClients; i++) {
            c = get(db->clients, i);
            printf("\n %d - Faire emprunter à %s %s ", i, c->name, c->surname);
        }

        printf("\n %d - Quitter "
               "\n Choix : ", i);

        valid = scanf("%d", &choice);
        getchar();

        if (valid == 1 && choice >= 0 && choice < db->numClients) {

            int sub_choice;
            int sub_valid;
            int valid_date;

            do {
                for (i = 0; i < dbb->numBooks; i++) {
                    b = get(dbb->books, i);
                    printf("\n%d - Emprunter %s {%s}", i, b->title, b->code);
                }

                printf("\n %d - Annuler"
                       "\n Choix : ", i);

                sub_valid = scanf("%d", &sub_choice);
                getchar();

                if (sub_valid == 1 && sub_choice >= 0 && sub_choice < dbb->numBooks) {
                    c = get(db->clients, choice);
                    b = get(dbb->books, sub_choice);

                    borrow(c, b);

                    for (int j = 0; j < 3; j++) {
                        if (c->dates[j]->day == 0) {
                            c->dates[j] = makeDate();
                            break;
                        }
                    }
                }

                else if (sub_valid == 1 && sub_choice == i) {
                     valid = 0;
                }

            } while (sub_valid == 0 || sub_choice < 0 || sub_choice > dbb->numBooks);
        }

        else if (valid == 1 && choice == i) {
            onMenu = 0;
        }

    } while (onMenu == 1 || valid == 0 || choice < 0 || choice > db->numClients);
}

void bookMenu(DBBooks *db, DBClients *dbc) {
    int onMenu = 1;
    int valid = 0;
    int choice;

    do {
        printf("\n --------------- Menu Livres  -----------------"
               "\n  1) Ajouter un livre "
               "\n  2) Retirer une série livre "
               "\n  3) Quitter "
               "\n Votre choix : ");

        valid = scanf("%d", &choice);
        getchar();

        if (valid == 1) {
            switch (choice) {
                case 1:
                    addBook(db, readBook(db));
                    sortAlphaBooks(db->books);
                    break;
                case 2:
                    removeBookMenu(db, dbc);
                    break;
                case 3:
                    onMenu = 0;
                    break;
                default:
                    break;
            }
        }

    } while (onMenu == 1 || valid == 0 || choice < 1 || choice > 3);
}

void removeBookMenu(DBBooks *db, DBClients *dbc) {
    int onMenu = 1;
    int valid = 0;
    int choice;
    int i;
    Book *b;

    do {
        printf("\n --------------- Retirer un livre  -----------------");

        for (i = 1; i < db->numBooks; i++) {
            b = get(db->books, i-1);
            if (b->disp == b->num)
                printf("\n %d - %s Supprimer %s (%s) (Aucun emprunt) %s", i, RED, b->title, b->code, WHITE);
            else
                printf("\n %d - Supprimer des exemplaires de %s (%s) ", i, b->title, b->code);
        }

        printf("\n %d - Quitter ", i);

        valid = scanf("%d", &choice);
        getchar();

        if (valid == 1 && choice > 0 && choice < db->numBooks) {

            Book *toDelete = get(db->books, choice-1);
            int value = 0;

            do {

                printf("\n Combien d'exemplaires (parmi %d) de %s souhaitez vous supprimer ? : ",
                        toDelete->disp, toDelete->title);
                valid = scanf("%d", &value);
            } while (valid == 0 || value  < 0 || value > toDelete->disp);

            if (choice == 1 && value == toDelete->num && value > 0)
                removeBook(db, toDelete, value-1);
            else
                removeBook(db, toDelete, value);

            Book *bk;

            for (Node *b = db->books; b != NULL; b = b->next) {

                bk = b->value;
                updateCode(db, dbc, bk);
            }
        }

        else if (valid == 1 && choice == i) {
            onMenu = 0;
        }

    } while (onMenu == 1 || valid == 0 || choice < 0 || choice > db->numBooks);
}

void searchMenu(DBBooks *db) {
    int onMenu = 1;
    int valid = 0;
    int choice;
    int subValid;
    int subChoice;
    char search[100];

    do {
        printf("\n --------------- Recherche  -----------------"
               "\n  1) Recherche par genre  "
               "\n  2) Rechercher par texte "
               "\n  3) Quitter "
               "\n Votre choix : ");

        valid = scanf("%d", &choice);
        getchar();

        if (valid == 1) {
            switch (choice) {
                case 1:

                    do {
                        printf("\n Quel est le genre du livre que vous cherchez ?"
                               "\n 1) Roman"
                               "\n 2) Policier"
                               "\n 3) Thriller"
                               "\n 4) Fantastique"
                               "\n Votre choix : ");

                        subValid = scanf("%d", &subChoice);
                        getchar();
                    } while (subValid == 0 || subChoice < 0 || subChoice > 4);

                    if (subChoice == 1) strcpy(search, "ROM");
                    else if (subChoice == 2) strcpy(search, "POL");
                    else if (subChoice == 3) strcpy(search, "THR");
                    else if (subChoice == 4) strcpy(search, "FAN");

                    searchBook(db, 1, search);

                    break;
                case 2:
                    printf("\n Entrez une chaine de caractère : ");
                    fgets(search, 100, stdin);
                    strtok(search, "\n");
                    searchBook(db, 2, search);
                    break;
                case 3:
                    onMenu = 0;
                    break;
                default:
                    break;
            }
        }

    } while (onMenu == 1 || valid == 0 || choice < 1 || choice > 3);
}

void giveMenu(DBClients *dbc, DBBooks *dbb) {
    int onMenu = 1;
    int valid = 0;
    int choice;
    int i;
    Client *c;
    Book *b;

    do {
        printf("\n --------------- Rendre client  -----------------");

        for (i = 0; i < dbc->numClients; i++) {
            c = get(dbc->clients, i);
            if (c->numBooks > 0)
                printf("\n %d - %s %s %s possède des livres %s", i, GREEN, c->name, c->surname, WHITE);
            else
                printf("\n %d - %s %s n'a pas de livres ", i, c->name, c->surname);
        }

        printf("\n %d - Quitter "
               "\n Choix : ", i);

        valid = scanf("%d", &choice);
        getchar();

        if (valid == 1 && choice >= 0 && choice < dbc->numClients) {
            c = get(dbc->clients, choice);
            int subValid;
            int subChoice;
            int j;
            int compare;
            Book *b;

            if (c->numBooks != 0) {
                do {
                    printf("\n Voici les livres empruntés par %s %s ", c->name, c->surname);

                    for (j = 0; j < c->numBooks; j++) {
                        b = byCode(dbb, c->borrowed[j]);
                        printf("\n %d - %s par %s [%s]", j+1, b->title, b->author, b->code);
                    }

                    printf("\n %d - Retour", j+1);
                    printf("\nVotre choix :");
                    subValid = scanf("%d", &subChoice);

                    if (subChoice >= 1 && subChoice <= c->numBooks && subValid == 1) {
                        b = byCode(dbb, c->borrowed[subChoice-1]);
                        give(c, b);
                        compare = compareDate(c->dates[subChoice-1]);

                        if (compare == 0) {
                            printf("\n %s Ce livre a été rendu en retard, %s %s prend 1 pénalité"
                                   "\n Pénalités (%d/3) %s", RED, c->name, c->surname, c->penalties, WHITE);
                            c->penalties++;

                            if (c->penalties > 3) {
                                printf("\n %s Le maximum de pénalités est atteint, le client a été supprimé "
                                       "%s", RED, WHITE);
                                updateLogs(c, dbb);
                                removeClient(dbc, c);
                            }
                        }

                        break;
                    }

                } while (subValid == 0 || subChoice < 1 || subChoice > (j+1));
            } else printf("\n %s Ce client  ne peut pas rendre de livres qu'il ne possède pas %s",
                    RED, WHITE);
        }
        else if (valid == 1 && choice == i) {
            onMenu = 0;
        }

    } while (onMenu == 1 || valid == 0 || choice < 0 || choice > dbc->numClients);
}
