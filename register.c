//This file contains the functions for the registration menu and all associated features.
#include <stdio.h>
#include <string.h>
#include <conio.h>
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

    while (choice != 'n' || choice != 'N')
    {

        printf("Register as a User\n");

        printf("Input User ID:");
        userid = getLong();

        printf("Input Name:");
        getString(name, 21);

        printf("Input Password:");
        getString(password,11 );

        printf("Input Address:");
        getString(address, 31);

        printf("Input Contact Number:");
        contactnumber = getLong();

        printf("User ID:%ld\n", userid);
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
            }
            else if (choice == 'N' || choice == 'n')
            {
                printf("Would you like to continue registration? [Y]/[N]:");

                getString(&choice, 1);

                if (choice == 'N' || choice == 'n')
                {
                    printf("Exiting registration");
                }
                else if (choice != 'Y' || choice != 'y')
                {
                    printf("Unrecognized option, exiting registration");
                }
            }
            else
            {
                printf("Unrecognized option, exiting registration");
                choice = 'n';
            }
        }
        else
        {
            printf("Unrecognized option, exiting registration");
        }

        if (success == 1)
        {
            printf("Registration successful!\n");
            users[userCount].userid = userid;
            strcpy(users[userCount].name, name);
            strcpy( users[userCount].password, password);
            strcpy( users[userCount].address, address);
            users[userCount].contactnumber = contactnumber;

            printf("Test: Determine what was stored\n");
            printf("User ID:%ld\n", users[userCount].userid);
            printf("Name:%s\n", users[userCount].name);
            printf("Password:%s\n", users[userCount].password);
            printf("Address:%s\n", users[userCount].address);
            printf("Contact Number:%ld\n", users[userCount].contactnumber);
        }

        return success;
    }



}

