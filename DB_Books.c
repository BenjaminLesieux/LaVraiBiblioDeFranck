//
// Created by Benjamin Lesieux on 05/05/2020.
//

#include "DB_Books.h"


void addBookToDB(Book *book, DBBooks *db) {
    Node *newBook = createNewNode(book);

    if (find(db->books, newBook->value) == -1) add(db->books, newBook);
    else printf("\nCe livre est déjà dans la base de donnée");
}

void removeBookFromDB(Book *book, DBBooks *db) {

    int index = find(db->books, book);
    Node *nodeBook = getFrom(db->books, book);

    removeAt(&db->books, index);
    free(nodeBook);
}