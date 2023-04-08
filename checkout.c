//This file contains the functions for the checkout menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"


void checkoutAll(struct user users[], long userid, int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount, int month, int day, int year)
{
    struct transaction transactions[10];






}
void checkoutBySeller(struct user users[], long userid, int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount, int month, int day, int year)
{
    struct transaction transactions[10];
    long productid;
    long sellerid;
    int cartProductIndex;
    int userIndex;
    int userProductIndex;
    int productIndex;
    int found = 0;
    int ctr = 0;
    int sellerProducts = 0;

    printf("Input Seller ID:");
    sellerid = getLong();

    for (int i = 0; i < cartItemCount; i++)
    {
        if (sellerid == cart[i].sellerid)
        {
            found = 1;
        }

    }

    if (found == 0)
    {
        printf("Seller Id not found! Returning to buy menu\n");
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        transactions[i].total = 0;
    }

    found = 0;
    for (int i = 0; i < cartItemCount; i++)
    {
        if (sellerid == cart[i].sellerid)
        {
            productid = cart[i].productid;
            cartProductIndex = i;
            found = 1;
        }

        if (found == 1)
        {
            for (int j = 0; j < userCount; j++)
            {
                for (int k = 0; k < users[j].userItemCount; k++)
                {
                    if (productid == users[j].items[k].productid)
                    {
                        userIndex = j;
                        j = userCount;
                        k = 20;
                    }
                }
            }

            for (int j = 0; j < users[userIndex].userItemCount; j++)
            {
                if (users[userIndex].items[j].productid == productid)
                {
                    userProductIndex = j;
                    j = userCount;
                }
            }

            for (int j = 0; j < itemCount; j++)
            {
                if (productid == items[j].productid)
                {
                    productIndex = j;
                    j = itemCount;
                }
            }

            transactions[ctr].buyerid = userid;
            transactions[ctr].sellerid = cart[cartProductIndex].sellerid;
            transactions[ctr].month = month;
            transactions[ctr].day = day;
            transactions[ctr].year = year;
            transactions[ctr].total += cart[cartProductIndex].quantity * cart[cartProductIndex].price;

            transactions[ctr].items[sellerProducts].sellerid = cart[cartProductIndex].sellerid;
            transactions[ctr].items[sellerProducts].productid = cart[cartProductIndex].productid;
            strcpy(transactions[ctr].items[sellerProducts].name, cart[cartProductIndex].name);
            strcpy(transactions[ctr].items[sellerProducts].category, cart[cartProductIndex].category);
            strcpy(transactions[ctr].items[sellerProducts].description, cart[cartProductIndex].description);
            transactions[ctr].items[sellerProducts].quantity = cart[cartProductIndex].quantity;
            transactions[ctr].items[sellerProducts].price = cart[cartProductIndex].price;

            users[userIndex].items[userProductIndex].quantity -= cart[cartProductIndex].quantity;
            items[productIndex].quantity -= cart[cartProductIndex].quantity;
            cart[cartProductIndex].quantity = 0;
            sellerProducts++;
            found = 0;
            if (sellerProducts == 5) {
                ctr++;
                sellerProducts = 0;
            }

        }

    }

    for (int i = 0; i <= ctr; i++)
    {
        if (ctr > 0 && i < ctr)
        {
            writeTransactionItems(5);
        }
        else
            writeTransactionItems(sellerProducts);

    }

    writeTransactions(transactions, ctr*5+sellerProducts);


}

void checkoutByItem(struct user users[], long userid, int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount, int month, int day, int year)
{
    struct transaction transactions[10];
    long productid;
    int cartProductIndex;
    int userIndex;
    int userProductIndex;
    int productIndex;
    int found = 0;

    printf("Input Product ID:");
    productid = getLong();

    for (int i = 0; i < cartItemCount; i++)
    {
        if (productid == cart[i].productid)
        {
            found = 1;
            cartProductIndex = i;
            i = cartItemCount;
        }

    }

    if (found == 0)
    {
        printf("Product ID not found! Returning to buy menu\n");
        return;
    }

    for (int i = 0; i < userCount; i++)
    {
        for (int j = 0; j < users[i].userItemCount; j++)
        {
            if (productid == users[i].items[j].productid)
            {
                userIndex = i;
                i = userCount;
                j = 20;
            }
        }
    }

    for (int i = 0; i < users[userIndex].userItemCount; i++)
    {
        if (users[userIndex].items[i].productid == productid)
        {
            userProductIndex = i;
            i = userCount;
        }

    }

    for (int i = 0; i < itemCount; i++)
    {
        if (productid == items[i].productid)
        {
            productIndex = i;
            i = itemCount;
        }
    }

    transactions[0].buyerid = userid;
    transactions[0].sellerid = cart[cartProductIndex].sellerid;
    transactions[0].month = month;
    transactions[0].day = day;
    transactions[0].year = year;
    transactions[0].total = cart[cartProductIndex].quantity * cart[cartProductIndex].price;

    transactions[0].items[0].sellerid = cart[cartProductIndex].sellerid;
    transactions[0].items[0].productid = cart[cartProductIndex].productid;
    strcpy(transactions[0].items[0].name, cart[cartProductIndex].name);
    strcpy(transactions[0].items[0].category, cart[cartProductIndex].category);
    strcpy(transactions[0].items[0].description, cart[cartProductIndex].description);
    transactions[0].items[0].quantity = cart[cartProductIndex].quantity;
    transactions[0].items[0].price = cart[cartProductIndex].price;

    users[userIndex].items[userProductIndex].quantity -= cart[cartProductIndex].quantity;
    items[productIndex].quantity -= cart[cartProductIndex].quantity;
    cart[cartProductIndex].quantity = 0;

    printf("Transaction Summary\n");
    printf("Quantity\t\t Product ID\t\t Item Name\t\t Unit Price\t\t Total Price of Item\n");
    printf("%ld %ld %s %lf %lf ", transactions[0].items[0].quantity, productid, transactions[0].items[0].name, transactions[0].items[0].price, transactions[0].total);

    printf("Total Amount Due: %lf\n", transactions[0].total);
    printf("Paid to: %ld %s\n", transactions[0].sellerid, users[userIndex].name);

    writeTransactionItems(1);
    writeTransactions(transactions, 1);

}

int checkCartItem(struct item items[], struct item cart[], int cartItemIndex, int itemIndex)
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
        printf("Price in cart: %lf\n", cart[cartItemIndex].price);
        printf("Price in items: %lf\n", items[itemIndex].price);
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
                *proceed = checkCartItem(items, cart, i, j);
                cartItemCount = sortCart(cart, cartItemCount);
            }

        }
    }

    return cartItemCount;

}

int checkoutMenu(struct user users[], long userid, int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount)
{
    int choice = 0;
    long month;
    long day;
    long year;
    int proceed = 1;

    printf("\n");
    cartItemCount = cartIntegrityCheck(items, itemCount, cart, cartItemCount, &proceed);
    cartItemCount = sortCart(cart, cartItemCount);

    if (proceed == 0)
    {
        printf("Please change the quantity of the products above or remove them before proceeding to checkout\n\n");
    }

    printf("Input month [mm]:");
    do
    {
        month = getLong();
        if (month < 1 || month > 12)
            printf("Please input a valid month:");
    }
    while(month < 1 || month > 12);
    printf("Input day [dd]:");
    do
    {
        day = getLong();
    }
    while(day < 1 || day > 31);
    printf("Input year [yyyy]:");
    do
    {
        year = getLong();
    }
    while(year < 0);

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
                checkoutAll(users, userid, userCount, items, itemCount, cart, cartItemCount, month, day, year);
                cartItemCount = sortCart(cart, cartItemCount);
                break;
            case 2:
               checkoutBySeller(users, userid, userCount, items, itemCount, cart, cartItemCount, month, day, year);
                cartItemCount = sortCart(cart, cartItemCount);
                break;
            case 3:
                checkoutByItem(users, userid, userCount, items, itemCount, cart, cartItemCount, month, day, year);
                cartItemCount = sortCart(cart, cartItemCount);
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
