#include <stdio.h>

int main(){
    FILE *fp;
    char buff[1000];
    char ch;

    fp = fopen(__FILE__, "r");

    /*while(!feof(fp)){
        ch = fgetc(fp);
        printf("%c", ch);
    }*/
    while(fgets(buff, 1000, fp)){
        printf("%s", buff);
    }
    fclose(fp);
    return 0;
}