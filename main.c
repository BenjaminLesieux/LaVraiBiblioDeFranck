#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "LinkedList.h"

int main() {

    xmlDocPtr doc = xmlParseFile("dbbooks.xml");
    xmlNodePtr node;

    xmlKeepBlanksDefault(0);

    node = xmlDocGetRootElement(doc);

    return 0;
}
