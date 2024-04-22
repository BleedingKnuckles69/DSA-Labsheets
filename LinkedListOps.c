#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node* NODE;
struct node{
    int ele;
    NODE next;
};

typedef struct linked_list* LIST;
struct linked_list{
    int count;
    NODE head;
};

LIST createNewList(){
    LIST myList;
    myList = (LIST)malloc(sizeof(struct linked_list));
    myList->count=0;
    myList->head=NULL;
    return myList;
}

NODE createNewNode(int value){
    NODE myNode;
    myNode = (NODE)malloc(sizeof(struct node));
    myNode->ele=value;
    myNode->next=NULL;
    return myNode;
}

bool isEmpty(LIST l1){
    return l1->count==0;
}

void printList(LIST l1){
    NODE temp = l1->head;
    printf("[HEAD] -> ");
    while(temp != NULL){
        printf("%d -> ", temp->ele);
        temp = temp->next;
    }
    printf("[NULL]\n");
}

void insertFirst(NODE n1, LIST l1){
    if(l1->head == NULL){
        l1->head = n1;
        n1->next = NULL;
        l1->count++;
    }
    else{
        n1->next = l1->head;
        l1->head = n1;
        l1->count++;
    }
}

void insertLast(NODE n1, LIST l1){
    if(l1->count == 0){
        insertFirst(n1, l1);
    }
    else{
        NODE temp = l1->head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = n1;
        n1->next = NULL;
        l1->count++;
    }
}

void insertAfter(int searchEle, NODE n1, LIST l1){
    if(l1->head == NULL){
        l1->head = n1;
        n1->next = NULL;
        l1->count++;
        return;
    }
    NODE temp = l1->head;
    while(temp != NULL){
        if(temp->ele == searchEle){
            n1->next = temp->next;
            temp->next = n1;
            l1->count++;
            return;
        }
        temp = temp->next;
    }
    printf("Element not found.\n");
}

void deleteFirst(LIST l1){
    if(l1->head == NULL){
        printf("Nothing to delete!\n");
    }
    else{
        NODE temp = l1->head;
        l1->head = temp->next;
        free(temp);
        l1->count--;
    }
}

void deleteLast(LIST l1){
    if(l1->head == NULL){
        printf("Nothing to delete!\n");
    }
    else{
        NODE temp = l1->head;
        while((temp->next)->next != NULL){
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
        l1->count--;
    }
}

void deleteEle(int searchEle, LIST l1) {
    NODE temp = l1->head;
    NODE prev = NULL; // Initialize prev to NULL
    if(l1->count == 0){
        printf("Nothing to delete!\n");
        return;
    }
    while(temp != NULL){
        if(temp->ele == searchEle){
            if(prev == NULL){ // Deleting the first node
                l1->head = temp->next;
            } 
            else{
                prev->next = temp->next;
            }
            free(temp);
            l1->count--;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Element not found.\n");
}

void deleteAt(int idx, LIST l1){
    NODE temp = l1->head;
    NODE prev = l1->head;
    if(idx > l1->count-1){
        printf("Index out of bounds!\n");
        return;
    }
    if(idx == 0){
        deleteFirst(l1);
        return;
    }
    for(int i=1;i<=idx;i++){
        prev = temp;
        temp = temp->next;
    }
    if(temp->next == NULL){
        prev->next = NULL;
        l1->count--;
        free(temp);
    }
    else{
        prev->next = temp->next;
        l1->count--;
        free(temp);
    }
    return;
}

void insertAt(int idx, NODE n1, LIST l1){
    NODE temp = l1->head;
    NODE prev = NULL;
    if(idx > l1->count-1){
        printf("Index out of bounds!\n");
        return;
    }
    if(idx == 0){
        insertFirst(n1, l1);
        return;
    }
    for(int i=1;i<=idx;i++){
        prev = temp;
        temp = temp->next;
    }
    prev->next = n1;
    n1->next = temp;
    l1->count++;
}

int search(int searchEle, LIST l1){
    NODE temp = l1->head;
    int idx = 0;
    while(temp != NULL){
        if(temp->ele == searchEle){
            break;
        }
        temp = temp->next;
        idx++;
    }
    if(temp == NULL){
        printf("Element not found.\n");
        return -1;
    }
    return idx;
}

//task 8
LIST rotateLeft(LIST l1, int k){
    NODE temp = l1->head;
    while(temp->next!=NULL){
        temp = temp->next;
    }
    temp->next = l1->head;
    temp = l1->head;
    while(k--){
        temp = temp->next;
    }
    l1->head = temp;
    int r = l1->count-1;
    while(r--){
        temp = temp->next;
    }
    temp->next = NULL;
    return l1;
}

LIST rotateRight(LIST l1, int k){
    NODE temp = l1->head;
    while(temp->next!=NULL){
        temp = temp->next;
    }
    temp->next = l1->head;
    temp = l1->head;
    int diff = l1->count - k;
    while(diff--){
        temp = temp->next;
    }
    l1->head = temp;
    int r = l1->count-1;
    while(r--){
        temp = temp->next;
    }
    temp->next = NULL;
    return l1;
}

void reverse(LIST l1){
    NODE prev=NULL, curr = l1->head, next=NULL;
    while(curr!=NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    l1->head = prev;
}

bool hasCycle(LIST l1){
    NODE tortoise = l1-> head;
    NODE hare = l1->head;
    while(hare!=NULL && hare->next!=NULL){
        tortoise = tortoise->next;
        hare = hare->next->next;
        if(hare==tortoise){
            return true;
        }
    }
    return false;
}

int main(){
    NODE n = createNewNode(7);
    LIST l = createNewList();
    l->count = 0;
    insertFirst(n, l);
    insertFirst(createNewNode(6), l);
    insertLast(createNewNode(8), l);
    //deleteFirst(l);
    //deleteLast(l);
    //deleteEle(8, l);
    insertAfter(8, createNewNode(9), l);
    insertLast(createNewNode(10), l);
    insertAt(0, createNewNode(5), l);
    reverse(l);
    if(isEmpty(l)){
        printf("List is empty.\n");
    }
    else{
        printList(l);
    }
    printf("List has cycle: %d", hasCycle(l));
    //printf("Index %d\n", search(7, l));
    return 0;
}