// This file contains the functions associated with the startup of the program
#include <stdio.h>
#include <string.h>
#include "structures.h"

void readUsers(struct user users[])
{
    FILE *userFile = fopen("Users.txt", "r");

    fclose(userFile);
}

void readItems(struct item items[])
{
    FILE *itemFile = fopen("Items.txt", "r");

    fclose(itemFile);
}

void readTransactions(struct transaction transactions[])
{
    FILE *transactionFile = fopen("Transactions.txt", "r");

    fclose(transactionFile);
}