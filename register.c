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
        do
        {
            userid = getLong();
            if (userid < 1)
                printf("Please input a positive number:");
        }
        while (userid < 1); // repeat prompt until user enters a positive number

        for (int i = 0; i < userCount; i++)
        {
            if (userid == users[i].userid)
            {
                printf("User ID already exists! Exiting registration\n");
                return success; // return if user already exists
            }
        }

        printf("Input Name:");
        getString(name, 20);

        printf("Input Password:");
        getString(password,10);

        printf("Input Address:");
        getString(address, 30);

        printf("Input Contact Number:");
        do
        {
            contactnumber = getLong();
            if (contactnumber < 1)
                printf("Please input a positive number:");
        }
        while (contactnumber < 1); // repeat prompt until user enters a positive number

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
                    printf("Exiting registration\n");
                    exit = 1;
                }

            }
            else
            {
                printf("Unrecognized option, exiting registration\n");
                exit = 1;
            }
        }
        else
        {
            printf("Unrecognized option, exiting registration\n");
            exit = 1;
        }

        if (success == 1) // store information if user says yes
        {
            printf("\nRegistration successful!\n");
            users[userCount].userid = userid;
            strcpy(users[userCount].name, name);
            strcpy(users[userCount].password, password);
            strcpy(users[userCount].address, address);
            users[userCount].contactnumber = contactnumber;
            users[userCount].userItemCount = 0;

            printf("\nTest: Determine what was stored\n");
            printf("User ID:%ld\n", users[userCount].userid);
            printf("Name:%s\n", users[userCount].name);
            printf("Password:%s\n", users[userCount].password);
            printf("Address:%s\n", users[userCount].address);
            printf("Contact Number:%ld\n", users[userCount].contactnumber);
            printf("Item Count:%ld\n\n", users[userCount].userItemCount);


        }

    }

    return success; // return success of registration

}

