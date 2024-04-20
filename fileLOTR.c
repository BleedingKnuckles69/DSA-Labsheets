#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *fp;
    char filename[] = "LOTR.txt";
    char word[100];
    char line[1000];
    int count = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s.\n", filename);
        exit(1);
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        char *token = strtok(line, " .,!?-\"\n\r");
        while (token != NULL) {
            if (strcasecmp(token, "hobbit") == 0) {  // Case insensitive comparison; if (strcmp(token, "hobbit") == 0)   // Case sensitive comparison
                count++;
            }
            token = strtok(NULL, " .,!?-\"\n\r");
        }
    }

    fclose(fp);

    printf("The word 'hobbit' appears %d times in the text.\n", count);

    return 0;
}
