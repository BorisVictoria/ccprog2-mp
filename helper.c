//This file contains the input and helper functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void getString(char dest[], int destsize)
{
    char buffer[1024];
    long len;
    int success;

    success = 0;
    while (success == 0)
    {
        fgets(buffer, 1024, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        len = strlen(buffer);
        if (len > destsize)
        {
            printf("Input too long! Please try again:");
        }
        else
        {
            success = 1;
        }

    }
    if (len > 1)
        strcpy(dest, buffer);
    else
        *dest = buffer[0];
}

long getLong(void)
{
    char buffer[1024];
    char *convert;
    long number;
    int success;

    do
    {
       fgets(buffer, 1024, stdin);

       errno = 0;
       number = strtol(buffer, &convert, 10);

       if (errno == ERANGE)
       {
           printf("Input is too large for integer. Please try again:");
           success = 0;
       }
       else if (convert == buffer)
       {
           printf("Input was not fully converted. Please try again:");
           success = 0;
       }
       else if (*convert && *convert != '\n')
       {
           printf("Input was not fully converted. Please try again:");
           success = 0;
       }
       else
       {
           success = 1;
       }

    }
    while (success == 0);

    return number;

}

double getDouble(void)
{
    char buffer[1024];
    char *convert;
    long number;
    int success;

    do
    {
        fgets(buffer, 1024, stdin);

        errno = 0;
        number = strtod(buffer, &convert);

        if (errno == ERANGE)
        {
            printf("Input is too large for long integer. Please try again:");
            success = 0;
        }
        else if (convert == buffer)
        {
            printf("Input was not fully converted. Please try again:");
            success = 0;
        }
        else if (*convert && *convert != '\n')
        {
            printf("Input was not fully converted. Please try again:");
            success = 0;
        }
        else
        {
            success = 1;
        }

    }
    while (success == 0);

    return number;

}