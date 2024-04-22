#include "stack.h"
#include <stdio.h>
#include <sys/time.h>

Element itoe(int i);

int main() {
    struct timeval t1, t2;
    double time_taken;

    gettimeofday(&t1, NULL);

    Stack *s = newStack();

    if (isEmpty(s)) {
        printf("Stack is empty\n");
    }

    push(s, itoe(1));
    int value = top(s)->int_value;
    printf("Top of stack is %d\n", value);
    
    push(s, itoe(2));
    value = top(s)->int_value;
    printf("Top of stack after pushing another element is %d\n", value);

    pop(s);
    value = top(s)->int_value;
    printf("Top of stack after popping is %d\n", value);

    printf("Trying to pop from an empty stack\n");
    printf("Pop returned %s\n", pop(s) ? "true" : "false");

    for(int i = 0; i< 500; i++){
        push(s, itoe(i));
    }
    pop(s);
    value = top(s)->int_value;
    printf("Top of stack after popping is %d\n", value);

    freeStack(s);

    gettimeofday(&t2, NULL);
    time_taken = (t2.tv_sec - t1.tv_sec) + (t2.tv_usec - t1.tv_usec) * 1e-6;
    printf("Stack Operations took %f seconds\n", time_taken);

    return 0;
}

Element itoe(int i) {
    Element e;
    e.int_value = i;
    e.float_value = 0;
    return e;
}
