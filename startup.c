// This file contains the functions associated with the startup of the program
#include <stdio.h>
#include <string.h>
#include "structures.h"

int readUsers(struct user users[])
{
    FILE *userFile = fopen("Users.txt", "r");
    char buffer[1024];
    int userCount = 0;
    char temp;

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
    char temp;

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

void readTransactions(struct transaction transactions[])
{
    FILE *transactionFile = fopen("Transactions.txt", "r");

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