//This file contains the functions for the registration menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

int registerUser(struct user users[], int userCount)
{
    long userid;
    char name[21];
    char password[11];
    char address[31];
    long contactnumber;
    char choice = '\0';
    int success = 0;
    int exit = 0;

    while (exit == 0)
    {

        printf("\nRegister as a User\n");

        printf("Input User ID:");
        userid = getLong();

        for (int i = 0; i < userCount; i++)
        {
            if (userid == users[i].userid)
            {
                printf("User ID already exists! Exiting registration\n\n");
                return success;
            }
        }

        printf("Input Name:");
        getString(name, 21);

        printf("Input Password:");
        getString(password,11 );

        printf("Input Address:");
        getString(address, 31);

        printf("Input Contact Number:");
        contactnumber = getLong();

        printf("\nUser ID:%ld\n", userid);
        printf("Name:%s\n", name);
        printf("Password:%s\n", password);
        printf("Address:%s\n", address);
        printf("Contact Number:%ld\n", contactnumber);
        printf("Would you like to register this information? [Y]/[N]:");
        getString(&choice, 1);

        if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')
        {
            if (choice == 'Y' || choice == 'y')
            {
                success = 1;
                exit = 1;
            }
            else if (choice == 'N' || choice == 'n')
            {
                printf("Would you like to continue registration? [Y]/[N]:");

                getString(&choice, 1);

                if (choice == 'N' || choice == 'n')
                {
                    printf("Exiting registration\n\n");
                    exit = 1;
                }

            }
            else
            {
                printf("Unrecognized option, exiting registration\n\n");
                exit = 1;
            }
        }
        else
        {
            printf("Unrecognized option, exiting registration\n\n");
            exit = 1;
        }

        if (success == 1)
        {
            printf("\nRegistration successful!\n");
            users[userCount].userid = userid;
            strcpy(users[userCount].name, name);
            strcpy(users[userCount].password, password);
            strcpy(users[userCount].address, address);
            users[userCount].contactnumber = contactnumber;
            users[userCount].itemCount = 0;

            printf("\nTest: Determine what was stored\n");
            printf("User ID:%ld\n", users[userCount].userid);
            printf("Name:%s\n", users[userCount].name);
            printf("Password:%s\n", users[userCount].password);
            printf("Address:%s\n", users[userCount].address);
            printf("Contact Number:%ld\n", users[userCount].contactnumber);
            printf("Item Count:%ld\n\n", users[userCount].itemCount);


        }

    }

    return success;

}

