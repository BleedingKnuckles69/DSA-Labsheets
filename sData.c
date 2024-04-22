#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

struct Student {
    char ID[20];
    float CGPA;
    struct Student* next;
};

// Function to populate the array with data from the file
void populateArray(struct Student* array, int size) {
    FILE* fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        if (fscanf(fp, "%[^,],%f\n", array[i].ID, &array[i].CGPA) != 2) {
            printf("Error reading file.\n");
            break;
        }
    }

    fclose(fp);
}

// Function to insert new records at specific positions in the array
void insertRecordsArray(struct Student* array, int size, int positions[], int numPositions) {
    for (int i = 0; i < numPositions; i++) {
        struct Student newStudent;
        printf("Enter details for new student at position %d:\n", positions[i]);
        printf("ID: ");
        scanf("%s", newStudent.ID);
        printf("CGPA: ");
        scanf("%f", &newStudent.CGPA);

        array[positions[i]] = newStudent;
    }
}

// Function to populate the linked list with data from the file
void populateLinkedList(struct Student** head, int size) {
    FILE* fp = fopen("data.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Student* temp = NULL;
    struct Student* current = *head;

    while (!feof(fp)) {
        struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
        if (fscanf(fp, "%[^,],%f\n", newStudent->ID, &newStudent->CGPA) != 2) {
            printf("Error reading file.\n");
            free(newStudent);
            break;
        }
        newStudent->next = NULL;

        if (*head == NULL) {
            *head = newStudent;
            current = *head;
        } else {
            current->next = newStudent;
            current = current->next;
        }
    }

    fclose(fp);
}

// Function to insert new records at specific positions in the linked list
void insertRecordsLinkedList(struct Student** head, int positions[], int numPositions) {
    struct Student* current = *head;
    for (int i = 0; i < numPositions; i++) {
        struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
        printf("Enter details for new student at position %d:\n", positions[i]);
        printf("ID: ");
        scanf("%s", newStudent->ID);
        printf("CGPA: ");
        scanf("%f", &newStudent->CGPA);

        newStudent->next = NULL;

        if (*head == NULL) {
            *head = newStudent;
            current = *head;
        } else {
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newStudent;
        }
    }
}

// Function to retrieve data from the array at a specific index
void retrieveDataArray(struct Student* array, int index) {
    if (index >= 0 && index < 10000) {
        printf("Array - Student ID: %s, CGPA: %.2f\n", array[index].ID, array[index].CGPA);
    } else {
        printf("Invalid index in array.\n");
    }
}

// Function to retrieve data from the linked list at a specific index
void retrieveDataLinkedList(struct Student* head, int index) {
    struct Student* temp = head;
    int i = 0;
    while (temp != NULL && i < index) {
        temp = temp->next;
        i++;
    }
    if (temp != NULL) {
        printf("Linked List - Student ID: %s, CGPA: %.2f\n", temp->ID, temp->CGPA);
    } else {
        printf("Invalid index in linked list.\n");
    }
}

// Function to delete every entry from the array of structs
void deleteRecordsArray(struct Student* array, int size) {
    for (int i = 0; i < size; i++) {
        memset(&array[i], 0, sizeof(struct Student));
    }
}

// Function to delete every entry from the linked list of structs
void deleteRecordsLinkedList(struct Student** head) {
    struct Student* current = *head;
    struct Student* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

// Function to display the students in the array
void displayStudentsArray(struct Student* array, int size) {
    printf("Array Students:\n");
    for (int i = 0; i < size; i++) {
        if (array[i].ID[0] != '\0') {
            printf("Student ID: %s, CGPA: %.2f\n", array[i].ID, array[i].CGPA);
        }
    }
}

// Function to display the students in the linked list
void displayStudentsLinkedList(struct Student* head) {
    printf("Linked List Students:\n");
    struct Student* temp = head;
    while (temp != NULL) {
        printf("Student ID: %s, CGPA: %.2f\n", temp->ID, temp->CGPA);
        temp = temp->next;
    }
}

int main() {
    struct timeval t1, t2;
    double time_taken;

    int size = 10000; // Number of students
    struct Student* array = (struct Student*)malloc(size * sizeof(struct Student));
    struct Student* linkedList = NULL;

    // Populate array with data from file
    gettimeofday(&t1, NULL);
    populateArray(array, size);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("Time taken to populate array: %.6f seconds\n", time_taken);

    // Populate linked list with data from file
    gettimeofday(&t1, NULL);
    populateLinkedList(&linkedList, size);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("Time taken to populate linked list: %.6f seconds\n", time_taken);

    // Prompt user for three new entries at specific positions
    int positions[3];
    printf("Enter 3 positions (0-9999) to insert new entries at:\n");
    for (int i = 0; i < 3; i++) {
        printf("Position %d: ", i + 1);
        scanf("%d", &positions[i]);
    }

    // Insert new records at specific positions in array
    gettimeofday(&t1, NULL);
    insertRecordsArray(array, size, positions, 3);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("Time taken to insert records in array: %.6f seconds\n", time_taken);

    // Insert new records at specific positions in linked list
    gettimeofday(&t1, NULL);
    insertRecordsLinkedList(&linkedList, positions, 3);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("Time taken to insert records in linked list: %.6f seconds\n", time_taken);

    // Retrieve data from specific position
    int retrievePosition;
    printf("Enter a position (0-9999) to retrieve data from:\n");
    scanf("%d", &retrievePosition);

    // Retrieve data from array
    gettimeofday(&t1, NULL);
    retrieveDataArray(array, retrievePosition);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("Time taken to retrieve data from array: %.6f seconds\n", time_taken);

    // Retrieve data from linked list
    gettimeofday(&t1, NULL);
    retrieveDataLinkedList(linkedList, retrievePosition);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("Time taken to retrieve data from linked list: %.6f seconds\n", time_taken);

    // Delete all records from array and linked list
    gettimeofday(&t1, NULL);
    deleteRecordsArray(array, size);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("Time taken to delete records from array: %.6f seconds\n", time_taken);

    gettimeofday(&t1, NULL);
    deleteRecordsLinkedList(&linkedList);
    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) + ((t2.tv_usec - t1.tv_usec) / 1000000.0);
    printf("Time taken to delete records from linked list: %.6f seconds\n", time_taken);

    free(array); // Free memory allocated for array
    return 0;
}
