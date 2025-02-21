#ifndef DELIVERY_AUTOMATION_H
#define DELIVERY_AUTOMATION_H

// Define purchase structure and pointer
struct purchase {
    int productID;
    int quantity;
    struct purchase *nextPurchasePtr;
};
typedef struct purchase Purchase;
typedef Purchase *PurchasePtr;

// Define customer structure and pointer
struct customer {
    int ID;
    char name[50];
    int address;
    PurchasePtr purchases; // Track purchases for the customer
    struct customer *nextCustomerPtr;
};
typedef struct customer Customer;
typedef Customer *CustomerPtr;

// Define product structure and pointer
struct product {
    int ID;
    char name[50];
    unsigned int type : 4;
    double price;
    char productInfo[100]; // New productInfo field
    struct product *nextProductPtr;
};
typedef struct product Product;
typedef Product *ProductPtr;

// Define store structure and pointer
struct store {
    int ID;
    char name[50];
    int address;
    struct store *nextStorePtr;
};
typedef struct store Store;
typedef Store *StorePtr;

// Function prototypes for customer, product, and store management
void insertCustomer(CustomerPtr *cPtr, int c_ID, char* c_name, int c_address);
int deleteCustomer(CustomerPtr *cPtr, int c_ID);
char* getCustomerName(CustomerPtr *cPtr, int c_ID);
int getCustomerAddress(CustomerPtr *cPtr, int c_ID);
ProductPtr findProduct(ProductPtr products, int productID);
void insertProduct(ProductPtr *pPtr, int p_ID, char* p_name, unsigned int p_type, double p_price, char* p_info);
void insertStore(StorePtr *sPtr, int s_ID, char* s_name, int s_address);
StorePtr findStore(StorePtr stores, int storeID);
void addPurchase(CustomerPtr customer, int productID, int quantity);
CustomerPtr getCustomerByID(CustomerPtr customers, int c_ID);
void displayProductsPurchased(PurchasePtr purchases, ProductPtr products);
double calculateTotalAmount(PurchasePtr purchases, ProductPtr products);
int calculateTotalAmountAll(CustomerPtr customers, ProductPtr products);

// Function prototypes for main program functionalities
void displayMainMenu();
void productSales(CustomerPtr customers, ProductPtr products);
void finishBuyingStage();
void displayCustomerInfo(CustomerPtr customers);
void displayStoreInfo(StorePtr stores, ProductPtr products);
void displayProductInfo(ProductPtr products);
void displayProductsByType(ProductPtr products, unsigned int productType);
void customerInformation(CustomerPtr customers);
void storeInformation(StorePtr stores, ProductPtr products);
void productInformation(ProductPtr products);
void customerAnalysis(CustomerPtr customers, ProductPtr products);
void productAnalysis(ProductPtr products);

#endif /* DELIVERY_AUTOMATION_H */

