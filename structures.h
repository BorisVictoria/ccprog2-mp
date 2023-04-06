// This file contains the structure variables and typedef declarations used in main.c
#ifndef STRUCTURES_H
#define STRUCTURES_H

struct user
{
    int userid;
    char name[21];
    char password[11];
    char address[31];
    int contactnumber;

};

struct item
{
    int sellerid;
    int productid;
    char name[21];
    char category[16];
    char description[31];
    int quantity;
    float price;
};

struct transactions
{
    int month;
    int day;
    int year;
    int buyerid;
    int sellerid;
    struct item items[5];
    float total;

};

//Helper.c Functions
void getString(char dest, int destsize);
int getLong(void);
int getDouble(void);

//User.c Functions
void userMenu();

#endif

