//This file contains the functions for the checkout menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void checkoutAll()
{
    printf("Test!\n\n");
}
void checkoutBySeller()
{
    printf("Test!\n\n");
}
void checkoutByItem()
{
    printf("Test!\n\n");
}

int checkoutMenu(struct item items[], int itemCount, struct item cart[], int cartItemCount)
{
    int choice = 0;

    while (choice != 4)
    {
        printf("\nCheckout Menu\n\n");
        printf("[1] All\n");
        printf("[2] By a Specific Seller\n");
        printf("[3] Specific Item\n");
        printf("[4] Exit\n");

        printf("\nSelect an option:");
        choice = getLong();

        switch (choice) {
            case 1:
                checkoutAll();
                break;
            case 2:
                checkoutBySeller();
                break;
            case 3:
                checkoutByItem();
                break;
            case 4:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }
    }

    return cartItemCount;

}
