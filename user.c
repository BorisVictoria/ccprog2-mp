//This file contains the functions for the user menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

/* userMenu has an int return type and returns the itemCount when sell menu is selected or user not found
* @param users passes the users array
* @param userCount number of users in the users array
* @param items passes items array
* @param itemCount number of items in item array
* @return returns itemCount
* Pre-condition: users array has at least one user
*/
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
    while (userid < 1); // repeat prompt until user enters a positive number

    for (int i = 0; i < userCount; i++) // search for user in users array
    {
        if (userid == users[i].userid)
        {
            found = 1;
            userIndex = i;
            i = userCount;
        }
    }

    if (found == 0) // return if user was not found
    {
        printf("User ID not found! Returning to main menu\n\n");
        return itemCount;
    }

    printf("Password:");
    getString(password, 10);

    if (strcmp(password, users[userIndex].password) != 0) // return if password is incorrect
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