//
// Created by Benjamin Lesieux on 13/05/2020.
//

#include "DBBooks.h"

Book *readBook(DBBooks *db) {
    Book *book = NULL;

    book = (Book*) malloc(sizeof(Book));

    if (book == NULL) printf("Erreur mémoire");

    book->title = (char*) malloc(sizeof(char) * 100);
    book->author = (char*) malloc(sizeof(char) * 100);
    book->code = (char*) malloc(sizeof(char) * 7);

    printf("\nVeuillez entrer le titre de votre libre : ");
    fgets(book->title, 100, stdin);
    strtok(book->title, "\n");
    printf("\nQuel est son auteur ? : ");
    fgets(book->author, 100, stdin);
    strtok(book->author, "\n");

    int valid = 0;

    getStyle(db, book->code);

    book->num = 10;
    book->disp = book->num;

    return book;
}

Book *byCode(DBBooks *db, char* code) {

    Book *b = NULL;

    for (Node *current = db->books; current != NULL; current = current->next) {
        b = current->value;

        if(strcmp(b->code, code) == 0) {
            printf("\n Found %s", b->title);
            return b;
        }
    }

    return NULL;
}

void *getStyle(DBBooks *db, char* value) {
    int style;
    int valid;

    do {
        printf("\nQuel est le style de votre roman : ");
        printf("\n1 - Roman");
        printf("\n2 - Policier");
        printf("\n3 - Thriller");
        printf("\n4 - Fantastique");
        printf("\nVotre choix : ");
        valid = scanf("%d", &style);
        getchar();
    } while(valid == 0 || style < 1 || style > 4);

    if (style == 1) sprintf(value, "ROM-");
    else if (style == 2) sprintf(value, "POL-");
    else if(style == 3) sprintf(value, "THR-");
    else if (style == 4) sprintf(value, "FAN-");

    Book *current;
    int val = 000;
    char *sval = (char*) malloc(sizeof(char) * 3);

    for (int i = 0; i < db->numBooks; i++) {
        current = get(db->books, i);
        if (strstr(current->code, value)) {
            val++;
            printf("%d", val);
        }
    }

    if (val < 10 && val >= 0) {
        sprintf(sval, "00%d", val);
    }

    else if (val < 100 && val > 10 && val > 0) {
        sprintf(sval, "0%d", val);
    }

    else if (val > 100){
        sprintf(sval, "%d", val);
    }

    strcat(value, sval);
}

void addBook(DBBooks *db, Book *book) {
    if (book == NULL) {
        printf("\nAjout d'un livre inexistant");
        exit(1);
    }

    if (db->numBooks == 0) {
        db->books = createLinkedList(book);
        db->numBooks++;

    }

    else {
        Node *b = createNewNode(book);
        add(db->books, b);
        db->numBooks++;
    }
}

void removeBook(DBBooks *db, Book *toDelete, int howMany) {
    Node *head = db->books;
    Book *b;

    for (int i = 0; i < db->numBooks; i++) {
        b = get(head, i);

        if (b != NULL && b == toDelete) {
            if (howMany >= b->disp) {
                b->num = b->num - b->disp;
                b->disp = 0;
            }

            else {
                printf("\nThat's where i go");
                b->num = b->num - howMany;
                b->disp = b->disp - howMany;
            }

            if (b->num == 0 && b->disp == 0) {
                db->numBooks--;
                removeAt(&head, i);
                free(toDelete);
            }
        }
    }
}

void updateXmlDBBooks(DBBooks *db) {

    Book *current;
    FILE *file = fopen("dbbooks.xml", "w");

    if (file == NULL) fopen("dbbooks.xml", "c");

    fprintf(file, "<books>\n");

    for(int i = 0; i < db->numBooks; i++) {
        current = get(db->books, i);

        fprintf(file, "    <book id = '%d'>\n"
                      "        <title>%s</title>\n"
                      "        <author>%s</author>\n"
                      "        <code>%s</code>\n"
                      "        <number>%d</number>\n"
                      "        <disp>%d</disp>\n"
                      "   </book>\n", i, current->title, current->author, current->code, current->num, current->disp);
    }

    fprintf(file, "</books>");
    fclose(file);
}

void *getBooks(DBBooks *db) {
    xmlDocPtr doc = xmlParseFile("dbbooks.xml");
    xmlNodePtr root = xmlDocGetRootElement(doc);
    xmlNodePtr currentChild = NULL;
    Book *book = NULL;
    char *val;
    int numClients;

    int childs = xmlChildElementCount(root);

    printf("\n%d childs", childs);

    for (currentChild = xmlFirstElementChild(root); currentChild != NULL;
         currentChild = xmlNextElementSibling(currentChild)) {

        book = (Book*) malloc(sizeof(Book));


        for (xmlNodePtr content = xmlFirstElementChild(currentChild); content != NULL;
             content = xmlNextElementSibling(content)) {

            val = (char*) xmlNodeGetContent(content);

            if (strcmp((char*)content->name, "title") == 0) {
                printf("\n Found a title");
                book->title = val;
            }

            else if (strcmp((char*)content->name, "author") == 0) {
                printf("\n Found a author");
                book->author = val;
            }

            else if (strcmp((char*)content->name, "code") == 0) {
                printf("\n Found a code");
                book->code = val;
            }

            else if (strcmp((char*)content->name, "number") == 0) {
                printf("\n Found a number");
                book->num = atoi(val);
            }

            else if (strcmp((char*)content->name, "disp") == 0) {
                printf("\n Found a disp");
                book->disp = atoi(val);
            }

        }

        addBook(db, book);
    }

    free(val);
}

void sortAlphaBooks(Node *head) {

    for (Node *n = head; n->next != NULL; n = n->next) {
        for (Node *next = head->next; next->next != NULL; next = next->next) {
            Book *b = n->value;
            Book *bn = n->next->value;

            if (strcmp(b->title, bn->title) > 0) {
                swap(n, n->next);
            }

            sortAlphaBooks(next);
        }
    }
}

void showBooks(DBBooks *db) {

    Node *head = db->books;
    Book *b = NULL;

    if (head == NULL) {
        printf("\nDatabase empty");
        exit(1);
    }

    for (Node *current = head; current != NULL; current = current->next) {
        b = current->value;
        printf("\n%s par %s (%s) avec %d exemplaires dont %d sont empruntés",
               b->title, b->author, b->code, b->num, b->num - b->disp);
    }

    //free(b);
    //free(head);
}

void searchBook(DBBooks *db, int criteria, char *string) {
    Node *head = db->books;
    Book *value;

    switch (criteria) {
        case 1: // Par style
            printf("\n Votre recherche par genre (%s) a donné : ", string);
            for (Node *current = head; current != NULL; current = current->next) {
                value = current->value;

                if (strstr(value->code, string)) {
                    printf("\n %s", value->title);
                }
            }
            break;
        case 2:
            printf("\n Votre recherche par texte (%s) a donné : ", string);
            for (Node *current = head; current != NULL; current = current->next) {
                value = current->value;

                if (strlen(value->title) > strlen(string)) {
                    if (strstr(value->title, string)) printf("\n %s", value->title);
                } else {
                    if (strstr(string, value->title)) printf("\n %s", value->title);
                }
            }
            break;
        default:
            printf("\n Entrée non valide");
            break;
    }
}
