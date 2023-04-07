//This file contains the functions for the buy menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void viewAllProducts(struct item items[], int itemCount)
{
    printf("\nAll Products\n\n");
    printf("Product ID\t\t Item Name\t\t Category\t\t Quantity\t\t Unit Price\n");

    for (int i = 0; i < itemCount )

}

void showProductBySeller(struct item items[], int itemCount)
{
    printf("Test!\n\n");
}

void showProductByCategory(struct item items[], int itemCount)
{
    printf("Test!\n\n");
}

void showProductByName(struct item items[], int itemCount)
{
    printf("Test!\n\n");
}
void addToCart(struct item items[], int itemCount)
{
    printf("Test!\n\n");
}

void buyMenu(struct user users[], int userIndex, struct item items[], int itemCount)
{
    int choice = 0;

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
                viewAllProducts(items, itemCount);
                break;
            case 2:
                showProductBySeller(items, itemCount);
                break;
            case 3:
                showProductByCategory(items, itemCount);
                break;
            case 4:
                showProductByName(items, itemCount);
                break;
            case 5:
                addToCart(items, itemCount);
                break;
            case 6:
                editCartMenu();
                break;
            case 7:
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


