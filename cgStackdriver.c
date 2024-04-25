#include "stack.h"
#include "heap_usage.h"  // Include the heap usage tracking header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

Element iftoe(int i, float f);

int main(int argc, char *argv[]) {
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file");
        exit(1);
    }

    char *line = malloc(100);

    /*
        Initialize the stack and heap performance variables
    */
    Stack *stack = newStack();
    size_t totalHeapUsed = 0;
    double totalTimePush = 0.0;
    double totalTimePop = 0.0;

    int score = 0;
    float cg = 0;
    int i = 0;

    while (fgets(line, 100, fp) != NULL) {
        char *token;
        token = strtok(line, ",");
        score = atoi(token);
        token = strtok(NULL, ",");
        cg = atof(token);

        Element e = iftoe(score, cg);
        
        struct timeval startPush, endPush;
        gettimeofday(&startPush, NULL);

        // Push the element onto the stack while tracking heap usage
        void *pushResult = myalloc(sizeof(Element));
        memcpy(pushResult, &e, sizeof(Element));
        push(stack, *((Element *)pushResult));

        gettimeofday(&endPush, NULL);
        totalTimePush += (endPush.tv_sec - startPush.tv_sec) + ((endPush.tv_usec - startPush.tv_usec) / 1000000.0);
        totalHeapUsed += heapMemoryAllocated;
        
        i++;
    }
    fclose(fp);

    printf("Total time taken to push onto stack: %.6f seconds\n", totalTimePush);
    printf("Maximum heap space utilized: %zu bytes\n", totalHeapUsed);

    // Empty the stack and measure time taken for popping
    struct timeval startPop, endPop;
    gettimeofday(&startPop, NULL);

    while (!isEmpty(stack)) {
        pop(stack);
    }

    gettimeofday(&endPop, NULL);
    totalTimePop = (endPop.tv_sec - startPop.tv_sec) + ((endPop.tv_usec - startPop.tv_usec) / 1000000.0);
    printf("Total time taken to pop from stack: %.6f seconds\n", totalTimePop);

    free(line);
    freeStack(stack);

    return 0;
}

Element iftoe(int i, float f) {
    Element e;
    e.int_value = i;
    e.float_value = f;
    return e;
}
