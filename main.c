#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "LinkedList.h"
#include <DBClients.h>
#include <time.h>

void afficher_noeud(xmlNodePtr noeud);
typedef void (*fct_parcours_t)(xmlNodePtr);
void parcours_prefixe(xmlNodePtr noeud, fct_parcours_t f);


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


    sortAlphaClients(db->clients);


    /** Code projet */



    /** Fin code projet */

    updateXmlDB(db); // A la fin, toujours update le fichier xml
    updateXmlDBBooks(dbBooks);

    return 0;
}



