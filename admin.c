//This file contains the functions for the admin menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

/* showAllUsers has a void return type and prints every user from the users array including userID, password, name, address, and phone number of each user in table form
* @param users passes the users array from main
* @param userCount the number of users in users array
* @return void return type
* Pre-condition: Admin password is correct
*/
void showAllUsers(struct user users[], int userCount){
    printf("All Users\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    printf("|   UserID   |  Password  |         Name          |             Address             | Phone Number |\n");
    printf("----------------------------------------------------------------------------------------------------\n");
    for(int i=0; i<userCount; i++) {
            printf("| %10ld | %-10s | %-21s | %-31s | %12ld |\n", users[i].userid, users[i].password, users[i].name, users[i].address, users[i].contactnumber);
            printf("----------------------------------------------------------------------------------------------------\n");
    }
//userID, password, name, address, phone number
}

/* showAllSellers has a void return type and prints every seller from the users array including userID, password, name, address, and phone number of each seller in table form
* @param users passes the users array from main
* @param userCount the number of users in users array
* @return void return type
* Pre-condition: Admin password is correct
*/
void showAllSellers(struct user users[], int userCount){
    printf("All Sellers\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|   UserID   |  Password  |         Name          |             Address             | Phone Number | Number of items for sale |\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------\n");
    for(int i=0; i<userCount; i++) {
        //users are determined as sellers if the userItemCount is greater than zero
        if(users[i].userItemCount > 0) {
            printf("| %10ld | %-10s | %-21s | %-31s | %12ld | %24ld |\n", users[i].userid, users[i].password, users[i].name, users[i].address, users[i].contactnumber, users[i].userItemCount);
            printf("-------------------------------------------------------------------------------------------------------------------------------\n");
        }
    }
}

/* showTotalSalesByDuration has a double return type and returns the total sales of every transaction between two given dates
* @param transactions passes the transactions array from adminMenu
* @param transactionCount the number of users in users array
* @return returns total sales as a double value
* Pre-condition: Start date and end date inputted are valid dates
*/
double showTotalSalesByDuration(struct transaction transactions[], int transactionCount){
    long month, month2;
    long day, day2;
    long year, year2;
    long temp;
    double total=0;
    int valid, swap;
    //date input validation for start date
    printf("Please input the start date:\n");
    do
    {
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
    while (checkValidDate(month, day, year) == 0);
    //date input validation for end date
    printf("Please input the end date:\n");
    do
    {
        printf("Input month [mm]:");
        do
        {
            month2 = getLong();
            if (month2 < 1 || month2 > 12)
                printf("Please input a valid month:");
        }
        while(month2 < 1 || month2 > 12);
        printf("Input day [dd]:");
        do
        {
            day2 = getLong();
            if (day2 < 1 || day2 > 31)
                printf("Please input a valid day:");
        }
        while(day2 < 1 || day2 > 31);
        printf("Input year [yyyy]:");
        do
        {
            year2 = getLong();
            if (year2 < 0)
                printf("Please input a valid year:");
        }
        while(year2 < 0);
    }
    while (checkValidDate(month2, day2, year2) == 0);

    //checks if the start date occurs before the end date, otherwise the two dates are swapped
    if(year2<year){
        swap = 1;
    }
    else if(year2==year){
        if(month2<month){
            swap=1;
        }
        else if(month2==month){
            if(day2<day)
                swap=1;
            else
                swap=0;
        }
        else
            swap=0;
    }
    else
        swap=0;

    if(swap){

        temp = day;
        day = day2;
        day2 = temp;

        temp = month;
        month = month2;
        month2 = temp;

        temp = year;
        year = year2;
        year2 = temp;
        printf("The end date inputted is earlier than the start date. The two dates have been swapped.\n");
    }
    //iterates through every transaction
    for(int i=0; i<transactionCount; i++){
        valid = 0;
        //checks if the transaction occurred between the two dates
        if(transactions[i].year>year){
            valid = 1;
        }
        else if(transactions[i].year==year){
            if(transactions[i].month>month){
                valid=1;
            }
            else if(transactions[i].month==month){
                if(transactions[i].day>=day){
                    valid=1;
                }
                else
                    valid=0;
            }
            else
                valid=0;
        }
        else
            valid=0;

        if(valid ==1){
            if(transactions[i].year<year2){
                valid = 1;
            }
            else if(transactions[i].year==year2){
                if(transactions[i].month<month2){
                    valid=1;
                }
                else if(transactions[i].month==month2){
                    if(transactions[i].day<=day2)
                        valid=1;
                    else
                        valid=0;
                }
                else
                    valid=0;
            }
            else
                valid=0;
        }
        //if the transaction occurred during the given duration, the total of that transaction is added to the total variable which is returned by the function
        if(valid){
            total+=transactions[i].total;
        }
    }

    return total;
}

/* showSellerSales has a void return type and prints every seller and their respective total sales in the inputted duration in a table format
* @param transactions passes the transactions array from adminMenu
* @param transactionCount the number of transactions
* @param users passes the users array
* @param userCount number of users in the users array
* @return void return type
* Pre-condition: Start date and end date inputted are valid dates
*/
void showSellerSales(struct transaction transactions[], int transactionCount, struct user users[], int userCount){
    struct transactor transactors[100];

    long month, month2;
    long day, day2;
    long year, year2;
    long temp;
    int valid, swap, foundIndex;
    int ctr=0;
    //date validation for the start date
    printf("Please input the start date:\n");
    do
    {
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
    while (checkValidDate(month, day, year) == 0);
    //input validation for end date
    printf("Please input the end date:\n");
    do
    {
        printf("Input month [mm]:");
        do
        {
            month2 = getLong();
            if (month2 < 1 || month2 > 12)
                printf("Please input a valid month:");
        }
        while(month2 < 1 || month2 > 12);
        printf("Input day [dd]:");
        do
        {
            day2 = getLong();
            if (day2 < 1 || day2 > 31)
                printf("Please input a valid day:");
        }
        while(day2 < 1 || day2 > 31);
        printf("Input year [yyyy]:");
        do
        {
            year2 = getLong();
            if (year2 < 0)
                printf("Please input a valid year:");
        }
        while(year2 < 0);
    }
    while (checkValidDate(month2, day2, year2) == 0);
    //checks if the start date occurs before the end date, otherwise the two dates are swapped
    if(year2<year){
        swap = 1;
    }
    else if(year2==year){
        if(month2<month){
            swap=1;
        }
        else if(month2==month){
            if(day2<day)
                swap=1;
            else
                swap=0;
        }
        else
            swap=0;
    }
    else
        swap=0;

    if(swap) {

        temp = day;
        day = day2;
        day2 = temp;

        temp = month;
        month = month2;
        month2 = temp;

        temp = year;
        year = year2;
        year2 = temp;
        printf("The end date inputted is earlier than the start date. The two dates have been swapped.\n");
    }
    //iterates through every transaction
    for(int i=0; i<transactionCount; i++){
        valid = 0;
    //checks if the transaction occurs during the duration
        if(transactions[i].year>year){
            valid = 1;
        }
        else if(transactions[i].year==year){
            if(transactions[i].month>month){
                valid=1;
            }
            else if(transactions[i].month==month){
                if(transactions[i].day>=day){
                    valid=1;
                }
                else
                    valid=0;
            }
            else
                valid=0;
        }
        else
            valid=0;

        if(valid ==1){
            if(transactions[i].year<year2){
                valid = 1;
            }
            else if(transactions[i].year==year2){
                if(transactions[i].month<month2){
                    valid=1;
                }
                else if(transactions[i].month==month2){
                    if(transactions[i].day<=day2)
                        valid=1;
                    else
                        valid=0;
                }
                else
                    valid=0;
            }
            else
                valid=0;
        }

        if(valid){
            foundIndex=-1;
            //checks if the current seller being checked already has an existing total
            for(int j=0; j<ctr; j++){
                if(transactors[j].sellerid == transactions[i].sellerid) {
                    foundIndex = j;
                    j=100;
                }
            }
            //if the seller does not have an existing total, their sellerid, name, and total are added into transactors
            if(foundIndex==-1){
                transactors[ctr].sellerid = transactions[i].sellerid;
                for(int l=0; l<userCount; l++){
                    if(transactions[i].sellerid == users[l].userid){
                        strcpy(transactors[ctr].name, users[l].name);
                    }
                }
                transactors[ctr].total = transactions[i].total;
                ctr++;
            }//if the seller already has an existing total in transactors, the total in any additional transactions for that seller is added to the existing total
            else{
                transactors[foundIndex].total += transactions[i].total;
            }
        }
    }

    printf("Seller Sales\n");
    printf("--------------------------------------------------------------------\n");
    printf("|  SellerID  |         Name          | Total sales in the duration |\n");
    printf("--------------------------------------------------------------------\n");
    for(int k=0; k<ctr; k++) {
        printf("| %10ld | %-21s | %27lf |\n", transactors[k].sellerid, transactors[k].name, transactors[k].total);
        printf("--------------------------------------------------------------------\n");
    }
}
/* showShopaholics has a void return type and prints every buyer and their respective total amount bought in the inputted duration in a table format
* @param transactions passes the transactions array from adminMenu
* @param transactionCount the number of transactions
* @param users passes the users array
* @param userCount number of users in the users array
* @return void return type
* Pre-condition: Start date and end date inputted are valid dates
*/
void showShopaholics(struct transaction transactions[], int transactionCount, struct user users[], int userCount){
    struct transactor transactors[100];

    long month, month2;
    long day, day2;
    long year, year2;
    long temp;
    int valid, swap, foundIndex;
    int ctr=0;
    //input validation for start date
    printf("Please input the start date:\n");
    do
    {
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
    while (checkValidDate(month, day, year) == 0);
    //input validation for end date
    printf("Please input the end date:\n");
    do
    {
        printf("Input month [mm]:");
        do
        {
            month2 = getLong();
            if (month2 < 1 || month2 > 12)
                printf("Please input a valid month:");
        }
        while(month2 < 1 || month2 > 12);
        printf("Input day [dd]:");
        do
        {
            day2 = getLong();
            if (day2 < 1 || day2 > 31)
                printf("Please input a valid day:");
        }
        while(day2 < 1 || day2 > 31);
        printf("Input year [yyyy]:");
        do
        {
            year2 = getLong();
            if (year2 < 0)
                printf("Please input a valid year:");
        }
        while(year2 < 0);
    }
    while (checkValidDate(month2, day2, year2) == 0);
    //checks if the start date occurs before the end date, otherwise the two dates are swapped
    if(year2<year){
        swap = 1;
    }
    else if(year2==year){
        if(month2<month){
            swap=1;
        }
        else if(month2==month){
            if(day2<day)
                swap=1;
            else
                swap=0;
        }
        else
            swap=0;
    }
    else
        swap=0;

    if(swap) {

        temp = day;
        day = day2;
        day2 = temp;

        temp = month;
        month = month2;
        month2 = temp;

        temp = year;
        year = year2;
        year2 = temp;
        printf("The end date inputted is earlier than the start date. The two dates have been swapped.\n");
    }
    //iterates through every transaction in transactions
    for(int i=0; i<transactionCount; i++){
        valid = 0;
        //checks if the transaction occurs in the duration inputted
        if(transactions[i].year>year){
            valid = 1;
        }
        else if(transactions[i].year==year){
            if(transactions[i].month>month){
                valid=1;
            }
            else if(transactions[i].month==month){
                if(transactions[i].day>=day){
                    valid=1;
                }
                else
                    valid=0;
            }
            else
                valid=0;
        }
        else
            valid=0;

        if(valid ==1){
            if(transactions[i].year<year2){
                valid = 1;
            }
            else if(transactions[i].year==year2){
                if(transactions[i].month<month2){
                    valid=1;
                }
                else if(transactions[i].month==month2){
                    if(transactions[i].day<=day2)
                        valid=1;
                    else
                        valid=0;
                }
                else
                    valid=0;
            }
            else
                valid=0;
        }

        if(valid){
            foundIndex=-1;
            //checks if the buyer has already been found and added into transactors
            for(int j=0; j<ctr; j++){
                if(transactors[j].buyerid == transactions[i].buyerid) {
                    foundIndex = j;
                    j=100;
                }
            }
            //if its the first time the buyer has appeared in a transaction their buyerid, name, and total is added into transactors
            if(foundIndex==-1){
                transactors[ctr].buyerid = transactions[i].buyerid;
                for(int l=0; l<userCount; l++){
                    if(transactions[i].buyerid == users[l].userid){
                        strcpy(transactors[ctr].name, users[l].name);
                    }
                }
                transactors[ctr].total = transactions[i].total;
                ctr++;
            }//if the buyer has already been added into transactors previously, only the total is added into the existing transactors total
            else{
                transactors[foundIndex].total += transactions[i].total;
            }
        }
    }

    printf("\nShopaholics\n");
    printf("----------------------------------------------------------------------------\n");
    printf("|  BuyerID   |         Name          | Total amount bought in the duration |\n");
    printf("----------------------------------------------------------------------------\n");
    for(int k=0; k<ctr; k++) {
        printf("| %10ld | %-21s | %35lf |\n", transactors[k].buyerid, transactors[k].name, transactors[k].total);
        printf("----------------------------------------------------------------------------\n");
    }
}

/* adminMenu has a void return type and allows the user to select from 5 admin options which each call their respective function
* @param users passes the users array
* @param userCount number of users in the users array
* @param itemCount number of items in the items array
* @return void return type
* Pre-condition: password admin inputted is correct
*/
void adminMenu(struct user users[], int userCount, int itemCount)
{
    struct transaction transactions[100];
    int transactionCount;
    char password[11];
    char admin[7] = "H3LLo?";
    int choice = 0;
    int transactionItems[1000];
    double total;

    //reads the transactions file and adds each transaction into the transactions array
    transactionCount = readTransactionItems(transactionItems);
    readTransactions(transactions, transactionItems, transactionCount);

    printf("Please input the administrator password:");
    getString(password, 11);
    //password validation
    if(strcmp(password, admin) != 0){
        printf("Unauthorized access not allowed\n");
        return;
    }
    //admin menu options
    while (choice != 6) {
        printf("\nAdmin Menu\n\n");
        printf("[1] Show All Users\n");
        printf("[2] Show All Sellers\n");
        printf("[3] Show Total Sales in Given Duration\n");
        printf("[4] Show Seller Sales\n");
        printf("[5] Show Shopaholics\n");
        printf("[6] Back to Main Menu\n");

        printf("\nSelect an option:");
        choice = getLong();

        switch (choice) {
            case 1:
                if (userCount <= 0)
                {
                    printf("No Users Found!\n");
                }
                else
                    showAllUsers(users,userCount);
                break;
            case 2:
                if (itemCount <= 0)
                {
                    printf("No Sellers Found!\n");
                }
                else
                    showAllSellers(users, userCount);
                break;
            case 3:
                if (transactionCount <= 0)
                {
                    printf("No Transactions Found!\n");
                }
                else
                {
                    total = showTotalSalesByDuration(transactions, transactionCount);
                    printf("Total sales in this given duration is: %lf\n", total);
                }
                break;
            case 4:
                if (transactionCount <= 0)
                {
                    printf("No Transactions Found!\n");
                }
                else
                    showSellerSales(transactions, transactionCount, users, userCount);
                break;
            case 5:
                if (transactionCount <= 0)
                {
                    printf("No Transactions Found!\n");
                }
                else
                    showShopaholics(transactions, transactionCount, users, userCount);
                break;
            case 6:
                printf("Returning to the Main Menu\n");
                break;
            default:
                printf("Please select from the listed options\n");
                break;
        }

    }

}


