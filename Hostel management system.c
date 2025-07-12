#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define BILL_AMOUNT 3000  // Monthly bill amount

struct HostelMember {
    int id;
    char name[50];
    char roomNo[10];
    char phone[15];
    float billPaid;
};

struct HostelMember members[MAX];
int count = 0;

// Function declarations
void loadMembersFromFile();
void saveMembersToFile();
int isRoomAvailable(const char *roomNo);
void addMember();
void viewAll();
void searchMember();
void payBill();
void menu();

int main() {
    int choice;
    loadMembersFromFile();

    while (1) {
        menu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume newline

        switch (choice) {
            case 1:
                addMember();
                break;
            case 2:
                viewAll();
                break;
            case 3:
                searchMember();
                break;
            case 4:
                payBill();
                break;
            case 5:
                saveMembersToFile();
                printf("Exiting and saving data...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

void menu() {
    printf("\n===== Bachelor Hostel Management System =====\n");
    printf("1. Add Member\n");
    printf("2. View All Members\n");
    printf("3. Search Member by ID\n");
    printf("4. Pay Bill\n");
    printf("5. Exit\n");
}

void loadMembersFromFile() {
    FILE *file = fopen("members.txt", "r");
    if (file == NULL) return;

    while (fscanf(file, "%d %[^\n] %[^\n] %[^\n] %f\n",
           &members[count].id,
           members[count].name,
           members[count].roomNo,
           members[count].phone,
           &members[count].billPaid) == 5) {
        count++;
    }

    fclose(file);
}

void saveMembersToFile() {
    FILE *file = fopen("members.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d\n%s\n%s\n%s\n%.2f\n",
                members[i].id,
                members[i].name,
                members[i].roomNo,
                members[i].phone,
                members[i].billPaid);
    }
    fclose(file);
}

int isRoomAvailable(const char *roomNo) {
    for (int i = 0; i < count; i++) {
        if (strcmp(members[i].roomNo, roomNo) == 0) {
            return 0;
        }
    }
    return 1;
}

void addMember() {
    if (count >= MAX) {
        printf("Hostel is full! Cannot add more members.\n");
        return;
    }

    char tempRoom[10];

    printf("Enter Member ID: ");
    scanf("%d", &members[count].id);
    getchar();

    printf("Enter Name: ");
    fgets(members[count].name, sizeof(members[count].name), stdin);
    strtok(members[count].name, "\n");

    do {
        printf("Enter Room Number: ");
        fgets(tempRoom, sizeof(tempRoom), stdin);
        strtok(tempRoom, "\n");

        if (!isRoomAvailable(tempRoom)) {
            printf("Room %s is already taken! Try another.\n", tempRoom);
        }
    } while (!isRoomAvailable(tempRoom));
    strcpy(members[count].roomNo, tempRoom);

    printf("Enter Phone Number: ");
    fgets(members[count].phone, sizeof(members[count].phone), stdin);
    strtok(members[count].phone, "\n");

    members[count].billPaid = 0.0;

    count++;
    printf("Member added successfully!\n");
}

void viewAll() {
    if (count == 0) {
        printf("No members found.\n");
        return;
    }

    printf("\n--- All Hostel Members ---\n");
    for (int i = 0; i < count; i++) {
        printf("\nID: %d\nName: %s\nRoom: %s\nPhone: %s\nBill Paid: %.2f BDT\n",
               members[i].id, members[i].name, members[i].roomNo,
               members[i].phone, members[i].billPaid);
    }
}

void searchMember() {
    int id, found = 0;
    printf("Enter Member ID to search: ");
    scanf("%d", &id);for (int i = 0; i < count; i++) {
        if (members[i].id == id) {
            printf("\n--- Member Found ---\n");
            printf("ID: %d\nName: %s\nRoom: %s\nPhone: %s\nBill Paid: %.2f BDT\n",
                   members[i].id, members[i].name, members[i].roomNo,
                   members[i].phone, members[i].billPaid);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No member found with ID %d.\n", id);
}

void payBill() {
    int id;
    float amount;
    int found = 0;

    printf("Enter Member ID to pay bill: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (members[i].id == id) {
            printf("Total Monthly Bill: %.2f BDT\n", (float)BILL_AMOUNT);
            printf("Enter amount to pay: ");
            scanf("%f", &amount);
            members[i].billPaid += amount;
            printf("Payment successful! Total paid: %.2f BDT\n", members[i].billPaid);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No member found with ID %d.\n", id);
}
