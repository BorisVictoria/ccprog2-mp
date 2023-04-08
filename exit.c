// This file contains the functions associated with the exit of the program
#include <stdio.h>
#include <string.h>
#include "structures.h"

void writeUsers(struct user users[], int userCount)
{
    FILE *userFile = fopen("Users.txt", "w");

    for (int i = 0; i < userCount; i++)
    {
        fprintf(userFile, "%ld %s\n", users[i].userid, users[i].password);
        fprintf(userFile, "%s\n", users[i].name);
        fprintf(userFile, "%s\n", users[i].address);
        fprintf(userFile, "%ld\n", users[i].contactnumber);
        fprintf(userFile, "\n");
    }

    fclose(userFile);
}

void writeItems(struct item items[], int itemCount)
{
    FILE *itemFile = fopen("Items.txt", "w");

    for (int i = 0; i < itemCount; i++)
    {
        fprintf(itemFile, "%ld %ld\n", items[i].productid, items[i].sellerid);
        fprintf(itemFile, "%s\n", items[i].name);
        fprintf(itemFile, "%s\n", items[i].category);
        fprintf(itemFile, "%s\n", items[i].description);
        fprintf(itemFile, "%ld %lf\n", items[i].quantity, items[i].price);
        fprintf(itemFile, "\n");
    }

    fclose(itemFile);
}

void writeCart(struct item items[], int itemCount, long userid)
{
    char fileName[32];
    sprintf(fileName, "%ld.txt", userid);

    FILE *itemFile = fopen(fileName, "w");

    for (int i = 0; i < itemCount; i++)
    {
        fprintf(itemFile, "%ld %ld\n", items[i].productid, items[i].sellerid);
        fprintf(itemFile, "%s\n", items[i].name);
        fprintf(itemFile, "%s\n", items[i].category);
        fprintf(itemFile, "%s\n", items[i].description);
        fprintf(itemFile, "%ld %lf\n", items[i].quantity, items[i].price);
        fprintf(itemFile, "\n");
    }

    fclose(itemFile);

}

void writeTransactions(struct transaction transactions[], int transactionCount)
{
    FILE *transactionFile = fopen("Transactions.txt", "a");

    for (int i = 0; i < transactionCount; i++)
    {
        fprintf(transactionFile, "%ld %ld %ld %ld %ld\n", transactions[i].buyerid, transactions[i].sellerid, transactions[i].month, transactions[i].day, transactions[i].year);
        fprintf(transactionFile, "%ld\n", transactions[i].buyerid);
        fprintf(transactionFile, "%lf\n", transactions[i].total);
    }

    fclose(transactionFile);
}