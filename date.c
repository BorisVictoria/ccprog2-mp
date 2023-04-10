// This file contains the function for validating the date in the checkout menu
#include "structures.h"

/* checkLeapYear checks if year is a leap year
 * @year - year
 */
int checkLeapYear(long year) // check if leap year
{
    if ((year % 4 == 0) && (year % 100 != 0) && (year % 400 == 0))
        return 1;
    else
        return 0;
}

/* checkValidDate checks if a date is valid
 * @month - month
 * @day - day
 * @year - year
 */
int checkValidDate(long month, long day, long year) // check if date is valid
{
    if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day <= 30)
            return 1;
        else
            return 0;
    }

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
