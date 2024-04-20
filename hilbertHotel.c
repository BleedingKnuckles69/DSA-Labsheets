#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Hotel Information
typedef struct Hotel{
    char name[50];
    char address[100];
    int occupied_rooms;
    struct Occupant *occupants;
} Hotel;

// Structure for Occupant Information
typedef struct Occupant{
    char name[50];
    int age;
    char address[100];
} Occupant;

// Function to initialize the hotel
void initialize_hotel(Hotel *hotel){
    strcpy(hotel->name, "The Grand Hotel");
    strcpy(hotel->address, "123 Main Street");
    hotel->occupied_rooms = 0;
    hotel->occupants = NULL;
}

// Function to reallocate memory for the occupant array
Occupant* reallocate_occupants(Hotel *hotel, int new_size){
    Occupant* new_occupants = (Occupant*)realloc(hotel->occupants, sizeof(Occupant) * new_size);
    if(new_occupants == NULL){
        printf("\nMemory allocation failed!\n");
        exit(1);
    }
    hotel->occupants = new_occupants;
    return hotel->occupants;
}

// Function to assign the first unoccupied room
void assign_first_room(Hotel *hotel, char *name, int age, char *address){
    hotel->occupants = reallocate_occupants(hotel, 1+hotel->occupied_rooms);
    strcpy(hotel->occupants[hotel->occupied_rooms].name, name);
    hotel->occupants[hotel->occupied_rooms].age = age;
    strcpy(hotel->occupants[hotel->occupied_rooms].address, address);
    hotel->occupied_rooms++;
    printf("\nRoom #%d assigned to %s.\n", hotel->occupied_rooms - 1, name);
}

// Function to assign Room #0 by shifting occupants
void assign_room_zero(Hotel *hotel, char *name, int age, char *address){
    if (hotel->occupied_rooms == 0){
        assign_first_room(hotel, name, age, address);
    } 
    else{
        hotel->occupants = reallocate_occupants(hotel, hotel->occupied_rooms + 1);
        for(int i = hotel->occupied_rooms; i > 0; i--){
            strcpy(hotel->occupants[i].name, hotel->occupants[i - 1].name);
            hotel->occupants[i].age = hotel->occupants[i - 1].age;
            strcpy(hotel->occupants[i].address, hotel->occupants[i - 1].address);
        }
        strcpy(hotel->occupants[0].name, name);
        hotel->occupants[0].age = age;
        strcpy(hotel->occupants[0].address, address);
        hotel->occupied_rooms++;
        printf("\nRoom #%d assigned to %s.\n", 0, name);
    }
}

// Function to empty a room
void empty_room(Hotel *hotel, int room_number){
    if(room_number < 0 || room_number >= hotel->occupied_rooms){
        printf("\nInvalid room number.\n");
        return;
    }
    if(hotel->occupied_rooms == 1){
        free(hotel->occupants);
        hotel->occupants = NULL;
        hotel->occupied_rooms = 0;
        printf("\nRoom #%d emptied.\n", room_number);
    } 
    else{
        for(int i = room_number; i < hotel->occupied_rooms - 1; i++){
            strcpy(hotel->occupants[i].name, hotel->occupants[i + 1].name);
            hotel->occupants[i].age = hotel->occupants[i + 1].age;
            strcpy(hotel->occupants[i].address, hotel->occupants[i + 1].address);
        }
        hotel->occupants = reallocate_occupants(hotel, hotel->occupied_rooms - 1);
        hotel->occupied_rooms--;
        printf("\nRoom #%d emptied.\n", room_number);
    }
}

// Function to display information of a specific occupant
void display_occupant(Hotel *hotel, int room_number) {
    if(room_number < 0 || room_number >= hotel->occupied_rooms){
        printf("\nInvalid room number.\n");
        return;
    }
    printf("\nRoom #%d occupant details:\n", room_number);
    printf("Name: %s\n", hotel->occupants[room_number].name);
    printf("Age: %d\n", hotel->occupants[room_number].age);
    printf("Address: %s\n", hotel->occupants[room_number].address);
}

// Main 
int main() {
    Hotel hotel;
    int choice, room_number;
    char name[50], address[100];
    int age;

    initialize_hotel(&hotel);

    while (1) {
        printf("\nThe Grand Hotel Management System\n");
        printf("1. Assign first available room\n");
        printf("2. Assign Room #0 (shifting occupants)\n");
        printf("3. Empty a room\n");
        printf("4. Display information of a guest\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Enter guest name: ");
                scanf(" %[^\n]s", name); // Include space to avoid scanf issues
                printf("Enter guest age: ");
                scanf("%d", &age);
                printf("Enter guest address: ");
                scanf(" %[^\n]s", address);
                assign_first_room(&hotel, name, age, address);
                break;
            case 2:
                printf("Enter guest name: ");
                scanf(" %[^\n]s", name);
                printf("Enter guest age: ");
                scanf("%d", &age);
                printf("Enter guest address: ");
                scanf(" %[^\n]s", address);
                assign_room_zero(&hotel, name, age, address);
                break;
            case 3:
                printf("Enter the room number to empty: ");
                scanf("%d", &room_number);
                empty_room(&hotel, room_number);
                break;
            case 4:
                printf("Enter the room number of the guest: ");
                scanf("%d", &room_number);
                display_occupant(&hotel, room_number);
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}