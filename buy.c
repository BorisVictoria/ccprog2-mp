//This file contains the functions for the buy menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void viewAllProducts(struct user users[], int userCount)
{
    char choice = '\0';
    int exit = 0;
    int userIndex = 0;
    int userItemCount;

    while (users[userIndex].userItemCount == 0)
    {
        userIndex++;
        if (userIndex >= userCount)
            userIndex = 0;
    }

    while (exit == 0)
    {
        printf("\nAll Products\n\n");
        printf("------------------------------------------------------------------------------------------------------\n");
        printf("| Seller ID  | Product ID |       Item Name       |     Category     |  Quantity  |    Unit Price    |\n");
        printf("------------------------------------------------------------------------------------------------------\n");
        userItemCount = users[userIndex].userItemCount;

        for (int i = 0; i < userItemCount; i++)
        {
            printf("| %10ld | %10ld | %-21s | %-16s | %10ld | %16lf |\n", users[userIndex].userid, users[userIndex].items[i].productid, users[userIndex].items[i].name, users[userIndex].items[i].category, users[userIndex].items[i].quantity, users[userIndex].items[i].price);
            printf("------------------------------------------------------------------------------------------------------\n");
        }

        printf("[N] Next Seller [X] Exit:");
        getString(&choice, 1);

        if (choice == 'N' || choice == 'n')
        {
            userIndex++;
            if (userIndex >= userCount)
                userIndex = 0;

            while (users[userIndex].userItemCount == 0)
            {
                    userIndex++;
                    if (userIndex >= userCount)
                    userIndex = 0;
            }

        }
        else if (choice == 'X' || choice == 'x')
            exit = 1;
        else
            printf("Invalid input! Please try again\n");

    }

}

void showProductBySeller(struct user users[], int userCount)
{
    long sellerid;
    int userIndex;
    int found = 0;

    printf("Enter sellerid to search:");
    do
    {
        sellerid = getLong();
        if (sellerid < 1)
            printf("Please input a positive number");
    }
    while (sellerid < 1);
    for (int i = 0; i < userCount; i++)
    {
        if (users[i].userid == sellerid)
        {
            found = 1;
            userIndex = i;
            i = userCount;
        }
    }

    if (found != 1)
    {
        printf("Seller ID not found! Returning to buy menu\n");
        return;
    }

    printf("\nSeller ID: %ld\n\n", sellerid);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| Product ID |       Item Name       |     Category     |  Quantity  |    Unit Price    |\n");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < users[userIndex].userItemCount; i++)
    {
        printf("| %10ld | %-21s | %-16s | %10ld | %16lf |\n", users[userIndex].items[i].productid, users[userIndex].items[i].name, users[userIndex].items[i].category, users[userIndex].items[i].quantity, users[userIndex].items[i].price);
        printf("-----------------------------------------------------------------------------------------\n");
    }

}

void showProductByCategory(struct item items[], int itemCount)
{
    char choice = '\0';
    int exit = 0;
    int productIndex = 0;
    int found;
    int loop = 0;

    char category[16];
    printf("Enter category to search:");
    getString(category, 15);

    while (exit == 0)
    {
        found = 0;
        for (int i = productIndex; i < itemCount; i++)
        {

            if (strcmp(items[i].category, category) == 0)
            {
                found = 1;
                loop = 1;
                productIndex = i;
                i = itemCount;
            }
            else if (i == itemCount-1 && loop == 1)
            {
                i = -1;
            }
        }

        if (found == 1)
        {
            printf("\nProducts by Category\n\n");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
            printf("| Product ID |       Item Name       |     Category     |           Description           |  Quantity  |    Unit Price    |\n");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %10ld | %-21s | %-16s | %-31s | %10ld | %16lf |\n", items[productIndex].productid, items[productIndex].name, items[productIndex].category, items[productIndex].description, items[productIndex].quantity, items[productIndex].price);
            printf("---------------------------------------------------------------------------------------------------------------------------\n");

            printf("[N] Next Item [X] Exit:");
            getString(&choice, 1);

            if (choice == 'N' || choice == 'n')
            {
                productIndex++;
                if (productIndex >= itemCount)
                    productIndex = 0;
            }

            else if (choice == 'X' || choice == 'x')
                exit = 1;
            else
                printf("Invalid input! Please try again\n");

        }
        else
        {
            printf("No item with that category! Returning to buy menu\n");
            exit = 1;
        }

    }
}

void showProductByName(struct item items[], int itemCount)
{
    char choice = '\0';
    int exit = 0;
    int productIndex = 0;
    int found;
    int loop = 0;

    char name[21];
    printf("Enter product name to search:");
    getString(name, 20);

    while (exit == 0)
    {
        found = 0;
        for (int i = productIndex; i < itemCount; i++)
        {

            if (strstr(items[i].name, name) != NULL)
            {
                found = 1;
                loop = 1;
                productIndex = i;
                i = itemCount;
            }
            else if (i == itemCount-1 && loop == 1)
            {
                i = -1;
            }
        }

        if (found == 1)
        {
            printf("\nProducts by Name\n\n");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
            printf("| Product ID |       Item Name       |     Category     |           Description           |  Quantity  |    Unit Price    |\n");
            printf("---------------------------------------------------------------------------------------------------------------------------\n");
            printf("| %10ld | %-21s | %-16s | %-31s | %10ld | %16lf |\n", items[productIndex].productid, items[productIndex].name, items[productIndex].category, items[productIndex].description, items[productIndex].quantity, items[productIndex].price);
            printf("---------------------------------------------------------------------------------------------------------------------------\n");

            printf("\n[N] Next Item [X] Exit:");
            getString(&choice, 1);

            if (choice == 'N' || choice == 'n')
            {
                productIndex++;
                if (productIndex >= itemCount)
                    productIndex = 0;
            }

            else if (choice == 'X' || choice == 'x')
                exit = 1;
            else
                printf("Invalid input! Please try again\n");

        }
        else
        {
            printf("No item with that name! Returning to buy menu\n");
            exit = 1;
        }

    }
}

int addToCart(struct item items[], int itemCount, struct item cart[], int cartItemCount, long userid)
{
    long productid;
    long quantity;
    char choice = '\0';
    int found = 0;
    int productIndex;
    int success = 0;

    printf("Product ID:");
    do
    {
        productid = getLong();
        if (productid < 1)
        printf("Please input a positive number:");
    }
    while (productid < 1);

    for (int i = 0; i < itemCount; i++)
    {
        if (productid == items[i].productid)
        {
            productIndex = i;
            found = 1;
            i = itemCount;
        }
    }

    if (found == 0)
    {
        printf("Product ID not found! Returning to buy menu\n");
        return success;
    }

    if (items[productIndex].sellerid == userid)
    {
        printf("You cannot buy your own product! Returning to buy menu\n");
        return success;
    }

    if (items[productIndex].quantity == 0)
    {
        printf("Product is out of stock! Returning to buy menu\n");
        return success;
    }

    for (int i = 0; i < cartItemCount; i++)
    {
        if (productid == cart[i].productid)
        {
            printf("Product already exists in cart! Returning to buy menu\n");
            return success;
        }
    }

    printf("Number of items in stock: %ld\n", items[productIndex].quantity);
    printf("Input quantity to add to cart:");
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
    while(quantity <= 0 || items[productIndex].quantity < quantity);
    printf("\nQuantity:%ld\n", quantity);

    printf("Confirm adding item to cart [Y]/[N]:");
    getString(&choice, 1);

    if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')
    {
        if (choice == 'Y' || choice == 'y')
        {
            success = 1;
        }
        else
        {
            printf("Returning to menu\n");

        }
    }
    else
    {
        printf("Unrecognized option, returning to menu\n");
    }

    if (success == 1)
    {

        cart[cartItemCount].sellerid = items[productIndex].sellerid;
        cart[cartItemCount].productid = items[productIndex].productid;
        strcpy(cart[cartItemCount].name, items[productIndex].name);
        strcpy(cart[cartItemCount].category, items[productIndex].category);
        strcpy(cart[cartItemCount].description, items[productIndex].description);
        cart[cartItemCount].quantity = quantity;
        cart[cartItemCount].price = items[productIndex].price;

    }

    return success;

}

void buyMenu(struct user users[], int userIndex, int userCount, struct item items[], int itemCount)
{
    int choice = 0;
    long userid;
    struct item cart[10];
    int cartItemCount;
    int cartItemAdded;
    int proceed = 1;

    printf("\n");
    userid = users[userIndex].userid;
    cartItemCount = readCart(cart, userid);

    cartItemCount = cartIntegrityCheck(items, itemCount, cart, cartItemCount, &proceed);
    cartItemCount = sortCart(cart, cartItemCount);

    if (proceed == 0)
    {
        printf("Please change the quantity of the products above or remove them before proceeding to checkout\n");
    }

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
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n");
                else
                    viewAllProducts(users, userCount);
                break;
            case 2:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n");
                else
                    showProductBySeller(users, userCount);
                break;
            case 3:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n");
                else
                    showProductByCategory(items, itemCount);
                break;
            case 4:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n");
                else
                    showProductByName(items, itemCount);
                break;
            case 5:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n");
                else if (cartItemCount >= 10)
                    printf("Maximum number of items in cart! Please remove an item first");
                else
                    cartItemAdded = addToCart(items, itemCount, cart, cartItemCount, userid);
                    if (cartItemAdded == 1)
                    {
                        cartItemCount++;
                        cartItemCount = sortCart(cart, cartItemCount);
                    }
                break;
            case 6:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n");
                else if (cartItemCount == 0)
                    printf("No items in cart! Please add an item first\n");
                else
                    cartItemCount = editCartMenu(cart, cartItemCount, items, itemCount);
                break;
            case 7:
                if (itemCount == 0)
                    printf("No items found! Please add an item first\n");
                else if (cartItemCount == 0)
                    printf("No items in cart! Please add an item first\n");
                else
                    cartItemCount = checkoutMenu(users, userid, userCount, items, itemCount, cart, cartItemCount);
                break;
            case 8:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }
    }

    writeCart(cart, cartItemCount, userid);

}


