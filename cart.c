//This file contains the functions for the edit cart menu and all associated features.
#include <stdio.h>
#include "structures.h"

/* removeItemsFromSeller removes items in cart corresponding to seller id inputted
 * @cart[] - array of items belonging to user
 * @cartItemCount - number of items in cart
*/
void removeItemsFromSeller(struct item cart[], int cartItemCount)
{
    long sellerid;
    int found = 0;

    printf("Enter Seller ID of items to remove:");
    do
    {
        sellerid = getLong();
        if (sellerid < 1)
            printf("Please input a positive number:");
    }
    while (sellerid < 1); // repeat prompt until user enters a positive number

    for (int i = 0; i < cartItemCount; i++)
    {
        if (cart[i].sellerid == sellerid)
        {
            found = 1;
            i = cartItemCount;
        }
    }

    if (found == 0) // return if seller is not found in items
    {
        printf("Seller ID not found! Returning to edit cart menu\n");
        return;
    }

    for (int i = 0; i < cartItemCount; i++) // set quantity to zero so item will get removed by sortCart()
    {
        if (sellerid == cart[i].sellerid)
            cart[i].quantity = 0;
    }
    printf("Items from seller removed from cart!\n");

}

/* removeSpecificItem removes item corresponding to product id inputted
 * @cart[] - array of items belonging to user
 * @cartItemCount - number of items in cart
*/
void removeSpecificItem(struct item cart[], int cartItemCount)
{
    long productid;
    int found = 0;

    printf("Enter Product ID of item to remove:");
    do
    {
        productid = getLong();
        if (productid < 1)
            printf("Please input a positive number:");
    }
    while (productid < 1); // repeat prompt until user enters a positive number

    for (int i = 0; i < cartItemCount; i++)
    {
        if (cart[i].productid == productid)
        {
            found = 1;
            i = cartItemCount;
        }
    }

    if (found == 0)
    {
        printf("Product ID not found! Returning to edit cart menu\n");
        return;
    }

    for (int i = 0; i < cartItemCount; i++) // set quantity to zero so item will get removed by sortCart()
    {
        if (productid == cart[i].productid)
            cart[i].quantity = 0;
    }
    printf("Item removed from cart!\n");

}

/* editQuantity edits the quantity of item in cart
 * @cart[] - array of items belonging to user
 * @cartItemCount - number of items in cart
 * @items[] - array of items
 * @itemCount - number of items
*/
void editQuantity(struct item cart[], int cartItemCount, struct item items[], int itemCount)
{
    long productid;
    long quantity;
    int found = 0;
    int productIndex;
    int cartProductIndex;

    printf("Enter Product ID of item to edit quantity:");
    do
    {
        productid = getLong();
        if (productid < 1)
            printf("Please input a positive number:");
    }
    while (productid < 1); // repeat prompt until user enters a positive number

    for (int i = 0; i < cartItemCount; i++)
    {
        if (cart[i].productid == productid)
        {
            found = 1;
            cartProductIndex = i;
            i = cartItemCount;
        }
    }

    if (found == 0) // return if product is not found in items
    {
        printf("Product ID not found! Returning to edit cart menu\n");
        return;
    }

    for (int i = 0; i < itemCount; i++)
    {
        if (productid == items[i].productid)
        {
            productIndex = i;
            i = itemCount;
        }
    }

    if (items[productIndex].quantity <= 0) // check to remove item if quantity is zero
    {
        printf("Product is out of stock! Removing from cart\n");
        cart[cartProductIndex].quantity = 0;
    }

    printf("Number of items in stock: %ld\n", items[productIndex].quantity);
    printf("Input new quantity:");
    do
    {
        quantity = getLong();
        if (quantity <= 0)
        {
            printf("Please input a positive quantity:");
        }
        else if (quantity > items[productIndex].quantity)
        {
            printf("Entered quantity is not available. Please try again:");
        }
    }
    while(quantity <= 0 || items[productIndex].quantity < quantity); // repeat prompt until user enters a positive number that is less than or equal to quantity available
    printf("\nProduct quantity changed!\n");
    printf("New Quantity:%ld\n", quantity);

    cart[cartProductIndex].quantity = quantity; // set quantity of item in cart

}

int editCartMenu(struct item cart[], int cartItemCount, struct item items[], int itemCount)
{
    int choice = 0;
    long sellers[10];
    int sellerCount = 0;

    printf("\nProducts in Cart\n");

    for (int i = 0; i < cartItemCount; i++) // determine number of items in cart
    {
        sellers[i] = cart[i].sellerid;
        sellerCount++;
    }

    for (int i = 0; i < sellerCount; i++) // store into sellers all non-duplicate seller id
    {
        for (int j = i+1; j < sellerCount; j++)
        {
            if (sellers[i] == sellers[j])
            {
                for (int k = j; k < sellerCount-1; k++)
                {
                    sellers[k] = sellers[k+1];
                }
                sellerCount--;
                j--;
            }
        }
    }

    for (int i = 0; i < sellerCount; i++) // iterate through seller id and print all their products by seller
    {
        printf("\nSeller ID: %ld\n", sellers[i]);
        printf("-----------------------------------------------------------------------------------------\n");
        printf("| Product ID |       Item Name       |     Category     |  Quantity  |    Unit Price    |\n");
        printf("-----------------------------------------------------------------------------------------\n");
        for (int j = 0; j < cartItemCount; j++)
        {
            if (sellers[i] == cart[j].sellerid)
            {
                printf("| %10ld | %-21s | %-16s | %10ld | %16lf |\n", cart[j].productid, cart[j].name, cart[j].category, cart[j].quantity, cart[j].price);
                printf("-----------------------------------------------------------------------------------------\n");
            }
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
                removeItemsFromSeller(cart, cartItemCount);
                cartItemCount = sortCart(cart, cartItemCount); // sort cart after removing item
                break;
            case 2:
                removeSpecificItem(cart, cartItemCount);
                cartItemCount = sortCart(cart, cartItemCount); // sort cart after removing item
                break;
            case 3:
                editQuantity(cart, cartItemCount, items, itemCount);
                cartItemCount = sortCart(cart, cartItemCount); // sort cart if item has been removed
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
