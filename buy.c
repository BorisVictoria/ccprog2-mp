//This file contains the functions for the buy menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void viewAllProducts(struct user users[], int userCount)
{
    char choice = '\0';
    int exit = 0;
    int userIndex = 0;
    int userItemCount;

    while (exit == 0)
    {
        printf("\nAll Products\n\n");
        printf("Seller ID\t\t Product ID\t\t Item Name\t\t Category\t\t Quantity\t\t Unit Price\n");
        userItemCount = users[userIndex].userItemCount;

        for (int i = 0; i < userItemCount; i++)
        {
            printf("%ld %ld %s %s %ld %lf\n", users[userIndex].userid, users[userIndex].items[i].productid, users[userIndex].items[i].name, users[userIndex].items[i].category, users[userIndex].items[i].quantity, users[userIndex].items[i].price);
        }

        printf("[N] Next Seller [X] Exit:");
        getString(&choice, 1);

        if (choice == 'N' || choice == 'n')
        {
            userIndex++;
            while (users[userIndex].userItemCount == 0)
            {
                userIndex++;
            }

            if (userIndex >= userCount)
                userIndex = 0;
        }
        else if (choice == 'X' || choice == 'x')
            exit = 1;
        else
            printf("Invalid input! Please try again\n");

    }

}

void showProductBySeller(struct user users[], int userCount)
{
    long sellerid;
    int userIndex;
    int found = 0;

    sellerid = getLong();
    for (int i = 0; i < userCount; i++)
    {
        if (users[i].userid == sellerid)
        {
            found = 1;
            userIndex = i;
            i = userCount;
        }
    }

    if (found != 1)
    {
        printf("Seller ID not found! Returning to buy menu\n\n");
        return;
    }

    printf("\nSeller %ld Products\n\n", sellerid);
    printf("Product ID\t\t Item Name\t\t Category\t\t Quantity\t\t Unit Price\n");

    for (int i = 0; i < users[userIndex].userItemCount; i++)
    {
        printf("%ld %s %s %ld %lf\n", users[userIndex].items[i].productid, users[userIndex].items[i].name, users[userIndex].items[i].category, users[userIndex].items[i].quantity, users[userIndex].items[i].price);
    }

}

void showProductByCategory(struct item items[], int itemCount)
{
    char choice = '\0';
    int exit = 0;
    int productIndex = 0;
    int found;
    int loop = 0;

    char category[16];
    getString(category, 16);

    while (exit == 0)
    {
        found = 0;
        for (int i = productIndex; i < itemCount; i++)
        {

            if (strcmp(items[i].category, category) == 0)
            {
                found = 1;
                loop = 1;
                productIndex = i;
                i = itemCount;
            }
            else if (i == itemCount-1 && loop == 1)
            {
                i = -1;
            }
        }

        if (found == 1)
        {
            printf("\nProducts by Category\n\n");
            printf("Product ID\t\t Item Name\t\t Category\t\t Description \t\tQuantity\t\t Unit Price\n");
            printf("%ld %s %s %s %ld %lf\n", items[productIndex].productid, items[productIndex].name, items[productIndex].category, items[productIndex].description, items[productIndex].quantity, items[productIndex].price);

            printf("[N] Next Item [X] Exit:");
            getString(&choice, 1);

            if (choice == 'N' || choice == 'n')
            {
                productIndex++;
                if (productIndex >= itemCount)
                    productIndex = 0;
            }

            else if (choice == 'X' || choice == 'x')
                exit = 1;
            else
                printf("Invalid input! Please try again\n");

        }
        else
        {
            printf("No item with that category! Returning to buy menu\n\n");
            exit = 1;
        }

    }
}

void showProductByName(struct item items[], int itemCount)
{
    char choice = '\0';
    int exit = 0;
    int productIndex = 0;
    int found;
    int loop = 0;

    char name[21];
    getString(name, 21);

    while (exit == 0)
    {
        found = 0;
        for (int i = productIndex; i < itemCount; i++)
        {

            if (strstr(items[i].name, name) != NULL)
            {
                found = 1;
                loop = 1;
                productIndex = i;
                i = itemCount;
            }
            else if (i == itemCount-1 && loop == 1)
            {
                i = -1;
            }
        }

        if (found == 1)
        {
            printf("\nProducts by Name\n\n");
            printf("Product ID\t\t Item Name\t\t Category\t\t Description \t\tQuantity\t\t Unit Price\n");
            printf("%ld %s %s %s %ld %lf\n", items[productIndex].productid, items[productIndex].name, items[productIndex].category, items[productIndex].description, items[productIndex].quantity, items[productIndex].price);

            printf("[N] Next Item [X] Exit:");
            getString(&choice, 1);

            if (choice == 'N' || choice == 'n')
            {
                productIndex++;
                if (productIndex >= itemCount)
                    productIndex = 0;
            }

            else if (choice == 'X' || choice == 'x')
                exit = 1;
            else
                printf("Invalid input! Please try again\n");

        }
        else
        {
            printf("No item with that category! Returning to buy menu\n\n");
            exit = 1;
        }

    }
}
void addToCart(struct item items[], int itemCount)
{
    printf("Test!\n\n");
}

void buyMenu(struct user users[], int userIndex, int userCount, struct item items[], int itemCount)
{
    int choice = 0;
    struct cart userCart;

    //readCart(userCart); Implement

    while (choice != 8)
    {
        printf("\nBuy Menu\n\n");
        printf("[1] View all Products\n");
        printf("[2] Show all Products by a Specific Seller\n");
        printf("[3] Search Products by Category\n");
        printf("[4] Search Products by Name\n");
        printf("[5] Add to Cart\n");
        printf("[6] Edit Cart\n");
        printf("[7] Checkout\n");
        printf("[8] Exit\n");

        printf("\nSelect an option:");
        choice = getLong();

        switch (choice) {
            case 1:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n\n");
                else
                    viewAllProducts(users, userCount);
                break;
            case 2:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n\n");
                else
                    showProductBySeller(users, userCount);
                break;
            case 3:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n\n");
                else
                    showProductByCategory(items, itemCount);
                break;
            case 4:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n\n");
                else
                    showProductByName(items, itemCount);
                break;
            case 5:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n\n");
                else
                    addToCart(items, itemCount);
                break;
            case 6:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n\n");
                else
                    editCartMenu();
                break;
            case 7:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n\n");
                else
                    checkoutMenu();
                break;
            case 8:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }
    }

}


