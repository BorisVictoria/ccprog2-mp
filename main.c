#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"

int main()
{
    struct user users[100];
    int choice = 0;

    while (choice != 4)
    {
        printf("Shopping Application\n\n");
        printf("[1] Register as a User\n");
        printf("[2] User Menu\n");
        printf("[3] Admin Menu\n");
        printf("[4] Exit\n");

        choice = getLong();

        switch (choice)
        {
            case 1:
                //register();
                break;
            case 2:
                userMenu();
                break;
            case 3:
                //adminMenu();
                break;
            case 4:
                printf("Thank you for shopping!\n");
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }

    }





    return 0;
}