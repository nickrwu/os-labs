#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void decrypt(char* cipher, int key) {
    int i;
    char c;
    for(i = 0; cipher[i] != '\0'; ++i) {
        c = cipher[i];
        if(c >= 'a' && c <= 'z'){
            c -= key;
            if(c < 'a'){
                c +='z' - 'a' + 1;
            }
            cipher[i] = c;
        }
        else if(c >= 'A' && c <= 'Z'){
            c -= key;
            if(c < 'A'){
                c += 'Z' - 'A' + 1;
            }
            cipher[i] = c;
        }
    }
    printf("%d: %s\n", key, cipher);
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Usage: %s [text]\n", argv[0]);
        return 1;
    }

    char * cipher;

    if (argc == 2) {
        cipher = argv[1];

        printf("Encypted Message: %s\n", cipher);

    } else {
        printf("Enter Encrypted Message: ");
        cipher = malloc(100);
        fgets(cipher, 100, stdin);
        cipher[strcspn(cipher, "\n")] = 0;

        printf("Encypted Message: %s\n", cipher);
    }

    printf("Decrypted Messages:\n");
    for(int key = 1; key <= 26; key++) {
        char decrypted[100];
        strcpy(decrypted, cipher);
        decrypt(decrypted, key);
    }
    return 0;
}