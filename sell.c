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
        productid = getLong();

        sellerid = users[userIndex].userid;

        for (int i = 0; i < userItemCount; i++)
        {
            if (productid == users[userIndex].items[i].productid)
            {
                printf("Product ID already exists! Returning to menu\n\n");
                return success;
            }

        }

        for (int i = 0; i < itemCount; i++)
        {
            if (productid == items[i].productid)
            {
                printf("Product ID already exists! Returning to menu\n\n");
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
        quantity = getLong();

        printf("Input Price:");
        price = getDouble();

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
                    printf("Returning to menu\n\n");
                    exit = 1;
                }
                else if (choice != 'Y' || choice != 'y')
                {
                    printf("Unrecognized option, returning to menu\n\n");
                    exit = 1;
                }

            }
            else
            {
                printf("Unrecognized option, returning to menu\n\n");
                exit = 1;
            }
        }
        else
        {
            printf("Unrecognized option, returning to menu\n\n");
            exit = 1;
        }

        if (success == 1)
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

            printf("\nTest: Determine what was stored\n");
            printf("\nProduct ID:%ld\n", users[userIndex].items[userItemCount].productid);
            printf("Seller ID:%ld\n", users[userIndex].items[userItemCount].sellerid);
            printf("Name:%s\n", users[userIndex].items[userItemCount].name);
            printf("Category:%s\n", users[userIndex].items[userItemCount].category);
            printf("Description:%s\n", users[userIndex].items[userItemCount].description);
            printf("Quantity:%ld\n",  users[userIndex].items[userItemCount].quantity);
            printf("Price:%lf\n\n",  users[userIndex].items[userItemCount].price);

        }

    }

    return success;

}

void showMyProducts(struct user users[], int userIndex, int userItemCount)
{
    printf("\nMy Products\n\n");
    printf("Product ID\t\t Item Name\t\t Category\t\t Quantity\t\t Unit Price\n");

    for (int i = 0; i < userItemCount; i++)
    {
        printf("%ld %s %s %ld %lf\n", users[userIndex].items[i].productid, users[userIndex].items[i].name, users[userIndex].items[i].category, users[userIndex].items[i].quantity, users[userIndex].items[i].price);
    }

}

void showMyLowStockProducts(struct user users[], int userIndex, int userItemCount)
{
    char choice = '\0';
    int exit = 0;
    int userProductIndex = 0;
    int found;
    int loop = 0;

    while (exit == 0)
    {
        found = 0;
        for (int i = userProductIndex; i < userItemCount; i++)
        {

            if (users[userIndex].items[i].quantity < 5)
            {
                found = 1;
                loop = 1;
                userProductIndex = i;
                i = userItemCount;
            }
            else if (i == userItemCount-1 && loop == 1)
            {
                i = -1;
            }
        }

        if (found == 1)
        {
            printf("\nLow Stock Products\n\n");
            printf("Product ID\t\t Item Name\t\t Category\t\t Description \t\tQuantity\t\t Unit Price\n");
            printf("%ld %s %s %s %ld %lf\n", users[userIndex].items[userProductIndex].productid, users[userIndex].items[userProductIndex].name, users[userIndex].items[userProductIndex].category, users[userIndex].items[userProductIndex].description, users[userIndex].items[userProductIndex].quantity, users[userIndex].items[userProductIndex].price);

            printf("[N] Next Item [X] Exit:");
            getString(&choice, 1);

            if (choice == 'N' || choice == 'n')
            {
                userProductIndex++;
                if (userProductIndex >= userItemCount)
                    userProductIndex = 0;
            }

            else if (choice == 'X' || choice == 'x')
                exit = 1;
            else
                printf("Invalid input! Please try again\n");

        }
        else
        {
            printf("No Low Stock Products Found!");
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
                    printf("Maximum number of items already added!\n\n");
                else
                    itemAdded = addNewItem(users, userIndex, userItemCount, items, itemCount);
                if (itemAdded == 1)
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
                    printf("No items found! Please add an item first\n\n");
                else
                    editStockMenu(users, userIndex, userItemCount, items, itemCount);
                break;
            case 3:
                if (userItemCount == 0)
                    printf("No items found! Please add an item first\n\n");
                else
                    showMyProducts(users, userIndex, userItemCount);
                break;
            case 4:
                if (userItemCount == 0)
                    printf("No items found! Please add an item first\n\n");
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






