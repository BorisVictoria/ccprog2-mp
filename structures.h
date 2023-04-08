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
    long buyerid;
    long sellerid;
    long month;
    long day;
    long year;
    struct item items[5];
    double total;

};


//Helper.c Functions
void getString(char dest[], int destsize);
long getLong(void);
double getDouble(void);
void sortUsers(struct user users[], int userCount);
void sortItems(struct item items[], int itemCount);
int sortCart(struct item items[], int cartItemCount);
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
int addToCart(struct item items[], int itemCount, struct item cart[], int cartItemCount, long userid);

//Cart.c Functions
int editCartMenu(struct item cart[], int cartItemCount, struct item items[], int itemCount);
void removeItemsFromSeller(struct item cart[], int cartItemCount);
void removeSpecificItem(struct item cart[], int cartItemCount);
void editQuantity(struct item cart[], int cartItemCount, struct item items[], int itemCount);

//Checkout.c Functions
int checkoutMenu(struct user users[], int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount);
int cartIntegrityCheck(struct item items[], int itemCount, struct item cart[], int cartItemCount, int* proceed);
int checkCartItem(struct item items[], struct item cart[], int cartItemIndex, int itemIndex);
int checkoutAll(struct user users[], int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount, struct transaction transactions[]);
int checkoutBySeller(struct user users[], int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount, struct transaction transactions[]);
int checkoutByItem(struct user users[], int userCount, struct item items[], int itemCount, struct item cart[], int cartItemCount, struct transaction transactions[]);

//Startup.c Functions
int readUsers(struct user users[]);
int readItems(struct item items[]);
int readCart(struct item items[], long userid);
void storeItemsToUsers(struct user users[], int userCount, struct item items[], int itemCount);

//Exit.c Functions
void writeUsers(struct user users[], int userCount);
void writeItems(struct item items[], int itemCount);
void writeCart(struct item items[], int itemCount, long userid);
void writeTransactions(struct transaction transactions[], int transactionCount);

//User.c Functions
int userMenu(struct user users[], int userCount, struct item items[], int itemCount);

//Register.c Functions
int registerUser(struct user users[], int userCount);

//admin.c Functions
void adminMenu(struct user users[], int userCount);
void showAllUsers(struct user users[], int userCount);
void showAllSellers(struct user users[], int userCount);
int showTotalSalesByDuration();
void showSellerSales();
void showShopaholics();

#endif

