#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int n, i;
    printf("Enter size of array: ");
    scanf("%d", &n);
    char** arr = (char**)malloc(n * sizeof(char*));
    if(arr == NULL){
        printf("Memory allocation failed\n");
        return -1; 
    }
    printf("Enter the strings: \n");
    for(i=0;i<n;i++){
        arr[i] = malloc(100 * sizeof(char));
        if(arr[i] == NULL){
            printf("Memory allocation failed\n");
            // Free memory allocated so far
            for(int j = 0; j < i; j++){
                free(arr[j]);
            }
            free(arr);
            return 1; // Exit with error code
        }
        scanf("%99s", arr[i]);
    }
    printf("\nGiven array of strings: ");
    for(i=0;i<n;i++){
        printf("%s\n", arr[i]);
    }
    printf("\n");
    printf("Select an option: \n(a) Add a string to the end of the array\n(b) Add a string to the beginning of the array\n(c) Delete the element at index x(taken as input) of the array\n(d) Display the length of the array\n");
    char c;
    scanf(" %c", &c);

    if(c=='a'){
        printf("Adding an string to the end of array.\n");
        char newstring[100];
        printf("Enter the string to be added: ");
        scanf("%99s", newstring);
        arr = realloc(arr, (n+1)*sizeof(char*));
        //strcpy(arr[n], newstring);
        arr[n] = newstring;
        n++;
    }

    if(c=='b'){
        printf("Adding an string to the beginning of array.\n");
        char newstring[100];
        printf("Enter the string to be added: ");
        scanf("%99s", newstring);
        arr = realloc(arr, (n+1)*sizeof(char*));
        for(i=n-1;i>=0;i--){
            arr[i+1]=arr[i];
        }
        arr[0] = newstring;
        //strcpy(arr[0], newstring);
        n++;
    }

    if(c=='c'){
        printf("Enter index of element to delete: ");
        int idx;
        scanf("%d", &idx);
        if(idx>=0 && idx<n){
            free(arr[idx]);
            for(i=idx;i<n-1;i++){
                arr[i] = arr[i+1];
            }
        }
        n--;
    }

    if(c=='d'){
        printf("Length of array is: %d\n", n);
    }
    printf("Elements of array are: \n");
    for(i=0;i<n;i++){
        printf("%s ", arr[i]);
    }
    printf("\n");
    return 0;
}