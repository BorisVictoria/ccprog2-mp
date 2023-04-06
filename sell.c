//This file contains the functions for the sell menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

int addNewItem(struct user users[], int index, int itemCount)
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

        sellerid = users[index].userid;

        for (int i = 0; i < itemCount; i++)
        {
            if (productid == users[index].items[i].productid)
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
            users[index].items[itemCount].sellerid = sellerid;
            users[index].items[itemCount].productid = productid;
            strcpy(users[index].items[itemCount].name, name);
            strcpy(users[index].items[itemCount].category, category);
            strcpy(users[index].items[itemCount].description, description);
            users[index].items[itemCount].quantity = quantity;
            users[index].items[itemCount].price = price;
            users[index].itemCount++;

            printf("\nTest: Determine what was stored\n");
            printf("\nProduct ID:%ld\n", users[index].items[itemCount].productid);
            printf("Seller ID:%ld\n", users[index].items[itemCount].sellerid = sellerid);
            printf("Name:%s\n", users[index].items[itemCount].name);
            printf("Category:%s\n", users[index].items[itemCount].category);
            printf("Description:%s\n", users[index].items[itemCount].description);
            printf("Quantity:%ld\n",  users[index].items[itemCount].quantity);
            printf("Price:%lf\n\n",  users[index].items[itemCount].price);

        }

    }

    return success;

}

void showMyProducts(struct user users[], int index, int itemCount)
{
    printf("\nMy Products\n\n");
    printf("Product ID\t\t Item Name\t\t Category\t\t Quantity\t\t Unit Price\n");

    for (int i = 0; i < itemCount; i++)
    {
        printf("%ld %s %s %ld %lf\n", users[index].items[i].productid, users[index].items[i].name, users[index].items[i].category, users[index].items[i].quantity, users[index].items[i].price);
    }

}

void showMyLowStockProducts(struct user users[], int index, int itemCount)
{
    printf("\nMy Low Stock Products\n\n");
    printf("Product ID\t\t Item Name\t\t Category\t\t Description\t\t Quantity\t\t Unit Price\n");

    for (int i = 0; i < itemCount; i++)
    {
        if (users[index].items[i].quantity < 5)
            printf("%ld %s %s %s %ld %lf\n", users[index].items[i].productid, users[index].items[i].name, users[index].items[i].category, users[index].items[i].description, users[index].items[i].quantity, users[index].items[i].price);
    }
}

void sellMenu(struct user users[], int index)
{

    int choice = 0;
    int itemCount = users[index].itemCount;
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
                if (itemCount == 20)
                    printf("Maximum number of items already added!\n\n");
                else
                    itemAdded = addNewItem(users, index, itemCount);
                if (itemAdded == 1)
                {
                    itemCount++;
                    itemAdded = 0;
                    sortItems(users[index].items, itemCount);
                }
                break;
            case 2:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n\n");
                else
                    editStockMenu(users, index, itemCount);
                break;
            case 3:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n\n");
                else
                    showMyProducts(users, index, itemCount);
                break;
            case 4:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n\n");
                else
                    showMyLowStockProducts(users, index, itemCount);
                break;
            case 5:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }
    }

}






