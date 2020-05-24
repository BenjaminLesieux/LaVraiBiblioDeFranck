#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "LinkedList.h"
#include "DBClients.h"
#include "DBBooks.h"
#include <time.h>
#include "Menu.h"


int main() {

    /**
     * Récupération des clients de la database
     * */

    DBClients *db = (DBClients*) malloc(sizeof(DBClients));
    DBBooks  *dbBooks = (DBBooks*) malloc(sizeof(DBBooks));
    getClients(db);
    getBooks(dbBooks);


    //Client *new = readClient();
    //addClient(db, new);

    welcome(db, dbBooks);

    time_t t = time(NULL);

    // il peut y avoir moins coûteux en énergie

    updateXmlDB(db); // UPDATE CLIENTS
    updateXmlDBBooks(dbBooks); // UPDATE BOOKS

    freeList(db->clients);
    freeList(dbBooks->books);
    free(db);
    free(dbBooks);

    printf("\nSauvegarde de la database en %ld secondes ", time(NULL) - t);

    return 0;
}





