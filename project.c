#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct order {
    int id;
    char name[100];
    char item[100];
};

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void placeOrder() {
    struct order x;
    FILE *fptr = fopen("orders.txt", "a");

    printf("\nEnter Order ID: ");
    scanf("%d", &x.id);
    getchar();
    printf("Enter Customer Name: ");
    fgets(x.name, sizeof(x.name), stdin);
    removeNewline(x.name);

    printf("Enter Food Item: ");
    fgets(x.item, sizeof(x.item), stdin);
    removeNewline(x.item);

    fprintf(fptr, "%d %s %s\n", x.id, x.name, x.item);
    fclose(fptr);
    printf("Order placed successfully!\n");
}

void viewOrders() {
    struct order x;
    FILE *fptr = fopen("orders.txt", "r");

    printf("\n_Order History_\n");
    while (fscanf(fptr, "%d %s %s", &x.id, x.name, x.item) == 3) {
        printf("ID: %d | Name: %s | Item: %s\n", x.id, x.name, x.item);
    }
    
    
    fclose(fptr);
}

void cancelOrder() {
    int id, found = 0;
    struct order x;
    FILE *fptr = fopen("orders.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    printf("Enter Order ID to cancel: ");
    scanf("%d", &id);

    while (fscanf(fptr, "%d %s %s", &x.id, x.name, x.item) == 3) {
        if (x.id != id) {
            fprintf(temp, "%d %s %s\n", x.id, x.name, x.item);
        } else {
            found = 1;
        }
    }

    fclose(fptr);
    fclose(temp);

    remove("orders.txt");
    rename("temp.txt", "orders.txt");

    if (found)
        printf("Order Cancelled Successfully.\n");
    else
        printf("Order ID not found.\n");
}

int main() {
    int choice;
    do {
        printf("\n_--Food Order Menu--_\n");
        printf("1. Place Order\n");
        printf("2. View Orders\n");
        printf("3. Cancel Orders\n");
        printf("4. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                placeOrder();
                break;
            case 2:
                viewOrders();
                break;
            case 3:
                cancelOrder();
                break;
            case 4:
                printf("Thank You!\n");
                break;
            default:
                printf("Invalid Choice.\n");
        }
    } while (choice != 4);

    return 0;
}