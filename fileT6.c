#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *fp1, *fp2;
    char buff[1000];
    char ch;
    
    fp1 = fopen("text1.txt", "r");
    if(fp1 == NULL){
        printf("Error opening file!");
        exit(1);
    }
    fp2 = fopen("text2.txt", "w");
    if(fp2 == NULL){
        printf("Error opening file!");
        exit(1);
    }
    while((ch = fgetc(fp1))!=EOF){
        fputc(ch, fp2);
    }
    fclose(fp1);
    fclose(fp2);

    fp1 = fopen("text1.txt", "w");
    if(fp1 == NULL){
        printf("Error emptying source file.\n");
        return 1;
    }
    fclose(fp1);

    printf("File contents moved successfully.\n");

    return 0;
}