// This file contains the function for validating the date in the checkout menu
#include <stdio.h>
#include "structures.h"
int checkLeapYear(long year)
{
    if ((year % 4 == 0) && (year % 100 != 0) && (year % 400 == 0))
        return 1;
    else
        return 0;
}

int checkValidDate(long month, long day, long year)
{
    if (month == 4 || month == 6 || month == 9 || month == 11)
        if (day <= 30)
            return 1;
        else
            return 0;

    if (month == 2)
    {
        if (checkLeapYear(year))
        {
            if (day <= 29)
                return 1;
            else
                return 0;
        }
    }

    return 1;
}
