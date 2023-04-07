#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"

int main()
{
    struct user users[100];
    struct item items[2000];
    int userCount, itemCount, transactionCount;
    int choice = 0;
    int registerSuccess;


    userCount = readUsers(users);
    itemCount = readItems(items);  // Read all data from text files to structures;
    //transactionCount = readTransactions();
    storeItemsToUsers(users, userCount, items, itemCount);

    while (choice != 4)
    {
        printf("Shopping Application\n\n");
        printf("[1] Register as a User\n");
        printf("[2] User Menu\n");
        printf("[3] Admin Menu\n");
        printf("[4] Exit\n");

        printf("\nSelect an option:");
        choice = getLong();

        switch (choice)
        {
            case 1:
                registerSuccess = registerUser(users, userCount);
                if (registerSuccess == 1)
                {
                    userCount++;
                    sortUsers(users, userCount);
                }
                break;
            case 2:
                if (userCount == 0)
                    printf("No users found! Please register a user first\n\n");
                else
                    itemCount = userMenu(users, userCount, items, itemCount);
                break;
            case 3:
                adminMenu();
                break;
            case 4:
                printf("Thank you for shopping!\n");
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }

    }

    writeUsers(users, userCount);
    writeItems(items, itemCount);              // Write all data from structures to text files;
    //writeTransactions();



    return 0;
}