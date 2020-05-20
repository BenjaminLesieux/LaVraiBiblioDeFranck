//
// Created by Benjamin Lesieux on 13/05/2020.
//

#include "DBBooks.h"

Book *readBook() {
    Book *book = NULL;

    book = (Book*) malloc(sizeof(Book));

    book->title = (char*) malloc(sizeof(char) * 100);
    book->author = (char*) malloc(sizeof(char) * 100);
    book->code = (char*) malloc(sizeof(char) * 7);

    printf("\nVeuillez entrer le titre de votre libre : ");
    fgets(book->title, 100, stdin);
    printf("\nQuel est son auteur ? : ");
    fgets(book->author, 100, stdin);

    book->code = "ROM-111";
    int valid = 0;

    do {
        printf("\nCombien possédez-vous d'exemplaires de ce livre ?");
        valid = scanf("%d", &book->num);
        getchar();
    } while (valid == 1);

    book->disp = book->num;
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
    int numClients;

    int childs = xmlChildElementCount(root);

    printf("\n%d childs", childs);

    for (currentChild = xmlFirstElementChild(root); currentChild != NULL;
         currentChild = xmlNextElementSibling(currentChild)) {

        book = (Book*) malloc(sizeof(Book));


        for (xmlNodePtr content = xmlFirstElementChild(currentChild); content != NULL;
             content = xmlNextElementSibling(content)) {

            char *val = (char*) xmlNodeGetContent(content);

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
}
