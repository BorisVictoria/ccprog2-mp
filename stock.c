//This file contains the functions for the edit stock menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void replenish()
{
    printf("Test!\n\n");
}

void changePrice()
{
    printf("Test!\n\n");
}

void changeItemName()
{
    printf("Test!\n\n");
}

void changeCategory()
{
    printf("Test!\n\n");
}

void changeDescription()
{
    printf("Test!\n\n");
}

void editStockMenu() {
    int choice = 0;

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
                replenish();
                break;
            case 2:
                changePrice();
                break;
            case 3:
                changeItemName();
                break;
            case 4:
                changeCategory();
                break;
            case 5:
                changeDescription();
                break;
            case 6:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }
    }

}