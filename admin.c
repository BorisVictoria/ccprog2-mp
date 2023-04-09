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

int showTotalSalesByDuration(){
    return 999;
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

    transactionCount = readTransactionItems(transactionItems);
    readTransactions(transactions, transactionItems, transactionCount);

    printf("Please input the administrator password:");
    getString(password, 11);

    if(strcmp(password, admin) != 0){
        printf("Unauthorized access not allowed");
        return;
    }

    /*TEST: Print contents of transactions[] if they are correct
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
                showTotalSalesByDuration();
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


