//This file contains the functions for the admin menu and all associated features.
#include <stdio.h>
#include <string.h>
#include "structures.h"

void adminMenu(){
    char password[11];
    char admin[7] = "H3LLo?";
    int choice = 0;

    printf("Please input the administrator password:");
    getString(password, 11);

    if(strcmp(password, admin) != 0){
        printf("Unauthorized access not allowed");
        return;
    }

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
                showAllUsers();
                break;
            case 2:
                showAllSellers();
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

void showAllUsers(){

}

void showAllSellers(){

}

int showTotalSalesByDuration(){

}

void showSellerSales(){

}

void showShopaholics(){

}
