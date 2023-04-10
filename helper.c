//This file contains the input and helper functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "structures.h"

/* justSpaces checks if the input is just made of spaces
 * @param *string - pointer to character
 * @return 1 if input is just spaces
 * @return 0 if input has non-whitespace character
*/
int justSpaces(char *string)
{
    while (*string != '\0')
    {
        if (!isspace((unsigned char)*string)) // check if item is all spaces
            return 0;
        string++;
    }
    return 1;
}

/* getString gets string input
 * @param dest[] - character array to output to
 * @param destsize - size of destination array
*/
void getString(char dest[], int destsize)
{
    char buffer[1024]; // set buffer to 1024
    long len;
    int success;

    success = 0;
    while (success == 0) // repeat until successful
    {
        fgets(buffer, 1024, stdin); // get input from user
        buffer[strcspn(buffer, "\n")] = '\0'; // replace new line with null
        len = strlen(buffer); // get length of buffer
        if (len > destsize) // repeat prompt if user enters string greater than destination size
        {
            printf("Input too long! Please try again:");
        }
        else if (len == 0) // repeat prompt if users enters nothing
        {
            printf("Input cannot be empty! Please try again:");
        }
        else if (justSpaces(buffer) == 1) // repeat prompt if input is just spaces
        {
            printf("Input cannot be just spaces! Please try again:");
        }
        else // store input
        {
            success = 1;
        }

    }
    if (destsize > 1) // input must be string
        strcpy(dest, buffer);
    else // input must be character
        *dest = buffer[0];
}

/* getLong gets long integer input
 *
*/
long getLong(void)
{
    char buffer[1024];
    char *convert;
    long number;
    int success;

    do
    {
       fgets(buffer, 1024, stdin); // get number

       errno = 0;
       number = strtol(buffer, &convert, 10); // convert to long

       if (errno == ERANGE) // repeat prompt if user enters a number too large
       {
           printf("Input is too large for long integer. Please try again:");
           success = 0;
       }
       else if (convert == buffer) // repeat prompt if no character was read
       {
           printf("Input was not fully converted. Please try again:");
           success = 0;
       }
       else if (*convert && *convert != '\n') // repeat prompt if input is not end of line
       {
           printf("Input was not fully converted. Please try again:");
           success = 0;
       }
       else // store input
       {
           success = 1;
       }

    }
    while (success == 0);

    return number; // return number

}

/* getDouble gets double input
 *
*/
double getDouble(void)
{
    char buffer[1024];
    char *convert;
    double number;
    int success;

    do
    {
        fgets(buffer, 1024, stdin); // get number

        errno = 0;
        number = strtod(buffer, &convert); // convert to double

        if (errno == ERANGE) // repeat prompt if user enters a number too large
        {
            printf("Input is too large for double. Please try again:");
            success = 0;
        }
        else if (convert == buffer) // repeat prompt if no character was read
        {
            printf("Input was not fully converted. Please try again:");
            success = 0;
        }
        else if (*convert && *convert != '\n') // repeat prompt if input is not end of line
        {
            printf("Input was not fully converted. Please try again:");
            success = 0;
        }
        else // store input
        {
            success = 1;
        }

    }
    while (success == 0);

    return number; // return number

}

/* sortUsers sorts users array by user id
 * @param users[] - array of users
 * @param userCount - number of users
*/
void sortUsers(struct user users[], int userCount) // selection sort for users
{
    int min;
    struct user temp;

    for (int i = 0; i < userCount-1; i++)
    {
        min = i;
        for (int j = i+1; j < userCount; j++)
        {
            if (users[j].userid < users[min].userid) // sort users by ascending order based on user id
                min = j;
        }
        if (min != i)
        {
            temp = users[i];
            users[i] = users[min];
            users[min] = temp;
        }

    }
}

/* sortItems sorts items array by product id
 * @param items[] - array of items
 * @param itemCount - number of items
*/
void sortItems(struct item items[], int itemCount) // selection sort for items
{
    int min;
    struct item temp;

    for (int i = 0; i < itemCount-1; i++)
    {
        min = i;
        for (int j = i+1; j < itemCount; j++)
        {
            if (items[j].productid < items[min].productid) // sort items by ascending order based on product id
                min = j;
        }
        if (min != i)
        {
            temp = items[i];
            items[i] = items[min];
            items[min] = temp;
        }

    }

}

/* sortCart sorts items array by seller id then product id
 * @param items[] - array of users
 * @param cartItemCount - number of users
*/
int sortCart(struct item items[], int cartItemCount) // selection sort for cart items
{
    int min;
    int max;
    struct item temp;
    int newCartItemCount = 0;

    for (int i = 0; i < cartItemCount; i++)
    {
        max = i;
        for (int j = i+1; j < cartItemCount; j++)
        {
            if (items[j].quantity > items[max].quantity) // sort cart items from max to min quantity
                max = j;
        }
        if (max != i)
        {
            temp = items[i];
            items[i] = items[max];
            items[max] = temp;
        }
    }

    for (int i = 0; i < cartItemCount; i++) // remove item from cart if quantity is zero
    {
        if (items[i].quantity > 0)
            newCartItemCount++;
    }

    for (int i = 0; i < newCartItemCount; i++)
    {
        min = i;
        for (int j = i+1; j < newCartItemCount; j++)
        {
            if (items[j].sellerid < items[min].sellerid) // sort items in cart by seller id in ascending order
                min = j;
        }
        if (min != i)
        {
            temp = items[i];
            items[i] = items[min];
            items[min] = temp;
        }

    }


    for (int i = 0; i < newCartItemCount; i++)
    {
        min = i;
        for (int j = i+1; j < newCartItemCount; j++)
        {
            if (items[j].sellerid == items[min].sellerid && items[j].productid < items[min].productid) // sort items of seller in cart by product in ascending order
                min = j;
        }
        if (min != i)
        {
            temp = items[i];
            items[i] = items[min];
            items[min] = temp;
        }

    }


    return newCartItemCount; // return number of items in cart

}
