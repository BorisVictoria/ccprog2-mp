//This file contains the functions for the sell menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void addNewItem()
{
    printf("Test!\n\n");
}

void showMyProducts()
{
    printf("Test!\n\n");
}

void showMyLowStockProducts()
{
    printf("Test!\n\n");
}

void sellMenu()
{

    int choice = 0;

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
                addNewItem();
                break;
            case 2:
                editStockMenu();
                break;
            case 3:
                showMyProducts();
                break;
            case 4:
                showMyLowStockProducts();
                break;
            case 5:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }
    }

}






