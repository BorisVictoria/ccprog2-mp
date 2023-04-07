//This file contains the functions for the edit cart menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void readCart(struct cart userCart)
{

}

void writeCart(struct cart userCart)
{

}

void removeItemsFromSeller()
{
    printf("Test!\n\n");
}
void removeSpecificItem()
{
    printf("Test!\n\n");
}
void editQuantity()
{
    printf("Test!\n\n");
}

void editCartMenu()
{
    int choice = 0;

    while (choice != 4)
    {
        printf("\nEdit Cart Menu\n\n");
        printf("[1] Remove All Items from Seller\n");
        printf("[2] Remove Specific Item\n");
        printf("[3] Edit Quantity\n");
        printf("[4] Exit\n");

        printf("\nSelect an option:");
        choice = getLong();

        switch (choice) {
            case 1:
                removeItemsFromSeller();
                break;
            case 2:
                removeSpecificItem();
                break;
            case 3:
                editQuantity();
                break;
            case 4:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }
    }

}
