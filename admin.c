//This file contains the functions for the admin menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void showAllUsers(struct user users[], int userCount){
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("|    userID    |   password   |          name          |             address             | phone number |\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    for(int i=0; i<userCount; i++) {
            printf("| %12ld | %-12s | %-22s | %-31s | %12ld |\n", users[i].userid, users[i].password, users[i].name, users[i].address, users[i].contactnumber);
            printf("---------------------------------------------------------------------------------------------------------\n");    }
//userID, password, name, address, phone number
}

void showAllSellers(struct user users[], int userCount){

    printf("userID password name address phone number number of items for sale\n");
    for(int i=0; i<userCount; i++) {
        if(users[i].userItemCount > 0) {
            printf("%ld %s %s %s %ld %ld\n", users[i].userid, users[i].password, users[i].name, users[i].address, users[i].contactnumber, users[i].userItemCount);
        }
    }
}

double showTotalSalesByDuration(struct transaction transactions[], int transactionCount){
    long month, month2;
    long day, day2;
    long year, year2;
    long temp;
    double total=0;
    int valid, swap;

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
//    printf("start date month %ld day %ld year %ld", month, day, year);
//    printf("end date month %ld day %ld year %ld", month2, day2, year2);

    for(int i=0; i<transactionCount; i++){
        valid = 0;

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
            total+=transactions[i].total;
        }
    }

    return total;
}

void showSellerSales(){

}

void showShopaholics(){

}

void adminMenu(struct user users[], int userCount)
{
    struct transaction transactions[100];
    int transactionCount;
    char password[11];
    char admin[7] = "H3LLo?";
    int choice = 0;
    int transactionItems[1000];
    double total;

    transactionCount = readTransactionItems(transactionItems);
    readTransactions(transactions, transactionItems, transactionCount);

    printf("Please input the administrator password:");
    getString(password, 11);

    if(strcmp(password, admin) != 0){
        printf("Unauthorized access not allowed\n");
        return;
    }
/*
    //TEST: Print contents of transactions[] if they are correct
    for (int i = 0; i < transactionCount; i++)
    {
        printf("\ntransactionsItems[%d] = %d\n", i, transactionItems[i]);
    }

    for (int i = 0; i < transactionCount; i++)
    {
        printf("\ntransactions[%d].buyerid = %ld\n", i, transactions[i].buyerid);
        printf("transactions[%d].sellerid = %ld\n", i, transactions[i].sellerid);
        printf("transactions[%d].month = %ld\n", i, transactions[i].month);
        printf("transactions[%d].day = %ld\n", i, transactions[i].day);
        printf("transactions[%d].year = %ld\n", i, transactions[i].year);
        printf("transactions[%d].total = %lf\n\n", i, transactions[i].total);

    }
*/

    while (choice != 6) {
        printf("Admin Menu\n\n");
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
                showAllUsers(users,userCount);
                break;
            case 2:
                showAllSellers(users, userCount);
                break;
            case 3:
                total = showTotalSalesByDuration(transactions, transactionCount);
                printf("Total sales in this given duration is: %lf\n", total);
                break;
            case 4:
                showSellerSales();
                break;
            case 5:
                showShopaholics();
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


