#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "LinkedList.h"
#include <DBClients.h>

void afficher_noeud(xmlNodePtr noeud);
typedef void (*fct_parcours_t)(xmlNodePtr);
void parcours_prefixe(xmlNodePtr noeud, fct_parcours_t f);


int main() {

    /**
     * Récupération des clients de la database
     * */

    DBClients *db = (DBClients*) malloc(sizeof(DBClients));
    getClients(db);
    printf("\n%d", db->numClients);

    // Fin de récupération

    Client *cl = get(db->clients, 3); // Vérification de la bonne présence des clients

    updateXmlDB(db); // A la fin, toujours update le fichier xml

    return 0;
}

void afficher_noeud(xmlNodePtr noeud) {
    if (noeud->type == XML_ELEMENT_NODE) {
        xmlChar *chemin = xmlGetNodePath(noeud);
        if (noeud->children != NULL && noeud->children->type == XML_TEXT_NODE) {
            xmlChar *contenu = xmlNodeGetContent(noeud);
            printf("%s -> %s\n", chemin, contenu);
            xmlFree(contenu);
        } else {
            printf("%s\n", chemin);
        }
        xmlFree(chemin);
    }
}

void parcours_prefixe(xmlNodePtr noeud, fct_parcours_t f) {
    xmlNodePtr n;

    for (n = noeud; n != NULL; n = n->next) {
        f(n);
        if ((n->type == XML_ELEMENT_NODE) && (n->children != NULL)) {
            parcours_prefixe(n->children, f);
        }
    }
}

