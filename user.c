//This file contains the functions for the user menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void userMenu(struct user users[], int userCount)
{
    long userid;
    char password[11];
    int index = 0;
    int found = 0;
    int choice = 0;

    printf("User ID:");
    userid = getLong();

    for (int i = 0; i < userCount; i++)
    {
        if (userid == users[i].userid)
        {
            found = 1;
            index = i;
            i = userCount;
        }
    }

    if (found == 0)
    {
        printf("User ID not found! Returning to main menu\n\n");
        return;
    }

    printf("Password:");
    getString(password, 11);

    if (strcmp(password, users[index].password) != 0)
    {
        printf("Incorrect password! Returning to main menu\n\n");
        return;
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
                sellMenu(users, index);
                break;
            case 2:
                buyMenu();
                break;
            case 3:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }

    }

}