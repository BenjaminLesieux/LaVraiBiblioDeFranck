#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "DB_Clients.h"
#include "Client.h"

int main() {

    DBClients *database = initDBC();
    database->clients = fillDBC();

    Client *name = (Client*) database->clients->value;

    printf("%s", name->name);
    return 0;
}