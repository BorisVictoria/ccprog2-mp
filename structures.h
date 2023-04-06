// This file contains the structure variables and typedef declarations used in main.c
#ifndef STRUCTURES_H
#define STRUCTURES_H

struct user
{
    long userid;
    char name[21];
    char password[11];
    char address[31];
    long contactnumber;

};

struct item
{
    long sellerid;
    long productid;
    char name[21];
    char category[16];
    char description[31];
    long quantity;
    double price;
};

struct transaction
{
    long month;
    long day;
    long year;
    long buyerid;
    long sellerid;
    struct item items[5];
    double total;

};

//Helper.c Functions
void getString(char dest[], int destsize);
int getLong(void);
int getDouble(void);

//Sell.c Functions
void sellMenu();

//Buy.c Functions
void buyMenu();

//Startup.c Functions
void readUsers(struct user users[]);
void readItems(struct item items[]);
void readTransactions(struct transaction transactions[]);

//Exit.c Functions
void writeUsers(struct user users[]);
void writeItems(struct item items[]);
void writeTransactions(struct transaction transactions[]);

//User.c Functions
void userMenu();

//Register.c Functions
int registerUser(struct user users[], int userCount);

//admin.c Functions
void adminMenu();
void showAllUsers();
void showAllSellers();
int showTotalSalesByDuration();
void showSellerSales();
void showShopaholics();

#endif

