#include <stdio.h>
#include "structures.h"

int main()
{
    struct user users[100]; //initialize structs containing users and items
    struct item items[2000];
    int userCount, itemCount; // determine number of users and items
    int choice = 0;
    int registerSuccess;

    userCount = readUsers(users);
    itemCount = readItems(items);  // Read all data from text files to structures;
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
                if (userCount >= 100) // check if users are already at max size
                {
                    printf("Maximum number of users already!\n");
                }
                else
                {
                    registerSuccess = registerUser(users, userCount);
                }
                if (registerSuccess == 1) // increment number of users if registration is successful
                {
                    userCount++;
                    sortUsers(users, userCount); // sort users in increasing order by userid
                }
                break;
            case 2:
                if (userCount == 0)
                    printf("No users found! Please register a user first\n\n");
                else
                    itemCount = userMenu(users, userCount, items, itemCount);
                break;
            case 3:
                adminMenu(users, userCount, itemCount);
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

    return 0;
}