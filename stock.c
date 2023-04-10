//This file contains the functions for the edit stock menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

/* replenish adds quantity to item
 * @users[] - array of users
 * @userIndex - index of user
 * @userProductIndex - index of user product
 * @items[] - array of items
 * @productIndex - index of product
*/
void replenish(struct user users[], int userIndex, int userProductIndex, struct item items[], int productIndex)
{
    long quantity;
    char choice = '\0';
    int success = 0;

    printf("Input quantity to add:");
    do
    {
        quantity = getLong();
        if (quantity < 1)
            printf("Please input a positive quantity:");
    }
    while (quantity < 1); // repeat prompt until user enters a positive number
    printf("\nQuantity:%ld\n", quantity);

    printf("Confirm amount added [Y]/[N]:");
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

    if (success == 1) // add quantity to item if user says yes
    {
        printf("\nAmount added!\n");
        users[userIndex].items[userProductIndex].quantity += quantity;
        items[productIndex].quantity += quantity;
        printf("New quantity:%ld\n", users[userIndex].items[userProductIndex].quantity);
    }
}

/* changePrice changes price of item
 * @users[] - array of users
 * @userIndex - index of user
 * @userProductIndex - index of user product
 * @items[] - array of items
 * @productIndex - index of product
*/
void changePrice(struct user users[], int userIndex, int userProductIndex, struct item items[], int productIndex)
{
    double price;
    char choice = '\0';
    int success = 0;

    printf("Input new price:");
    do
    {
        price = getDouble();
        if (price <= 0)
            printf("Please input a positive price:");
    }
    while (price <= 0); // repeat prompt until user enters a positive double number
    printf("\nPrice:%lf\n", price);

    printf("Confirm new price [Y]/[N]:");
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

    if (success == 1) // change price if user says yes
    {
        printf("\nPrice changed!\n");
        users[userIndex].items[userProductIndex].price = price;
        items[productIndex].price = price;
        printf("New price:%lf\n", users[userIndex].items[userProductIndex].price);

    }

}

/* changeItemName changes name of item
 * @users[] - array of users
 * @userIndex - index of user
 * @userProductIndex - index of user product
 * @items[] - array of items
 * @productIndex - index of product
*/
void changeItemName(struct user users[], int userIndex, int userProductIndex, struct item items[], int productIndex)
{
    char name[21];
    char choice = '\0';
    int success = 0;

    printf("Input new name:");
    getString(name, 21);
    printf("\nName:%s\n", name);

    printf("Confirm new name [Y]/[N]:");
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

    if (success == 1) // change name if user says yes
    {
        printf("\nItem name changed!\n");
        strcpy(users[userIndex].items[userProductIndex].name, name);
        strcpy(items[productIndex].name, name);
        printf("New name:%s\n", users[userIndex].items[userProductIndex].name);
    }

}

/* changeCategory changes category of item
 * @users[] - array of users
 * @userIndex - index of user
 * @userProductIndex - index of user product
 * @items[] - array of items
 * @productIndex - index of product
*/
void changeCategory(struct user users[], int userIndex, int userProductIndex, struct item items[], int productIndex)
{
    char category[16];
    char choice = '\0';
    int success = 0;

    printf("Input new category:");
    getString(category,16);
    printf("\nCategory:%s\n", category);

    printf("Confirm new category [Y]/[N]:");
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

    if (success == 1) // change category if user says yes
    {
        printf("\nItem category changed!\n");
        strcpy(users[userIndex].items[userProductIndex].category, category);
        strcpy(items[productIndex].category, category);
        printf("New category:%s\n", users[userIndex].items[userProductIndex].category);
    }

}

/* changeDescription changes description of item
 * @users[] - array of users
 * @userIndex - index of user
 * @userProductIndex - index of user product
 * @items[] - array of items
 * @productIndex - index of product
*/
void changeDescription(struct user users[], int userIndex, int userProductIndex, struct item items[], int productIndex)
{
    char description[31];
    char choice = '\0';
    int success = 0;

    printf("Input Description:");
    getString(description, 31);
    printf("\nDescription:%s\n", description);

    printf("Confirm new description [Y]/[N]:");
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

    if (success == 1) // change description if user says yes
    {
        printf("\nItem description changed!\n");
        strcpy(users[userIndex].items[userProductIndex].description, description);
        strcpy(items[productIndex].description, description);
        printf("New description:%s\n", users[userIndex].items[userProductIndex].description);
    }

}

void editStockMenu(struct user users[], int userIndex, int userItemCount, struct item items[], int itemCount) {

    long productid;
    int userProductIndex = 0;
    int productIndex = 0;
    int found = 0;
    int choice = 0;

    showMyProducts(users, userIndex, userItemCount);

    printf("\nProduct ID:");
    do
    {
        productid = getLong();
        if (productid < 1)
            printf("Please input a positive number");
    }
    while (productid < 1); // repeat prompt until user enters a positive number

    for (int i = 0; i < userItemCount; i++) // search for product in items
    {
        if (productid == users[userIndex].items[i].productid)
        {
            found = 1;
            userProductIndex = i;
            i = userItemCount;
        }
    }

    if (found == 0) // return if product is not found
    {
        printf("Product ID not found in User! Returning to sell menu\n");
        return;
    }

    found = 0;

    for (int i = 0; i < itemCount; i++)
    {
        if (productid == items[i].productid)
        {
            found = 1;
            productIndex = i;
            i = itemCount;
        }
    }

    if (found == 0) // return if product is not found
    {
        printf("Product ID not found in Items array! Returning to sell menu\n");
        return;
    }

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
                replenish(users, userIndex, userProductIndex, items, productIndex);
                break;
            case 2:
                changePrice(users, userIndex, userProductIndex, items, productIndex);
                break;
            case 3:
                changeItemName(users, userIndex, userProductIndex, items, productIndex);
                break;
            case 4:
                changeCategory(users, userIndex, userProductIndex, items, productIndex);
                break;
            case 5:
                changeDescription(users, userIndex, userProductIndex, items, productIndex);
                break;
            case 6:
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }
    }

}