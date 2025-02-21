#include <stdio.h>
#include "delivery_automation.h"

int main() {
    // Initialize pointers to the start of each linked list
    CustomerPtr customers = NULL;
    ProductPtr products = NULL;
    StorePtr stores = NULL;

    insertCustomer(&customers, 1, "Ali Karaman", 3);
    insertCustomer(&customers, 2, "Zehra Cilek", 4);
    insertCustomer(&customers, 3, "Mehmet Derin", 7);
    insertCustomer(&customers, 4, "Veli Ortanca", 5);
    insertCustomer(&customers, 5, "Menekse Serin", 1);

    insertProduct(&products, 1, "Portakal Sikma", 1, 5.99, "Freshly squeezed orange juice");
    insertProduct(&products, 2, "Muz Yerli", 1, 12.95, "Fresh local bananas");
    insertProduct(&products, 3, "Sogan", 2, 7.45, "Onions imported from Spain");
    insertProduct(&products, 4, "Pirasa", 2, 3.95, "Fresh leeks");
    insertProduct(&products, 5, "Lahana", 2, 5.95, "Cabbage");
    insertProduct(&products, 6, "Limon", 1, 7.45, "Lemons from the garden");
    insertProduct(&products, 7, "Hamsi", 3, 15, "Fresh anchovies from the Black Sea");

    insertStore(&stores, 1, "Store 1", 1);
    insertStore(&stores, 2, "Store 2", 2);
    insertStore(&stores, 3, "Store 3", 4);
    insertStore(&stores, 4, "Store 4", 6);
    insertStore(&stores, 5, "Store 5", 7);
    insertStore(&stores, 6, "Store 6", 8);

    // Main program loop
    int choice;
    do {
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                productSales(customers, products);
                break;
            case 2:
                customerInformation(customers);
                break;
            case 3:
                storeInformation(stores, products);
                break;
            case 4:
                productInformation(products);
                break;
            case 5:
                customerAnalysis(customers, products);
                break;
            case 6:
                productAnalysis(products);
                break;
            case 7:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    // Free allocated memory before exiting
    // Code for freeing memory here...

    return 0;
}

