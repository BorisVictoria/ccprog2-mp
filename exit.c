// This file contains the functions associated with the exit of the program
#include <stdio.h>
#include "structures.h"

void writeUsers(struct user users[], int userCount)
{
    FILE *userFile = fopen("Users.txt", "w");

    for (int i = 0; i < userCount; i++) // write information of user to file
    {
        fprintf(userFile, "%ld %s\n", users[i].userid, users[i].password);
        fprintf(userFile, "%s\n", users[i].name);
        fprintf(userFile, "%s\n", users[i].address);
        fprintf(userFile, "%ld\n", users[i].contactnumber);
        fprintf(userFile, "\n");
    }

    fclose(userFile); // close file
}

void writeItems(struct item items[], int itemCount)
{
    FILE *itemFile = fopen("Items.txt", "w");

    for (int i = 0; i < itemCount; i++) // write information of items to file
    {
        fprintf(itemFile, "%ld %ld\n", items[i].productid, items[i].sellerid);
        fprintf(itemFile, "%s\n", items[i].name);
        fprintf(itemFile, "%s\n", items[i].category);
        fprintf(itemFile, "%s\n", items[i].description);
        fprintf(itemFile, "%ld %lf\n", items[i].quantity, items[i].price);
        fprintf(itemFile, "\n");
    }

    fclose(itemFile); // close file
}

void writeCart(struct item items[], int itemCount, long userid)
{
    char fileName[32]; // item file name will be userid
    sprintf(fileName, "%ld.txt", userid);

    FILE *itemFile = fopen(fileName, "w");

    for (int i = 0; i < itemCount; i++) // write information of cart to file
    {
        fprintf(itemFile, "%ld %ld\n", items[i].productid, items[i].sellerid);
        fprintf(itemFile, "%s\n", items[i].name);
        fprintf(itemFile, "%s\n", items[i].category);
        fprintf(itemFile, "%s\n", items[i].description);
        fprintf(itemFile, "%ld %lf\n", items[i].quantity, items[i].price);
        fprintf(itemFile, "\n");
    }

    fclose(itemFile); // close file

}

void writeTransactionItems(int transactionItems) // write transaction dimensions to file
{
    FILE *transactionItemFile = fopen("TransactionOffsets.txt", "a");

    fprintf(transactionItemFile, "%d\n", transactionItems);
    fprintf(transactionItemFile, "\n");

    fclose(transactionItemFile); // close file

}

void writeTransactions(struct transaction transactions[], int totalTransactionItemCount)
{
    FILE *transactionFile = fopen("Transactions.txt", "a");

    int transactionItemCount;
    int totalTransactions = totalTransactionItemCount / 5;

    if (totalTransactions == 0) // items transacted must be less than 5
    {
        totalTransactions = 1;
        transactionItemCount = totalTransactionItemCount % 5; // then items transacted must be a remainder
    }
    else if (totalTransactions == 1) // items transacted must be equal to 5 or greater
    {
        if (totalTransactionItemCount % 5 == 0) // items transacted is 5
        {
            transactionItemCount = 5; // items transacted is greater than 5
        }
        else
        {
            totalTransactions = 2; // items transacted is greater than 5
            transactionItemCount = 5;
        }
    }
    else // items transacted must be equal to 10
    {
        totalTransactions = 2;
        transactionItemCount = 5;
    }


    for (int i = 0; i < totalTransactions; i++)
    {
        if (i == 1) // if i = 1 then items transacted must be greater than 5
            if (totalTransactionItemCount % 5 != 0) // then next transaction must be a remainder of 5
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

    fclose(transactionFile); // close file

}