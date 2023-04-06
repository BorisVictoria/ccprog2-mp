//This file contains the functions for the buy menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void viewAllProducts()
{
    printf("Test!\n\n");
}

void showProductBySeller()
{
    printf("Test!\n\n");
}

void showProductByCategory()
{
    printf("Test!\n\n");
}

void showProductByName()
{
    printf("Test!\n\n");
}
void addToCart()
{
    printf("Test!\n\n");
}

void buyMenu()
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
                viewAllProducts();
                break;
            case 2:
                showProductBySeller();
                break;
            case 3:
                showProductByCategory();
                break;
            case 4:
                showProductByName();
                break;
            case 5:
                addToCart();
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


