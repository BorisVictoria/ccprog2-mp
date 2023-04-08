//This file contains the functions for the edit cart menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

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

void editCartMenu(struct item cart[], int cartItemCount)
{
    int choice = 0;
    long sellerid;
    int toPrint = 1;

    printf("\nProducts in Cart\n");

    for (int i = 0; i < cartItemCount; i++)
    {
        if (toPrint == 1)
        {
            sellerid = cart[i].sellerid;
            printf("\nSeller %ld Products\n", sellerid);
        }
        else if (toPrint == 0)
        {
            if (sellerid < cart[i].sellerid)
            {
                if (sellerid != cart[i].sellerid)
                {
                    sellerid = cart[i].sellerid;
                    toPrint = 1;
                }
            }
        }

        for (int j = 0;j < cartItemCount && toPrint == 1; j++)
        {
            if (sellerid == cart[j].sellerid)
                printf("%ld %s %s %ld %lf\n", cart[j].productid, cart[j].name, cart[j].category, cart[j].quantity, cart[j].price);

            if (j == cartItemCount-1)
                toPrint = 0;
        }

    }

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
