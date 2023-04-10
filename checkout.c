//This file contains the functions for the checkout menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

/* checkoutAll checks out all items found in the cart
 * @users[] - array of users
 * @userid - id belonging to user
 * @userCount - number of users
 * @items[] - array of items
 * @itemCount - number of items
 * @cart[] - array of items belong to user
 * @cartItemCount - number of items in cart
 * @month - month
 * @day - day
 * @yar - year
 */
void checkoutAll(struct user users[], long userid, int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount, int month, int day, int year)
{
    struct transaction transactions[10];
    long productid;
    long sellers[10]; // sellers to print
    int sellerCount = 0;
    int cartProductIndex; // index of product in cart
    int userIndex; // index of user
    int userProductIndex; // index of user product
    int productIndex; // index of item
    int totalTransactions; // total number of transactions
    int totalTransactionItemCount; // total number of transacted items
    int transactionItemCount; // index of transaction item
    int found;
    int ctr;
    int sellerProducts;

    for (int i = 0; i < cartItemCount; i++) // store all seller id to sellers array
    {
        sellers[i] = cart[i].sellerid;
        sellerCount++;
    }

    for (int i = 0; i < sellerCount; i++) // remove duplicate seller id
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

    for (int i = 0; i < sellerCount; i++) // iterate through seller id for transactions
    {
        ctr = 0; // ctr of transaction
        sellerProducts = 0; // ctr of each item corresponding to seller id
        found = 0;

        for (int j = 0; j < 10; j++) // initialize total to zero to prevent undefined read
        {
            transactions[j].total = 0;
        }

        for (int j = 0; j < cartItemCount; j++) // search through entire cart
        {

            if (sellers[i] == cart[j].sellerid) // if sellerid corresponds to item then it belongs to the seller
            {
                productid = cart[j].productid;
                cartProductIndex = j;
                found = 1;
            }

            if (found == 1) // transact item if it has been found
            {
                for (int k = 0; k < userCount; k++) // find item in users
                {
                    for (int l = 0; l < users[k].userItemCount; l++)
                    {
                        if (productid == users[k].items[l].productid)
                        {
                            userIndex = k;
                            k = userCount;
                            l = 20;
                        }
                    }
                }

                for (int k = 0; k < users[userIndex].userItemCount; k++) // find number of items of user
                {
                    if (users[userIndex].items[k].productid == productid)
                    {
                        userProductIndex = k;
                        k = 20;
                    }
                }

                for (int k = 0; k < itemCount; k++) // find item in items
                {
                    if (productid == items[k].productid)
                    {
                        productIndex = k;
                        k = itemCount;
                    }
                }
                // store in transactions array the information of the transaction and item transacted
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

                // remove quantity from cart in items and set cart item quantity to zero
                users[userIndex].items[userProductIndex].quantity -= cart[cartProductIndex].quantity;
                items[productIndex].quantity -= cart[cartProductIndex].quantity;
                cart[cartProductIndex].quantity = 0;
                sellerProducts++;
                found = 0;
                if (sellerProducts == 5) // if number of items transacted is already 5 then next item will be in next transaction
                {
                    ctr++;
                    sellerProducts = 0;
                }

            }

        }

        totalTransactionItemCount = ctr*5+sellerProducts; // determine number of items transacted
        totalTransactions = totalTransactionItemCount / 5; // determine number of transactions

        if (totalTransactions == 0) // items transacted must be less than 5
        {
            totalTransactions = 1;
            transactionItemCount = totalTransactionItemCount % 5; // then items transacted must be a remainder
        }
        else if (totalTransactions == 1) // items transacted must be equal to 5 or greater
        {
            if (totalTransactionItemCount % 5 == 0) // items transacted is 5
            {
                transactionItemCount = 5;
            }
            else // items transacted is greater than 5
            {
                totalTransactions = 2;
                transactionItemCount = 5;
            }
        }
        else // items transacted must be equal to 10
        {
            totalTransactions = 2;
            transactionItemCount = 5;
        }

        for (int k = 0; k < totalTransactions; k++)
        {
            if (k == 1) // if i = 1 then items transacted must be greater than 5
                if (totalTransactionItemCount % 5 != 0) // then next transaction must be a remainder of 5
                    transactionItemCount = totalTransactionItemCount % 5;

            printf("\nTransaction Summary\n");
            printf("--------------------------------------------------------------------------------------------\n");
            printf("|  Quantity  | Product ID |       Item Name       |    Unit Price    | Total Price of Item |\n");
            printf("--------------------------------------------------------------------------------------------\n");

            for (int l = 0; l < transactionItemCount; l++)
            {
                printf("| %10ld | %10ld | %-21s | %16lf | %19lf |\n", transactions[k].items[l].quantity, transactions[k].items[l].productid, transactions[k].items[l].name, transactions[k].items[l].price, transactions[k].items[l].quantity * transactions[k].items[l].price);
                printf("--------------------------------------------------------------------------------------------\n");
            }
            printf("\nTotal Amount Due: %lf\n", transactions[k].total);
            printf("Paid to: %ld %s\n", transactions[k].sellerid, users[userIndex].name);
        }

        for (int k = 0; k <= ctr; k++) // determine dimensions of transactions and items array inside
        {
            if (ctr > 0 && k < ctr) // items transacted must be greater than 5 if ctr is greater than 1
            {
                writeTransactionItems(5);
            } else
                writeTransactionItems(sellerProducts);

        }

        writeTransactions(transactions, ctr * 5 + sellerProducts); // write transactions to file

    }


}

/* checkoutBySeller checks out all items corresponding to seller id inputted
 * @users[] - array of users
 * @userid - id belonging to user
 * @userCount - number of users
 * @items[] - array of items
 * @itemCount - number of items
 * @cart[] - array of items belong to user
 * @cartItemCount - number of items in cart
 * @month - month
 * @day - day
 * @yar - year
 */
void checkoutBySeller(struct user users[], long userid, int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount, int month, int day, int year)
{
    struct transaction transactions[10];
    long productid;
    long sellerid;
    int cartProductIndex; // index of product in cart
    int userIndex; // index of user
    int userProductIndex; // index of user product
    int productIndex; // index of item
    int totalTransactions; // total number of transactions
    int totalTransactionItemCount; // total number of transacted items
    int transactionItemCount; // index of transaction item
    int found = 0;
    int ctr = 0;
    int sellerProducts = 0;

    printf("Input Seller ID:");
    do
    {
        sellerid = getLong();
        if (sellerid < 1)
            printf("Please input a positive number:");
    }
    while (sellerid < 1); // repeat prompt until user enters a positive number

    for (int i = 0; i < cartItemCount; i++)
    {
        if (sellerid == cart[i].sellerid)
        {
            found = 1;
        }

    }

    if (found == 0) // return if seller id is not found in cart
    {
        printf("Seller Id not found! Returning to checkout menu\n");
        return;
    }

    for (int i = 0; i < 10; i++) // initialize total to zero to prevent undefined read
    {
        transactions[i].total = 0;
    }

    found = 0;
    for (int i = 0; i < cartItemCount; i++) // search through entire cart
    {
        if (sellerid == cart[i].sellerid) // if sellerid corresponds to item then it belongs to the seller
        {
            productid = cart[i].productid;
            cartProductIndex = i;
            found = 1;
        }

        if (found == 1) // transact item if it has been found
        {
            for (int j = 0; j < userCount; j++) // find item in users
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

            for (int j = 0; j < users[userIndex].userItemCount; j++) // find number of items of user
            {
                if (users[userIndex].items[j].productid == productid)
                {
                    userProductIndex = j;
                    j = 20;
                }
            }

            for (int j = 0; j < itemCount; j++) // find item in items
            {
                if (productid == items[j].productid)
                {
                    productIndex = j;
                    j = itemCount;
                }
            }
            // store in transactions array the information of the transaction and item transacted
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

            // remove quantity from cart in items and set cart item quantity to zero
            users[userIndex].items[userProductIndex].quantity -= cart[cartProductIndex].quantity;
            items[productIndex].quantity -= cart[cartProductIndex].quantity;
            cart[cartProductIndex].quantity = 0;
            sellerProducts++;
            found = 0;
            if (sellerProducts == 5) // if number of items transacted is already 5 then next item will be in next transaction
            {
                ctr++;
                sellerProducts = 0;


            }

        }

    }

    totalTransactionItemCount = ctr*5+sellerProducts; // determine number of items transacted
    totalTransactions = totalTransactionItemCount / 5; // determine number of transactions

    if (totalTransactions == 0) // items transacted must be less than 5
    {
        totalTransactions = 1;
        transactionItemCount = totalTransactionItemCount % 5; // then items transacted must be a remainder
    }
    else if (totalTransactions == 1) // items transacted must be equal to 5 or greater
    {
        if (totalTransactionItemCount % 5 == 0) // items transacted is 5
        {
            transactionItemCount = 5;
        }
        else // items transacted is greater than 5
        {
            totalTransactions = 2;
            transactionItemCount = 5;
        }
    }
    else // items transacted must be equal to 10
    {
        totalTransactions = 2;
        transactionItemCount = 5;
    }

    for (int i = 0; i < totalTransactions; i++)
    {
        if (i == 1) // if i = 1 then items transacted must be greater than 5
            if (totalTransactionItemCount % 5 != 0) // then next transaction must be a remainder of 5
                transactionItemCount = totalTransactionItemCount % 5;

        printf("\nTransaction Summary\n");
        printf("--------------------------------------------------------------------------------------------\n");
        printf("|  Quantity  | Product ID |       Item Name       |    Unit Price    | Total Price of Item |\n");
        printf("--------------------------------------------------------------------------------------------\n");

        for (int j = 0; j < transactionItemCount; j++)
        {
            printf("| %10ld | %10ld | %-21s | %16lf | %19lf |\n", transactions[i].items[j].quantity, transactions[i].items[j].productid, transactions[i].items[j].name, transactions[i].items[j].price, transactions[i].items[j].quantity * transactions[i].items[j].price);
            printf("--------------------------------------------------------------------------------------------\n");
        }
        printf("\nTotal Amount Due: %lf\n", transactions[i].total);
        printf("Paid to: %ld %s\n", transactions[i].sellerid, users[userIndex].name);
    }

    for (int i = 0; i <= ctr; i++) // determine dimensions of transactions and items array inside
    {
        if (ctr > 0 && i < ctr) // items transacted must be greater than 5 if ctr is greater than 1
        {
            writeTransactionItems(5);
        }
        else
            writeTransactionItems(sellerProducts);

    }

    writeTransactions(transactions, ctr*5+sellerProducts); // write transactions to file


}

/* checkoutByItem checks out an item corresponding to product id inputted
 * @users[] - array of users
 * @userid - id belonging to user
 * @userCount - number of users
 * @items[] - array of items
 * @itemCount - number of items
 * @cart[] - array of items belong to user
 * @cartItemCount - number of items in cart
 * @month - month
 * @day - day
 * @yar - year
 */
void checkoutByItem(struct user users[], long userid, int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount, int month, int day, int year)
{
    struct transaction transactions[10];
    long productid;
    int cartProductIndex; // index of product in cart
    int userIndex; // index of user
    int userProductIndex; // index of user product
    int productIndex; // index of item
    int found = 0;

    printf("Input Product ID:");
    do
    {
        productid = getLong();
        if (productid < 1)
            printf("Please input a positive number:");
    }
    while (productid < 1); // repeat prompt until user enters a positive number

    for (int i = 0; i < cartItemCount; i++)
    {
        if (productid == cart[i].productid) {
            found = 1;
            cartProductIndex = i;
            i = cartItemCount;
        }

    }

    if (found == 0) // return if product not found in cart
    {
        printf("Product ID not found! Returning to buy menu\n");
        return;
    }

    for (int i = 0; i < userCount; i++) // find item in users
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

    for (int i = 0; i < users[userIndex].userItemCount; i++) // find number of items of user
    {
        if (users[userIndex].items[i].productid == productid)
        {
            userProductIndex = i;
            i = userCount;
        }

    }

    for (int i = 0; i < itemCount; i++) // find item in items
    {
        if (productid == items[i].productid)
        {
            productIndex = i;
            i = itemCount;
        }
    }
    // store in transactions array the information of the transaction and item transacted
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

    // remove quantity from cart in items and set cart item quantity to zero
    users[userIndex].items[userProductIndex].quantity -= cart[cartProductIndex].quantity;
    items[productIndex].quantity -= cart[cartProductIndex].quantity;
    cart[cartProductIndex].quantity = 0;

    printf("\nTransaction Summary\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("|  Quantity  | Product ID |       Item Name       |    Unit Price    | Total Price of Item |\n");
    printf("--------------------------------------------------------------------------------------------\n");
    printf("| %10ld | %10ld | %-21s | %16lf | %19lf |\n", transactions[0].items[0].quantity, productid, transactions[0].items[0].name, transactions[0].items[0].price, transactions[0].total);
    printf("--------------------------------------------------------------------------------------------\n");
    printf("Total Amount Due: %lf\n", transactions[0].total);
    printf("Paid to: %ld %s\n", transactions[0].sellerid, users[userIndex].name);

    writeTransactionItems(1); // determine dimensions of transactions and items inside
    writeTransactions(transactions, 1);

}

/* checkCartItem checks if any modification has been made to the item and changes it accordingly
 * @items[] - array of items
 * @cart[] - array of items belong to user
 * @cartItemIndex - index of cart item
 * @itemIndex - index of item
 */
int checkCartItem(struct item items[], struct item cart[], int cartItemIndex, int itemIndex)
{
    int proceed = 1;

    if (strcmp(cart[cartItemIndex].name, items[itemIndex].name) != 0) // inform user of name change
    {
        printf("Name of product in cart has changed!\n");
        printf("Name in cart: %s\n", cart[cartItemIndex].name);
        printf("Name in items: %s\n", items[itemIndex].name);
        printf("Changing name...\n\n");

        strcpy(cart[cartItemIndex].name, items[itemIndex].name);
    }

    if (strcmp(cart[cartItemIndex].category, items[itemIndex].category) != 0) // inform user of category change
    {
        printf("Category of product in cart has changed!\n");
        printf("Category in cart: %s\n", cart[cartItemIndex].category);
        printf("Category in items: %s\n", items[itemIndex].category);
        printf("Changing category...\n\n");

        strcpy(cart[cartItemIndex].category, items[itemIndex].category);
    }

    if (strcmp(cart[cartItemIndex].description, items[itemIndex].description) != 0) // inform user of description change
    {
        printf("Description of product in cart has changed!\n");
        printf("Description in cart: %s\n", cart[cartItemIndex].description);
        printf("Description in items: %s\n", items[itemIndex].description);
        printf("Changing description...\n\n");

        strcpy(cart[cartItemIndex].description, items[itemIndex].description);
    }

    if (cart[cartItemIndex].quantity > items[itemIndex].quantity && items[itemIndex].quantity > 0) // inform user of quantity change and change quantity if item quantity is greater than what's available
    {
        printf("Unfortunately, the currently selected quantity for this item is no longer available.\n");
        printf("Please edit the quantity before proceeding to checkout...\n");
        printf("Quantity in cart: %ld\n", cart[cartItemIndex].quantity);
        printf("Available quantity: %ld\n", items[itemIndex].quantity);
        printf("Setting quantity to what's available..........Done!\n\n");
        cart[cartItemIndex].quantity = items[itemIndex].quantity;
        proceed = 0;
    }
    else if (cart[cartItemIndex].quantity > items[itemIndex].quantity && items[itemIndex].quantity <= 0) // remove item from cart if it is out of stock
    {
        printf("Unfortunately, this item is no longer available.\n");
        printf("Removing item from cart..........Done!\n\n");
        cart[cartItemIndex].quantity = 0;
    }

    if (cart[cartItemIndex].price != items[itemIndex].price) // inform user of price change
    {
        printf("Price of product in cart has changed!\n");
        printf("Price in cart: %lf\n", cart[cartItemIndex].price);
        printf("Price in items: %lf\n", items[itemIndex].price);
        printf("Changing price...\n\n");

        cart[cartItemIndex].price = items[itemIndex].price;

    }

    return proceed;
}

/* cartIntegrityCheck checks integrity of cart by comparing it to items array
 * @items[] - array of items
 * @itemCount - number of items
 * @cartItemIndex - index of cart item
 * @cartItemCount - number of items in cart
 * @*proceed - 1 if item has been modified, 0 if not
 * @return cartItemCount, the number of items in the cart after modification
 */
int cartIntegrityCheck(struct item items[], int itemCount, struct item cart[], int cartItemCount, int* proceed)
{
    long productid;
    int ctr = cartItemCount;

    for (int i = 0; i < ctr; i++) // search for item in cart in items array
    {
        productid = cart[i].productid;
        for (int j = 0; j < itemCount; j++)
        {
            if (productid == items[j].productid) // check item in cart against item in items array
            {
                printf("Checking availability of product: %s..........Done!\n\n", cart[i].name);
                *proceed = checkCartItem(items, cart, i, j);

            }

        }
    }

    cartItemCount = sortCart(cart, cartItemCount); // sort cart if any item has been removed
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
    cartItemCount = cartIntegrityCheck(items, itemCount, cart, cartItemCount, &proceed); // check for any changes in items before proceeding
    cartItemCount = sortCart(cart, cartItemCount); // sort cart if any items have been removed

    if (proceed == 0)
    {
        printf("Please change the quantity of the products above or remove them before proceeding to checkout\n\n");
    }

    do
    {
        printf("Please input a valid date for the transaction:\n");
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
            if (day < 1 || day > 31)
                printf("Please input a valid day:");
        }
        while(day < 1 || day > 31);
        printf("Input year [yyyy]:");
        do
        {
            year = getLong();
            if (year < 0)
                printf("Please input a valid year:");
        }
        while(year < 0);
    }
    while (checkValidDate(month, day, year) == 0); // repeat prompt until user enters a valid date

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
                if (cartItemCount == 0)
                {
                    printf("Please add an item to cart first!\n");
                }
                else
                {
                    checkoutAll(users, userid, userCount, items, itemCount, cart, cartItemCount, month, day, year);
                    cartItemCount = sortCart(cart, cartItemCount);
                }
                break;
            case 2:
                if (cartItemCount == 0)
                {
                    printf("Please add an item to cart first!\n");
                }
                else
                {
                    checkoutBySeller(users, userid, userCount, items, itemCount, cart, cartItemCount, month, day, year);
                    cartItemCount = sortCart(cart, cartItemCount);
                }
                break;
            case 3:
                if (cartItemCount == 0)
                {
                    printf("Please add an item to cart first!\n");
                }
                else
                {
                    checkoutByItem(users, userid, userCount, items, itemCount, cart, cartItemCount, month, day, year);
                    cartItemCount = sortCart(cart, cartItemCount);
                }
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
