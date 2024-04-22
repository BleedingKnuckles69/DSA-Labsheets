#include "element.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

LIST createNewList(){
    LIST myList;
    myList = (LIST) malloc(sizeof(struct linked_list));
    myList->count=0;
    myList->head=NULL;
    return myList;
}

NODE createNewNode(Element data){
    NODE myNode;
    myNode = (NODE) malloc(sizeof(struct node));
    myNode->data=data;
    myNode->next=NULL;
    return myNode;
}

void insertNodeIntoList(NODE n1, LIST l1){
    if(l1->head == NULL){
        l1->head = n1;
        n1->next = NULL;
        l1->count++;
    }
    else{
        NODE temp = l1->head;
        n1->next = temp;
        l1->head = n1;
        l1->count++;
    }
    return;
}

void removeFirstNode(LIST l1){
    if(l1->head == NULL){
        printf("Nothing to delete!");
    }
    else{
        NODE temp = l1->head;
        l1->head = temp->next;
        free(temp);
        l1->count--;
    }
    return;
}

void destroyList(LIST list){
    while(list->head != NULL){
        removeFirstNode(list);
    }
}

//optional, needed for queue
void insertNodeAtEnd(NODE node, LIST list){
    NODE temp = list->head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = node;
    node->next = NULL;
    list->count++;
}