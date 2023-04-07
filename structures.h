// This file contains the structure variables and typedef declarations used in main.c
#ifndef STRUCTURES_H
#define STRUCTURES_H
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

struct user
{
    long userid;
    char name[21];
    char password[11];
    char address[31];
    long contactnumber;
    struct item items[20];
    long userItemCount;
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

struct cart
{
    int userid;
    struct item items[10];
};

//Helper.c Functions
void getString(char dest[], int destsize);
long getLong(void);
double getDouble(void);
void sortUsers(struct user users[], int userCount);
void sortItems(struct item items[], int itemCount);
void sortTransactions(struct transaction transactions[], int transactionCount);
//int getTotalItemsFromUsers(struct user users[], int userCount, struct item items[]);

//Sell.c Functions
int sellMenu(struct user users[], int userIndex, struct item items[], int itemCount);
int addNewItem(struct user users[], int userIndex, int userItemCount, struct item items[], int itemCount);
void showMyProducts(struct user users[], int userIndex, int userItemCount);
void showMyLowStockProducts(struct user users[], int userIndex, int userItemCount);

//Stock.c Functions
void editStockMenu(struct user users[], int userIndex, int userItemCount, struct item items[], int itemCount);
void replenish(struct user users[], int userIndex, int userProductIndex, struct item items[], int productIndex);
void changePrice(struct user users[], int userIndex, int userProductIndex, struct item items[], int productIndex);
void changeItemName(struct user users[], int userIndex, int userProductIndex, struct item items[], int productIndex);
void changeCategory(struct user users[], int userIndex, int userProductIndex, struct item items[], int productIndex);
void changeDescription(struct user users[], int userIndex, int userProductIndex, struct item items[], int productIndex);

//Buy.c Functions
void buyMenu(struct user users[], int userIndex, int userCount, struct item items[], int itemCount);
void viewAllProducts(struct user users[], int userCount);
void showProductBySeller(struct user users[], int userCount);
void showProductByCategory(struct item items[], int itemCount);
void showProductByName(struct item items[], int itemCount);
void addToCart(struct item items[], int itemCount);

//Cart.c Functions
void readCart(struct cart userCart); // implement
void writeCart(struct cart userCart); // implement
void editCartMenu();
void removeItemsFromSeller();
void removeSpecificItem();
void editQuantity();

//Checkout.c Functions
void checkoutMenu();
void checkoutAll();
void checkoutBySeller();
void checkoutByItem();

//Startup.c Functions
int readUsers(struct user users[]);
int readItems(struct item items[]);
void readTransactions(struct transaction transactions[]);
void storeItemsToUsers(struct user users[], int userCount, struct item items[], int itemCount);

//Exit.c Functions
void writeUsers(struct user users[], int userCount);
void writeItems(struct item items[], int itemCount);
void writeTransactions(struct transaction transactions[]);

//User.c Functions
int userMenu(struct user users[], int userCount, struct item items[], int itemCount);

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

