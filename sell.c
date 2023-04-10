//This file contains the functions for the sell menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

int addNewItem(struct user users[], int userIndex, int userItemCount, struct item items[], int itemCount)
{
    long productid;
    long sellerid;
    char name[21];
    char category[16];
    char description[31];
    long quantity;
    double price;
    char choice = '\0';
    int success = 0;
    int exit = 0;

    while (exit == 0)
    {

        printf("\nAdd a new item\n");

        printf("Input Product ID:");
        do
        {
            productid = getLong();
            if (productid < 1)
                printf("Please input a positive number");
        }
        while (productid < 1); // repeat prompt until user enters a positive number

        sellerid = users[userIndex].userid;

        for (int i = 0; i < userItemCount; i++) // search for productid and return if it exists
        {
            if (productid == users[userIndex].items[i].productid)
            {
                printf("Product ID already exists! Returning to menu\n");
                return success;
            }

        }

        for (int i = 0; i < itemCount; i++)
        {
            if (productid == items[i].productid) // search for productid and return if it exists
            {
                printf("Product ID already exists! Returning to menu\n");
                return success;
            }

        }

        printf("Input Name:");
        getString(name, 21);

        printf("Input Category:");
        getString(category,16);

        printf("Input Description:");
        getString(description, 31);

        printf("Input Quantity:");
        do
        {
            quantity = getLong();
            if (quantity < 1)
                printf("Please input a positive quantity:");
        }
        while (quantity < 1); // repeat prompt if user does not enter a positive number

        printf("Input Price:");
        do
        {
            price = getDouble();
            if (price < 1)
                printf("Please input a positive price:");
        }
        while (price < 1); // repeat prompt if user does not enter a positive number

        printf("\nProduct ID:%ld\n", productid);
        printf("Seller ID:%ld\n", sellerid);
        printf("Name:%s\n", name);
        printf("Category:%s\n", category);
        printf("Description:%s\n", description);
        printf("Quantity:%ld\n", quantity);
        printf("Price:%lf\n", price);
        printf("Would you like to add this item? [Y]/[N]:");
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
                printf("Would you like to continue adding an item? [Y]/[N]:");

                getString(&choice, 1);

                if (choice == 'N' || choice == 'n')
                {
                    printf("Returning to menu\n");
                    exit = 1;
                }
                else if (choice == 'Y' || choice == 'y')
                {

                }
                else
                {
                    printf("Unrecognized option, returning to menu\n");
                }

            }
            else
            {
                printf("Unrecognized option, returning to menu\n");
                exit = 1;
            }
        }
        else
        {
            printf("Unrecognized option, returning to menu\n");
            exit = 1;
        }

        if (success == 1) // store information if user says yes
        {
            printf("\nAdding item successful!\n");
            users[userIndex].items[userItemCount].sellerid = sellerid;
            users[userIndex].items[userItemCount].productid = productid;
            strcpy(users[userIndex].items[userItemCount].name, name);
            strcpy(users[userIndex].items[userItemCount].category, category);
            strcpy(users[userIndex].items[userItemCount].description, description);
            users[userIndex].items[userItemCount].quantity = quantity;
            users[userIndex].items[userItemCount].price = price;
            users[userIndex].userItemCount++;

        }

    }

    return success;

}

void showMyProducts(struct user users[], int userIndex, int userItemCount)
{
    printf("\nMy Products\n\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| Product ID |       Item Name       |     Category     |  Quantity  |    Unit Price    |\n");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < userItemCount; i++) // show products of user
    {
        printf("| %10ld | %-21s | %-16s | %10ld | %16lf |\n", users[userIndex].items[i].productid, users[userIndex].items[i].name, users[userIndex].items[i].category, users[userIndex].items[i].quantity, users[userIndex].items[i].price);
        printf("-----------------------------------------------------------------------------------------\n");
    }

}

void showMyLowStockProducts(struct user users[], int userIndex, int userItemCount)
{
    char choice = '\0';
    int exit = 0;
    int userProductIndex = 0;
    int found;
    int loop = 0;

    while (exit == 0) // cycle through items
    {
        found = 0;
        for (int i = userProductIndex; i < userItemCount; i++)
        {

            if (users[userIndex].items[i].quantity < 5) // print if a low stock item is found
            {
                found = 1;
                loop = 1; // will loop from end to start of items if a low stock item is found
                userProductIndex = i;
                i = userItemCount;
            }
            else if (i == userItemCount-1 && loop == 1) // set i to -1 to restart loop if a low stock item is found
            {
                i = -1;
            }
        }

        if (found == 1)
        {
            printf("\nLow Stock Products\n\n");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
            printf("| Product ID |       Item Name       |     Category     |           Description           |  Quantity  |    Unit Price    |\n");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %10ld | %-21s | %-16s | %-31s | %10ld | %16lf |\n", users[userIndex].items[userProductIndex].productid, users[userIndex].items[userProductIndex].name, users[userIndex].items[userProductIndex].category, users[userIndex].items[userProductIndex].description, users[userIndex].items[userProductIndex].quantity, users[userIndex].items[userProductIndex].price);
            printf("---------------------------------------------------------------------------------------------------------------------------\n");


            printf("[N] Next Item [X] Exit:");
            getString(&choice, 1);

            if (choice == 'N' || choice == 'n')
            {
                userProductIndex++; // go to next index in items
                if (userProductIndex >= userItemCount) // reset index to zero if index is greater than the number of items a user has
                    userProductIndex = 0;
            }

            else if (choice == 'X' || choice == 'x')
                exit = 1;
            else
                printf("Invalid input! Please try again\n");

        }
        else
        {
            printf("No Low Stock Products Found!\n"); // return if no low stock product is found
            exit = 1;
        }

    }
}

int sellMenu(struct user users[], int userIndex, struct item items[], int itemCount)
{

    int choice = 0;
    int userItemCount = users[userIndex].userItemCount;
    int itemAdded = 0;

    while(choice != 5)
    {
        printf("\nSell Menu\n\n");
        printf("[1] Add New Item\n");
        printf("[2] Edit Stock\n");
        printf("[3] Show My Products\n");
        printf("[4] Show My Low Stock Products\n");
        printf("[5] Exit\n");

        printf("\nSelect an option:");
        choice = getLong();

        switch (choice)
        {
            case 1:
                if (userItemCount == 20)
                    printf("Maximum number of items already added!\n");
                else
                    itemAdded = addNewItem(users, userIndex, userItemCount, items, itemCount);
                if (itemAdded == 1) // increment number of items if item was added
                {
                    userItemCount++;
                    itemCount++;
                    itemAdded = 0;
                    items[itemCount-1] = users[userIndex].items[userItemCount-1];
                    sortItems(users[userIndex].items, userItemCount);
                    sortItems(items, itemCount);
                }
                break;
            case 2:
                if (userItemCount == 0)
                    printf("No items found! Please add an item first\n");
                else
                    editStockMenu(users, userIndex, userItemCount, items, itemCount);
                break;
            case 3:
                if (userItemCount == 0)
                    printf("No items found! Please add an item first\n");
                else
                    showMyProducts(users, userIndex, userItemCount);
                break;
            case 4:
                if (userItemCount == 0)
                    printf("No items found! Please add an item first\n");
                else
                    showMyLowStockProducts(users, userIndex, userItemCount);
                break;
            case 5:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }
    }

    return itemCount;

}






