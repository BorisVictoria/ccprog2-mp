// This file contains the functions associated with the exit of the program
#include <stdio.h>
#include <string.h>
#include "structures.h"

void writeUsers(struct user users[])
{
    FILE *userFile = fopen("Users.txt", "w");

    fclose(userFile);
}

void writeItems(struct item items[])
{
    FILE *itemFile = fopen("Items.txt", "w");

    fclose(itemFile);
}

void writeTransactions(struct transaction transactions[])
{
    FILE *transactionFile = fopen("Transactions.txt", "w");

    fclose(transactionFile);
}