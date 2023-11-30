#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void decrypt(char* cipherTXT, int shift) {
    int i;
    char ch;
    for(i = 0; cipherTXT[i] != '\0'; ++i) {
        ch = cipherTXT[i];
        if(ch >= 'a' && ch <= 'z'){
            ch = ch - shift;
            if(ch < 'a'){
                ch = ch + 'z' - 'a' + 1;
            }
            cipherTXT[i] = ch;
        }
        else if(ch >= 'A' && ch <= 'Z'){
            ch = ch - shift;
            if(ch < 'A'){
                ch = ch + 'Z' - 'A' + 1;
            }
            cipherTXT[i] = ch;
        }
    }
    printf(" %s\n", cipherTXT);
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Usage: %s [text]\n", argv[0]);
        return 1;
    }

    char * cipherTXT;
    
    printf("Enter Encrypted Message: ");

    if (argc == 2) {
        cipherTXT = argv[1];

    } else {
        
        cipherTXT = malloc(100);
        fgets(cipherTXT, 100, stdin);
        cipherTXT[strcspn(cipherTXT, "\n")] = 0;
    }

    printf("Decrypted Messages:\n");
    for(int shift = 1; shift <= 26; shift++) {
        char decryptTXT[100];
        strcpy(decryptTXT, cipherTXT);
        decrypt(decryptTXT, shift);
    }
    return 0;
}