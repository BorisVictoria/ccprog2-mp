// This file contains the functions associated with the startup of the program
#include <stdio.h>
#include <string.h>
#include "structures.h"

int readUsers(struct user users[])
{
    FILE *userFile = fopen("Users.txt", "r");
    char buffer[1024]; // set buffer to 1024
    int userCount = 0; // number of users

    if (userFile == NULL) // users must be zero if file cannot be found
        return userCount;

    while(!feof(userFile)) // read until eof
    {
        if (fgets(buffer, 1024, userFile) != NULL) // store id and password
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %[^\n]", &users[userCount].userid, users[userCount].password);

        }

        if (fgets(buffer, 1024, userFile) != NULL) // store name
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(users[userCount].name, buffer);
        }

        if (fgets(buffer, 1024, userFile) != NULL) // store address
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(users[userCount].address, buffer);
        }

        if (fgets(buffer, 1024, userFile) != NULL) // store contactnumber
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld", &users[userCount].contactnumber);
        }

        if (fgets(buffer, 1024, userFile) != NULL) // increment users
        {
            userCount++;
        }

    }

    fclose(userFile); // close file

    return userCount; // return number of users

}

int readItems(struct item items[])
{
    FILE *itemFile = fopen("Items.txt", "r");
    char buffer[1024]; // set buffer to 1024
    int itemCount = 0; // number of items

    if (itemFile == NULL) // items must be zero if file is not found
        return itemCount;

    while(!feof(itemFile)) // read until eof
    {
        if (fgets(buffer, 1024, itemFile) != NULL) // store product id and seller id
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %ld", &items[itemCount].productid, &items[itemCount].sellerid);
        }

        if (fgets(buffer, 1024, itemFile) != NULL) // store item name
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].name, buffer);
        }

        if (fgets(buffer, 1024, itemFile) != NULL) // store item category
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].category, buffer);
        }

        if (fgets(buffer, 1024, itemFile) != NULL) // store item description
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].description, buffer);

        }

        if (fgets(buffer, 1024, itemFile) != NULL) // store quantity and price
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %lf", &items[itemCount].quantity, &items[itemCount].price);
        }

        if (fgets(buffer, 1024, itemFile) != NULL) // increment items
        {
            itemCount++;
        }

    }

    fclose(itemFile); // close file

    return itemCount; // return number of items

}

int readCart(struct item items[], long userid)
{

    char fileName[32]; // item filename will be userid
    sprintf(fileName, "%ld.txt", userid);

    FILE *itemFile = fopen(fileName, "r");
    char buffer[1024]; // set buffer to 1024
    int itemCount = 0;

    if (itemFile == NULL) // cart must be empty if file is not found
        return itemCount;

    while(!feof(itemFile)) // read until eof
    {
        if (fgets(buffer, 1024, itemFile) != NULL) // store product id and seller id
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %ld", &items[itemCount].productid, &items[itemCount].sellerid);
        }

        if (fgets(buffer, 1024, itemFile) != NULL) // store name
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].name, buffer);
        }

        if (fgets(buffer, 1024, itemFile) != NULL) // store category
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].category, buffer);
        }

        if (fgets(buffer, 1024, itemFile) != NULL) // store description
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(items[itemCount].description, buffer);

        }

        if (fgets(buffer, 1024, itemFile) != NULL) // store quantity and price
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %lf", &items[itemCount].quantity, &items[itemCount].price);
        }

        if (fgets(buffer, 1024, itemFile) != NULL) // increment items
        {
            itemCount++;
        }

    }

    fclose(itemFile); // close file

    return itemCount; // return number of items

}

int readTransactionItems(int transactionItems[])
{
    FILE *transactionItemFile = fopen("TransactionOffsets.txt", "r");
    char buffer[1024]; // set buffer to 1024
    int transactionCount = 0;

    if (transactionItemFile == NULL) // transactions must be zero if file is not found
        return transactionCount;

    while(!feof(transactionItemFile)) // read until eof
    {
        if (fgets(buffer, 1024, transactionItemFile) != NULL) // store number of items of each transaction
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%d", &transactionItems[transactionCount]);
        }

        if (fgets(buffer, 1024, transactionItemFile) != NULL) // increment number of transactions
        {
            transactionCount++;
        }

    }

    fclose(transactionItemFile); // close file

    return transactionCount; // return number of transactions

}

void readTransactions(struct transaction transactions[], int transactionItems[], int transactionCount)
{
    FILE *transactionFile = fopen("Transactions.txt", "r");
    char buffer[1024];

    for (int i = 0; i < transactionCount; i++)
    {
        if (fgets(buffer, 1024, transactionFile) != NULL)  // store information about transaction
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            sscanf(buffer, "%ld %ld %ld %ld %ld %lf", &transactions[i].buyerid, &transactions[i].sellerid, &transactions[i].month, &transactions[i].day, &transactions[i].year, &transactions[i].total);
        }

        for (int j = 0; j < transactionItems[i]; j++) // store items in transactions
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

            if (fgets(buffer, 1024, transactionFile) != NULL) // catch new line character
            {

            }
        }

    }

    fclose(transactionFile); // close file
}

void storeItemsToUsers(struct user users[], int userCount, struct item items[], int itemCount)
{
    int userItemCount;

    for (int i = 0; i < userCount; i++) // store items to items array in users
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