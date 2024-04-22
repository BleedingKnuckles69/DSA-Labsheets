#include "linked_list.h"
#include "stack.h"
#include "element.h"
#include <stdlib.h>
#include <stdio.h>

struct Stack{
    int top;
    LIST l;
};

Stack *newStack(){
    Stack *s = (Stack*)malloc(sizeof(struct Stack));
    if(s != NULL){
        s->top = -1;
        s->l = createNewList();
    }
    return s;
}

bool push(Stack *s, Element e){
    insertNodeIntoList(createNewNode(e), s->l);
    s->top++;
    return true;
}

Element *top(Stack *stack){
    if(isEmpty(stack)){
        return NULL;
    }
    return &(stack->l->head->data);
}

bool isEmpty(Stack *stack){
    if(stack->top == -1){
        return true;
    }
    return false;
}

bool pop(Stack *stack){
    if(isEmpty(stack)){
        //printf("Nothing to pop!\n");
        return false;
    }
    else{
        stack->top--;
        removeFirstNode(stack->l);
        return true;
        //return &(stack->l->head->data); // if it were Element *pop
    }
}

void freeStack(Stack *stack){
    stack->top = -1;
    destroyList(stack->l);
}