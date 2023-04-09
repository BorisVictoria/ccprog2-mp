// This file contains the functions associated with the startup of the program
#include <stdio.h>
#include <string.h>
#include "structures.h"

int readUsers(struct user users[])
{
    FILE *userFile = fopen("Users.txt", "r");
    char buffer[1024];
    int userCount = 0;

    if (userFile == NULL)
        return userCount;

    while(!feof(userFile))
    {
        if (fgets(buffer, 1024, userFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %[^\n]", &users[userCount].userid, users[userCount].password);

        }

        if (fgets(buffer, 1024, userFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(users[userCount].name, buffer);
        }

        if (fgets(buffer, 1024, userFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(users[userCount].address, buffer);
        }

        if (fgets(buffer, 1024, userFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld", &users[userCount].contactnumber);
        }

        if (fgets(buffer, 1024, userFile) != NULL)
        {
            userCount++;
        }

    }

    fclose(userFile);

    return userCount;

}

int readItems(struct item items[])
{
    FILE *itemFile = fopen("Items.txt", "r");
    char buffer[1024];
    int itemCount = 0;

    if (itemFile == NULL)
        return itemCount;

    while(!feof(itemFile))
    {
        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %ld", &items[itemCount].productid, &items[itemCount].sellerid);
        }

        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].name, buffer);
        }

        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].category, buffer);
        }

        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].description, buffer);

        }

        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %lf", &items[itemCount].quantity, &items[itemCount].price);
        }

        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            itemCount++;
        }

    }

    fclose(itemFile);

    return itemCount;

}

int readCart(struct item items[], long userid)
{

    char fileName[32];
    sprintf(fileName, "%ld.txt", userid);

    FILE *itemFile = fopen(fileName, "r");
    char buffer[1024];
    int itemCount = 0;

    if (itemFile == NULL)
        return itemCount;

    while(!feof(itemFile))
    {
        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %ld", &items[itemCount].productid, &items[itemCount].sellerid);
        }

        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].name, buffer);
        }

        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].category, buffer);
        }

        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].description, buffer);

        }

        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %lf", &items[itemCount].quantity, &items[itemCount].price);
        }

        if (fgets(buffer, 1024, itemFile) != NULL)
        {
            itemCount++;
        }

    }

    fclose(itemFile);

    return itemCount;

}

int readTransactionItems(int transactionItems[])
{
    FILE *transactionItemFile = fopen("TransactionOffsets.txt", "r");
    char buffer[1024];
    int transactionCount = 0;

    if (transactionItemFile == NULL)
        return transactionCount;

    while(!feof(transactionItemFile))
    {
        if (fgets(buffer, 1024, transactionItemFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%d", &transactionItems[transactionCount]);
        }

        if (fgets(buffer, 1024, transactionItemFile) != NULL)
        {
            transactionCount++;
        }

    }

    fclose(transactionItemFile);

    return transactionCount;

}

void readTransactions(struct transaction transactions[], int transactionItems[], int transactionCount)
{
    FILE *transactionFile = fopen("Transactions.txt", "r");
    char buffer[1024];

    for (int i = 0; i < transactionCount; i++)
    {
        if (fgets(buffer, 1024, transactionFile) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %ld %ld %ld %ld %lf", &transactions[i].buyerid, &transactions[i].sellerid, &transactions[i].month, &transactions[i].day, &transactions[i].year, &transactions[i].total);
        }

        for (int j = 0; j < transactionItems[i]; j++)
        {
            if (fgets(buffer, 1024, transactionFile) != NULL)
            {
                buffer[strcspn(buffer, "\n")] = '\0';
                sscanf(buffer, "%ld %ld", &transactions[i].items[j].productid, &transactions[i].items[j].sellerid);
            }

            if (fgets(buffer, 1024, transactionFile) != NULL)
            {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(transactions[i].items[j].name, buffer);
            }

            if (fgets(buffer, 1024, transactionFile) != NULL)
            {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(transactions[i].items[j].category, buffer);
            }

            if (fgets(buffer, 1024, transactionFile) != NULL)
            {
                buffer[strcspn(buffer, "\n")] = '\0';
                strcpy(transactions[i].items[j].description, buffer);

            }

            if (fgets(buffer, 1024, transactionFile) != NULL)
            {
                buffer[strcspn(buffer, "\n")] = '\0';
                sscanf(buffer, "%ld %lf", &transactions[i].items[j].quantity, &transactions[i].items[j].price);
            }

            if (fgets(buffer, 1024, transactionFile) != NULL)
            {

            }
        }

    }

    fclose(transactionFile);
}

void storeItemsToUsers(struct user users[], int userCount, struct item items[], int itemCount)
{
    int userItemCount;

    for (int i = 0; i < userCount; i++)
    {
        userItemCount = 0;

        for (int j = 0; j < itemCount; j++)
        {
            if (users[i].userid == items[j].sellerid)
            {
                users[i].items[userItemCount] = items[j];
                userItemCount++;
                users[i].userItemCount = userItemCount;
            }
        }

    }


}