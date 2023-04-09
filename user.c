//This file contains the functions for the user menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

int userMenu(struct user users[], int userCount, struct item items[], int itemCount)
{
    long userid;
    char password[11];
    int userIndex = 0;
    int found = 0;
    int choice = 0;

    printf("User ID:");
    do
    {
        userid = getLong();
        if (userid < 1)
            printf("Please input a positive number:");
    }
    while (userid < 1);

    for (int i = 0; i < userCount; i++)
    {
        if (userid == users[i].userid)
        {
            found = 1;
            userIndex = i;
            i = userCount;
        }
    }

    if (found == 0)
    {
        printf("User ID not found! Returning to main menu\n\n");
        return itemCount;
    }

    printf("Password:");
    getString(password, 10);

    if (strcmp(password, users[userIndex].password) != 0)
    {
        printf("Incorrect password! Returning to main menu\n\n");
        return itemCount;
    }

    while(choice != 3)
    {
        printf("\nUser Menu\n\n");
        printf("[1] Sell Menu\n");
        printf("[2] Buy Menu\n");
        printf("[3] Return to main menu\n");

        printf("\nSelect an option:");
        choice = getLong();

        switch (choice)
        {
            case 1:
                itemCount = sellMenu(users, userIndex, items, itemCount);
                break;
            case 2:
                buyMenu(users, userIndex, userCount, items, itemCount);
                break;
            case 3:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }

    }

    return itemCount;

}