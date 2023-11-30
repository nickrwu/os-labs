#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* encrypt(char* plainTXT, int key) {
    char* encryptTXT = malloc(strlen(plainTXT) + 1);
    for (int i = 0; i < strlen(plainTXT); i++) {
        if (plainTXT[i] >= 'a' && plainTXT[i] <= 'z') {
            encryptTXT[i] = (plainTXT[i] - 'a' + (key % 26)) % 26 + 'a';
        } else if (plainTXT[i] >= 'A' && plainTXT[i] <= 'Z') {
            encryptTXT[i] = (plainTXT[i] - 'A' + (key % 26)) % 26 + 'A';
        } else {
            encryptTXT[i] = plainTXT[i];
        }
    }
    printf("Encrypted Message: %s\n", encryptTXT);

    return encryptTXT;
}

int main(int argc, char *argv[]) {
    if (argc > 3 || argc < 2) {
        printf("Usage: %s <key> [text]\n", argv[0]);
        return 1;
    }

    int key = atoi(argv[1]);
    if (key < 0) {
        printf("Key must be a non-negative integer.\n");
        return 1;
    }

    char* plainTXT;
    char* encryptTXT;
    char* decryptTXT;

    if (argc == 3) {
        plainTXT = argv[2];
        encryptTXT = encrypt(plainTXT, key);

    } else {
        printf("Enter Message: ");
        plainTXT = malloc(100);
        fgets(plainTXT, 100, stdin);
        plainTXT[strcspn(plainTXT, "\n")] = 0;

        encryptTXT = encrypt(plainTXT, key);
    }

    decryptTXT = malloc(strlen(encryptTXT) + 1);
    for (int i = 0; i < strlen(encryptTXT); i++) {
        if (encryptTXT[i] >= 'a' && encryptTXT[i] <= 'z') {
            decryptTXT[i] = (encryptTXT[i] - 'a' - key + 26) % 26 + 'a';
        } else if (encryptTXT[i] >= 'A' && encryptTXT[i] <= 'Z') {
            decryptTXT[i] = (encryptTXT[i] - 'A' - key + 26) % 26 + 'A';
        } else {
            decryptTXT[i] = encryptTXT[i];
        }
    }

    printf("Decrypted Message: %s\n", decryptTXT);
    
    return 0;
}