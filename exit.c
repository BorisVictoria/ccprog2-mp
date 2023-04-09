// This file contains the functions associated with the exit of the program
#include <stdio.h>
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

void writeTransactionItems(int transactionItems)
{
    FILE *transactionItemFile = fopen("TransactionOffsets.txt", "a");

    fprintf(transactionItemFile, "%d\n", transactionItems);
    fprintf(transactionItemFile, "\n");

    fclose(transactionItemFile);

}

void writeTransactions(struct transaction transactions[], int totalTransactionItemCount)
{
    FILE *transactionFile = fopen("Transactions.txt", "a");

    int transactionItemCount;
    int totalTransactions = totalTransactionItemCount / 5;

    if (totalTransactions == 0)
    {
        totalTransactions = 1;
        transactionItemCount = totalTransactionItemCount % 5;
    }
    else if (totalTransactions == 1)
    {
        if (totalTransactionItemCount % 5 == 0)
        {
            transactionItemCount = 5;
        }
        else
        {
            totalTransactions = 2;
            transactionItemCount = 5;
        }
    }
    else
    {
        totalTransactions = 2;
        transactionItemCount = 5;
    }


    for (int i = 0; i < totalTransactions; i++)
    {
        if (i == 1)
            if (totalTransactionItemCount % 5 != 0)
                transactionItemCount = totalTransactionItemCount % 5;
        fprintf(transactionFile, "%ld %ld %ld %ld %ld %lf\n", transactions[i].buyerid, transactions[i].sellerid, transactions[i].month, transactions[i].day, transactions[i].year, transactions[i].total);
        for (int j = 0; j < transactionItemCount; j++)
        {
            fprintf(transactionFile, "%ld %ld\n", transactions[i].items[j].productid, transactions[i].items[j].sellerid);
            fprintf(transactionFile, "%s\n", transactions[i].items[j].name);
            fprintf(transactionFile, "%s\n", transactions[i].items[j].category);
            fprintf(transactionFile, "%s\n", transactions[i].items[j].description);
            fprintf(transactionFile, "%ld %lf\n", transactions[i].items[j].quantity, transactions[i].items[j].price);
            fprintf(transactionFile, "\n");
        }
    }

    fclose(transactionFile);
}