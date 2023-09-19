#include <stdlib.h>
#include <stdio.h>

void pal(char* str) {
    char * lPtr = str;
    char * rPtr = str;

    while (*rPtr != '\0') {
        rPtr++;
    }
     
    rPtr--;

    while (lPtr != rPtr) {
        if (*lPtr != *rPtr) {
            printf("%s is NOT a palindrome\n", str);
            return;
        }
        lPtr++;
        rPtr--;
    }
    printf("%s is a palindrome\n", str);
}

int main () {
    char string [100];
    printf("Enter your word: ");
    scanf("%s", string);

    pal(string);

    return 0;
}