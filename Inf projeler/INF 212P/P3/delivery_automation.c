#include "delivery_automation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function implementations...

void displayMainMenu() {
    printf("\n===== Grocery Delivery Automation Menu =====\n");
    printf("1. Sales\n");
    printf("2. Customer Information\n");
    printf("3. Store Information\n");
    printf("4. Product Information\n");
    printf("5. Customer Analysis\n");
    printf("6. Product Analysis (Bonus)\n");
    printf("7. Exit\n");
    printf("============================================\n");
}

// Function to handle the product sales process
void productSales(CustomerPtr customers, ProductPtr products) {
    int customerId;
    int productId;
    int quantity;

    printf("\nEnter the customer number: ");
    scanf("%d", &customerId);

    // Find the customer
    char *customerName = getCustomerName(&customers, customerId);
    if (customerName == NULL) {
        printf("Customer not found!\n");
        return;
    }

    // Proceed with product sales
    printf("\n===== Product Sales =====\n");
    while (1) {
        printf("Enter the product number (0 to finish): ");
        scanf("%d", &productId);

        if (productId == 0) {
            break;
        }

        // Find the product
        ProductPtr product = findProduct(products, productId);
        if (product == NULL) {
            printf("Product not found!\n");
            continue;
        }

        printf("Enter the quantity: ");
        scanf("%d", &quantity);

        // Update customer's purchases
        CustomerPtr customer = getCustomerByID(customers, customerId);
        if (customer != NULL) {
            addPurchase(customer, productId, quantity);
        } else {
            printf("Customer not found!\n");
        }
    }

    // Finish the buying stage for the current customer
    finishBuyingStage();
}

// Function to finish the buying stage for the current customer
void finishBuyingStage() {
    printf("\nBuying stage for this customer has been completed.\n");
}

// Function to insert a new product into the linked list
void insertProduct(ProductPtr *pPtr, int p_ID, char* p_name, unsigned int p_type, double p_price, char* p_info) {
    ProductPtr newProduct = (ProductPtr)malloc(sizeof(Product));
    if (newProduct != NULL) {
        newProduct->ID = p_ID;
        strcpy(newProduct->name, p_name);
        newProduct->type = p_type;
        newProduct->price = p_price;
        strcpy(newProduct->productInfo, p_info); // Copy product info
        newProduct->nextProductPtr = NULL;

        if (*pPtr == NULL) {
            *pPtr = newProduct;
        } else {
            ProductPtr current = *pPtr;
            while (current->nextProductPtr != NULL) {
                current = current->nextProductPtr;
            }
            current->nextProductPtr = newProduct;
        }
        printf("Product %s added successfully.\n", p_name);
    } else {
        printf("Memory allocation failed. Unable to add product.\n");
    }
}

// Function to insert a new store into the linked list
void insertStore(StorePtr *sPtr, int s_ID, char* s_name, int s_address) {
    StorePtr newStore = (StorePtr)malloc(sizeof(Store));
    if (newStore != NULL) {
        newStore->ID = s_ID;
        strcpy(newStore->name, s_name);
        newStore->address = s_address;
        newStore->nextStorePtr = NULL;

        if (*sPtr == NULL) {
            *sPtr = newStore;
        } else {
            StorePtr current = *sPtr;
            while (current->nextStorePtr != NULL) {
                current = current->nextStorePtr;
            }
            current->nextStorePtr = newStore;
        }
        printf("Store %s added successfully.\n", s_name);
    } else {
        printf("Memory allocation failed. Unable to add store.\n");
    }
}

// Function to display customer information
void displayCustomerInfo(CustomerPtr customers) {
    printf("\n===== Customer Information =====\n");
    CustomerPtr current = customers;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Address: %d\n", current->ID, current->name, current->address);
        current = current->nextCustomerPtr;
    }
}

// Function to display store information
void displayStoreInfo(StorePtr stores, ProductPtr products) {
    printf("\n===== Store Information =====\n");
    StorePtr current = stores;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Address: %d\n", current->ID, current->name, current->address);
        printf("Products in Store:\n");
        // List all products (assuming all products are available in all stores)
        displayProductInfo(products);
        printf("\n");
        current = current->nextStorePtr;
    }
}

// Function to display product information
void displayProductInfo(ProductPtr products) {
    printf("\n===== Product Information =====\n");
    ProductPtr current = products;
    while (current != NULL) {
        printf("ID: %d, Name: %s, Type: %d, Price: %.2f, Info: %s\n", current->ID, current->name, current->type, current->price, current->productInfo); // Updated print statement
        current = current->nextProductPtr;
    }
}

void displayProductsByType(ProductPtr products, unsigned int productType) {
    printf("\n===== Products of Type %u =====\n", productType);
    ProductPtr current = products;
    while (current != NULL) {
        if (current->type == productType) {
            printf("ID: %d, Name: %s, Type: %d, Price: %.2f\n", current->ID, current->name, current->type, current->price);
        }
        current = current->nextProductPtr;
    }
}

// Function to handle customer information menu
void customerInformation(CustomerPtr customers) {
    int choice;
    int customerId; // Move the declaration here

    do {
        printf("\n===== Customer Information Menu =====\n");
        printf("1. All Customers\n");
        printf("2. Single Customer\n");
        printf("3. Back to Main Menu\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayCustomerInfo(customers);
                break;
            case 2:
                // Code to handle displaying information of a single customer
                printf("Enter customer ID: ");
                scanf("%d", &customerId);
                char *customerName = getCustomerName(&customers, customerId);
                int customerAddress = getCustomerAddress(&customers, customerId);
                if (customerName != NULL && customerAddress != -1) {
                    printf("Customer ID: %d, Name: %s, Address: %d\n", customerId, customerName, customerAddress);
                } else {
                    printf("Customer not found!\n");
                }
                break;
            case 3:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

// Function to handle store information menu
void storeInformation(StorePtr stores, ProductPtr products) {
    int choice;
    int storeID;

    do {
        printf("\n===== Store Information Menu =====\n");
        printf("1. All Stores\n");
        printf("2. Single Store\n");
        printf("3. Back to Main Menu\n");
        printf("==================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayStoreInfo(stores, products);
                break;
            case 2:
                printf("Enter store ID: ");
                scanf("%d", &storeID);
                // Find the store
                StorePtr store = findStore(stores, storeID);
                if (store != NULL) {
                    printf("Store ID: %d, Name: %s, Address: %d\n", store->ID, store->name, store->address);
                    printf("Products in Store:\n");
                    // List all products (assuming all products are available in all stores)
                    displayProductInfo(products);
                } else {
                    printf("Store not found!\n");
                }
                break;
            case 3:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

// Function to handle product information menu
void productInformation(ProductPtr products) {
    int choice;

    do {
        printf("\n===== Product Information Menu =====\n");
        printf("1. All Products\n");
        printf("2. Products by Type\n");
        printf("3. Single Product\n");
        printf("4. Back to Main Menu\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nAll Products:\n");
                displayProductInfo(products);
                break;
            case 2:
                printf("\nEnter the product type (1, 2, or 3): ");
                unsigned int productType;
                scanf("%u", &productType);
                displayProductsByType(products, productType);
                break;
            case 3:
                printf("\nEnter the ID of the product: ");
                int productID;
                scanf("%d", &productID);
                ProductPtr product = findProduct(products, productID);
                if (product != NULL) {
                    printf("\nProduct Information:\n");
                    printf("ID: %d, Name: %s, Type: %d, Price: %.2f\n", product->ID, product->name, product->type, product->price);
                } else {
                    printf("\nProduct not found!\n");
                }
                break;
            case 4:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}


// Function to handle customer analysis menu
void customerAnalysis(CustomerPtr customers, ProductPtr products) {
    int choice;

    do {
        printf("\n===== Customer Analysis =====\n");
        printf("1. Products purchased by a customer\n");
        printf("2. Total amount of purchases by a customer\n");
        printf("3. Total amount of products purchased by all customers\n");
        printf("4. Customers' shipping fees\n");
        printf("5. Back to Main Menu\n");
        printf("=================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int customerId;
                printf("Enter customer ID: ");
                scanf("%d", &customerId);
                CustomerPtr customer = getCustomerByID(customers, customerId);
                if (customer != NULL) {
                    printf("Products purchased by customer %s:\n", customer->name);
                    displayProductsPurchased(customer->purchases, products);
                } else {
                    printf("Customer not found!\n");
                }
                break;
            }
            case 2: {
                int customerId;
                printf("Enter customer ID: ");
                scanf("%d", &customerId);
                CustomerPtr customer = getCustomerByID(customers, customerId);
                if (customer != NULL) {
                    double totalAmount = calculateTotalAmount(customer->purchases, products);
                    printf("Total amount of purchases by customer %s: %.2lf\n", customer->name, totalAmount);
                } else {
                    printf("Customer not found!\n");
                }
                break;
            }
            case 3: {
                int totalAmount = calculateTotalAmountAll(customers, products);
                printf("Total amount of products purchased by all customers: %d\n", totalAmount);
                break;
            }
            case 4: {
                // You can implement this case according to your specific requirements
                printf("Customers' shipping fees analysis\n");
                break;
            }
            case 5:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}

void displayProductsPurchased(PurchasePtr purchases, ProductPtr products) {
    PurchasePtr current = purchases;
    while (current != NULL) {
        ProductPtr product = findProduct(products, current->productID);
        if (product != NULL) {
            printf("ID: %d, Name: %s, Quantity: %d\n", product->ID, product->name, current->quantity);
        }
        current = current->nextPurchasePtr;
    }
}

// Function to calculate the total amount of purchases by a customer
double calculateTotalAmount(PurchasePtr purchases, ProductPtr products) {
    double totalAmount = 0.0;
    PurchasePtr current = purchases;
    while (current != NULL) {
        ProductPtr product = findProduct(products, current->productID);
        if (product != NULL) {
            totalAmount += (product->price * current->quantity);
        }
        current = current->nextPurchasePtr;
    }
    return totalAmount;
}

// Function to calculate the total amount of products purchased by all customers
int calculateTotalAmountAll(CustomerPtr customers, ProductPtr products) {
    int totalAmount = 0;
    CustomerPtr currentCustomer = customers;
    while (currentCustomer != NULL) {
        totalAmount += calculateTotalAmount(currentCustomer->purchases, products);
        currentCustomer = currentCustomer->nextCustomerPtr;
    }
    return totalAmount;
}

// Function to handle product analysis menu
void productAnalysis(ProductPtr products) {
    // Here you can implement functions to analyze product data
    printf("\n===== Product Analysis =====\n");
    printf("Implement product analysis here.\n");
}

// Function to insert a new customer into the linked list
void insertCustomer(CustomerPtr *cPtr, int c_ID, char* c_name, int c_address) {
    CustomerPtr newCustomer = (CustomerPtr)malloc(sizeof(Customer));
    if (newCustomer != NULL) {
        newCustomer->ID = c_ID;
        strcpy(newCustomer->name, c_name);
        newCustomer->address = c_address;
        newCustomer->nextCustomerPtr = NULL;
        newCustomer->purchases = NULL; // Initialize purchases for the new customer

        if (*cPtr == NULL) {
            *cPtr = newCustomer;
        } else {
            CustomerPtr current = *cPtr;
            while (current->nextCustomerPtr != NULL) {
                current = current->nextCustomerPtr;
            }
            current->nextCustomerPtr = newCustomer;
        }
        printf("Customer %s added successfully.\n", c_name);
    } else {
        printf("Memory allocation failed. Unable to add customer.\n");
    }
}

// Function to delete a customer from the linked list
int deleteCustomer(CustomerPtr *cPtr, int c_ID) {
    if (*cPtr == NULL) {
        return 0; // Customer list is empty
    } else {
        if ((*cPtr)->ID == c_ID) {
            CustomerPtr temp = *cPtr;
            *cPtr = (*cPtr)->nextCustomerPtr;
            free(temp);
            printf("Customer ID %d deleted successfully.\n", c_ID);
            return 1; // Customer found and deleted
        } else {
            CustomerPtr prev = *cPtr;
            CustomerPtr current = (*cPtr)->nextCustomerPtr;
            while (current != NULL && current->ID != c_ID) {
                prev = current;
                current = current->nextCustomerPtr;
            }
            if (current != NULL) {
                prev->nextCustomerPtr = current->nextCustomerPtr;
                free(current);
                printf("Customer ID %d deleted successfully.\n", c_ID);
                return 1; // Customer found and deleted
            } else {
                printf("Customer ID %d not found.\n", c_ID);
                return -1; // Customer not found
            }
        }
    }
}

// Function to find a customer by ID
CustomerPtr getCustomerByID(CustomerPtr customers, int c_ID) {
    CustomerPtr current = customers;
    while (current != NULL) {
        if (current->ID == c_ID) {
            return current;
        }
        current = current->nextCustomerPtr;
    }
    return NULL; // Customer not found
}

// Function to find a product by ID
ProductPtr findProduct(ProductPtr products, int productID) {
    ProductPtr current = products;
    while (current != NULL) {
        if (current->ID == productID) {
            return current;
        }
        current = current->nextProductPtr;
    }
    return NULL; // Product not found
}

// Function to find a store by ID
StorePtr findStore(StorePtr stores, int storeID) {
    StorePtr current = stores;
    while (current != NULL) {
        if (current->ID == storeID) {
            return current;
        }
        current = current->nextStorePtr;
    }
    return NULL; // Store not found
}

// Function to add a purchase for a customer
void addPurchase(CustomerPtr customer, int productID, int quantity) {
    PurchasePtr newPurchase = (PurchasePtr)malloc(sizeof(Purchase));
    if (newPurchase != NULL) {
        newPurchase->productID = productID;
        newPurchase->quantity = quantity;
        newPurchase->nextPurchasePtr = NULL;

        if (customer->purchases == NULL) {
            customer->purchases = newPurchase;
        } else {
            PurchasePtr current = customer->purchases;
            while (current->nextPurchasePtr != NULL) {
                current = current->nextPurchasePtr;
            }
            current->nextPurchasePtr = newPurchase;
        }
        printf("Purchase added successfully.\n");
    } else {
        printf("Memory allocation failed. Unable to add purchase.\n");
    }
}

// Function to get customer name by ID
char* getCustomerName(CustomerPtr *cPtr, int c_ID) {
    CustomerPtr current = *cPtr;
    while (current != NULL) {
        if (current->ID == c_ID) {
            return current->name;
        }
        current = current->nextCustomerPtr;
    }
    return NULL; // Customer not found
}

// Function to get customer address by ID
int getCustomerAddress(CustomerPtr *cPtr, int c_ID) {
    CustomerPtr current = *cPtr;
    while (current != NULL) {
        if (current->ID == c_ID) {
            return current->address;
        }
        current = current->nextCustomerPtr;
    }
    return -1; // Customer not found
}

