//This file contains the functions for the edit stock menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void replenish(struct user users[], int index, int productIndex)
{
    long quantity;
    char choice = '\0';
    int success = 0;

    printf("Input quantity to add:");
    quantity = getLong();
    printf("\nQuantity:%ld\n", quantity);

    printf("Confirm amount added [Y]/[N]:");
    getString(&choice, 1);

    if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')
    {
        if (choice == 'Y' || choice == 'y')
        {
            success = 1;
        }
        else
        {
            printf("Returning to menu\n\n");

        }
    }
    else
    {
        printf("Unrecognized option, returning to menu\n\n");
    }

    if (success == 1)
    {
        printf("\nAmount added!\n");
        users[index].items[productIndex].quantity += quantity;
        printf("New quantity:%ld\n", users[index].items[productIndex].quantity);
    }
}

void changePrice(struct user users[], int index, int productIndex)
{
    double price;
    char choice = '\0';
    int success = 0;

    printf("Input new price:");
    price = getDouble();
    printf("\nPrice:%lf\n", price);

    printf("Confirm new price [Y]/[N]:");
    getString(&choice, 1);

    if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')
    {
        if (choice == 'Y' || choice == 'y')
        {
            success = 1;
        }
        else
        {
            printf("Returning to menu\n\n");

        }
    }
    else
    {
        printf("Unrecognized option, returning to menu\n\n");
    }

    if (success == 1)
    {
        printf("\nPrice changed!\n");
        users[index].items[productIndex].price = price;
        printf("New price:%lf\n", users[index].items[productIndex].price);

    }

}

void changeItemName(struct user users[], int index, int productIndex)
{
    char name[21];
    char choice = '\0';
    int success = 0;

    printf("Input new name:");
    getString(name, 21);
    printf("\nName:%s\n", name);

    printf("Confirm new name [Y]/[N]:");
    getString(&choice, 1);

    if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')
    {
        if (choice == 'Y' || choice == 'y')
        {
            success = 1;
        }
        else
        {
            printf("Returning to menu\n\n");

        }
    }
    else
    {
        printf("Unrecognized option, returning to menu\n\n");
    }

    if (success == 1)
    {
        printf("\nItem name changed!\n");
        strcpy(users[index].items[productIndex].name, name);
        printf("New name:%s\n", users[index].items[productIndex].name);
    }

}

void changeCategory(struct user users[], int index, int productIndex)
{
    char category[16];
    char choice = '\0';
    int success = 0;

    printf("Input new category:");
    getString(category,16);
    printf("\nCategory:%s\n", category);

    printf("Confirm new category [Y]/[N]:");
    getString(&choice, 1);

    if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')
    {
        if (choice == 'Y' || choice == 'y')
        {
            success = 1;
        }
        else
        {
            printf("Returning to menu\n\n");

        }
    }
    else
    {
        printf("Unrecognized option, returning to menu\n\n");
    }

    if (success == 1)
    {
        printf("\nItem category changed!\n");
        strcpy(users[index].items[productIndex].category, category);
        printf("New category:%s\n", users[index].items[productIndex].category);
    }

}

void changeDescription(struct user users[], int index, int productIndex)
{
    char description[31];
    char choice = '\0';
    int success = 0;

    printf("Input Description:");
    getString(description, 31);
    printf("\nDescription:%s\n", description);

    printf("Confirm new description [Y]/[N]:");
    getString(&choice, 1);

    if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')
    {
        if (choice == 'Y' || choice == 'y')
        {
            success = 1;
        }
        else
        {
            printf("Returning to menu\n\n");

        }
    }
    else
    {
        printf("Unrecognized option, returning to menu\n\n");
    }

    if (success == 1)
    {
        printf("\nItem description changed!\n");
        strcpy(users[index].items[productIndex].description, description);
        printf("New description:%s\n", users[index].items[productIndex].description);
    }

}

void editStockMenu(struct user users[], int index, int itemCount) {

    long productid;
    int productIndex = 0;
    int found = 0;
    int choice = 0;

    showMyProducts(users, index, itemCount);

    printf("\nProduct ID:");
    productid = getLong();

    for (int i = 0; i < itemCount; i++)
    {
        if (productid == users[index].items[i].productid)
        {
            found = 1;
            productIndex = i;
            i = itemCount;
        }
    }

    if (found == 0)
    {
        printf("Product ID not found! Returning to sell menu\n\n");
        return;
    }

    while (choice != 6)
    {
        printf("\nEdit Stock Menu\n\n");
        printf("[1] Replenish\n");
        printf("[2] Change Price\n");
        printf("[3] Change Item Name\n");
        printf("[4] Change Category\n");
        printf("[5] Change Description\n");
        printf("[6] Exit\n");

        printf("\nSelect an option:");
        choice = getLong();

        switch (choice) {
            case 1:
                replenish(users, index, productIndex);
                break;
            case 2:
                changePrice(users, index, productIndex);
                break;
            case 3:
                changeItemName(users, index, productIndex);
                break;
            case 4:
                changeCategory(users, index, productIndex);
                break;
            case 5:
                changeDescription(users, index, productIndex);
                break;
            case 6:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }
    }

}