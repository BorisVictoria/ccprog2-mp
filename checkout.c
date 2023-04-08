//This file contains the functions for the checkout menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void checkoutAll(struct transaction transactions[])
{
    printf("Test!\n\n");
}
void checkoutBySeller(struct transaction transactions[])
{
    printf("Test!\n\n");
}
void checkoutByItem(struct transaction transactions[])
{
    printf("Test!\n\n");
}

int checkCartItem(struct item cart[], struct item items[], int cartItemIndex, int itemIndex)
{
    int proceed = 1;

    if (strcmp(cart[cartItemIndex].name, items[itemIndex].name) != 0)
    {
        printf("Name of product in cart has changed!\n");
        printf("Name in cart: %s\n", cart[cartItemIndex].name);
        printf("Name in items: %s\n", items[itemIndex].name);
        printf("Changing name...\n\n");

        strcpy(cart[cartItemIndex].name, items[itemIndex].name);
    }

    if (strcmp(cart[cartItemIndex].category, items[itemIndex].category) != 0)
    {
        printf("Category of product in cart has changed!\n");
        printf("Category in cart: %s\n", cart[cartItemIndex].category);
        printf("Category in items: %s\n", items[itemIndex].category);
        printf("Changing category...\n\n");

        strcpy(cart[cartItemIndex].category, items[itemIndex].category);
    }

    if (strcmp(cart[cartItemIndex].description, items[itemIndex].description) != 0)
    {
        printf("Description of product in cart has changed!\n");
        printf("Description in cart: %s\n", cart[cartItemIndex].description);
        printf("Description in items: %s\n", items[itemIndex].description);
        printf("Changing description...\n\n");

        strcpy(cart[cartItemIndex].description, items[itemIndex].description);
    }

    if (cart[cartItemIndex].quantity > items[itemIndex].quantity)
    {
        printf("Unfortunately, the currently selected quantity for this item is greater than what's available.\n");
        printf("Please edit the quantity before proceeding to checkout...\n");
        printf("Quantity in cart: %ld\n", cart[cartItemIndex].quantity);
        printf("Available quantity: %ld\n\n", items[itemIndex].quantity);
        proceed = 0;
    }

    if (cart[cartItemIndex].price != items[itemIndex].price)
    {
        printf("Price of product in cart has changed!\n");
        printf("Price in cart: %s\n", cart[cartItemIndex].price);
        printf("Price in items: %s\n", items[itemIndex].price);
        printf("Changing price...\n\n");

        cart[cartItemIndex].price = items[itemIndex].price;

    }

    return proceed;
}

int cartIntegrityCheck(struct item items[], int itemCount, struct item cart[], int cartItemCount, int* proceed)
{
    long productid;

    for (int i = 0; i < cartItemCount; i++)
    {
        productid = cart[i].productid;
        for (int j = 0; j < itemCount; j++)
        {
            if (productid == items[j].productid)
            {
                printf("Checking availability of product: %s..........Done!\n\n", cart[i].name);
                *proceed = checkCartItem(cart, items, i, j);
                cartItemCount = sortCart(cart, cartItemCount);
            }

        }
    }

    return cartItemCount;

}

int checkoutMenu(struct user users[], int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount)
{
    int choice = 0;
    struct transaction transactions[10];
    long month;
    long day;
    long year;
    int proceed = 1;

    printf("\n");
    cartItemCount = cartIntegrityCheck(items, itemCount, cart, cartItemCount, &proceed);
    cartItemCount = sortCart(cart, cartItemCount);

    if (proceed == 0)
    {
        printf("Please change the quantity of the products above or remove them before proceeding to checkout\n");
    }

    printf("Input month [mm]:");
    month = getLong();
    printf("Input day [dd]:");
    day = getLong();
    printf("Input year [yyyy]:");
    year = getLong();

    for (int i = 0; i < 10; i++)
    {
        transactions[i].month = month;
        transactions[i].day = day;
        transactions[i].year = year;
    }

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
                checkoutAll(transactions);
                break;
            case 2:
                checkoutBySeller(transactions);
                break;
            case 3:
                checkoutByItem(transactions);
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
