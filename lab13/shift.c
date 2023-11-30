#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* encrypt(char* plainTXT, int* keys) {
    char* encryptTXT = malloc(strlen(plainTXT) + 1);

    srand(time(NULL));

    for (int i = 0; i < strlen(plainTXT); i++) {
        keys[i] = rand() % 26;
    }

    for (int i = 0; i < strlen(plainTXT); i++) {
        if (plainTXT[i] >= 'a' && plainTXT[i] <= 'z') {
            encryptTXT[i] = (plainTXT[i] - 'a' + keys[i]) % 26 + 'a';
        } else if (plainTXT[i] >= 'A' && plainTXT[i] <= 'Z') {
            encryptTXT[i] = (plainTXT[i] - 'A' + keys[i]) % 26 + 'A';
        } else {
            encryptTXT[i] = plainTXT[i];
        }
    }

    return encryptTXT;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        printf("Usage: %s [text]\n", argv[0]);
        return 1;
    }

    char* plainTXT;
    char* encryptTXT;
    char* decryptTXT;

    // Allocate randomized key for each character position
    int* keys;

    // If text is provided as CMD line argument
    if (argc == 2) {
        plainTXT = argv[1];

        keys = (int*) malloc(strlen(plainTXT) * sizeof(int));

        encryptTXT = encrypt(plainTXT, keys);
        printf("Encrypted Message: %s\n", encryptTXT);

    } else {
        // User input if no text is provided through CMD line
        printf("Enter Message: ");
        plainTXT = malloc(100);
        fgets(plainTXT, 100, stdin);
        plainTXT[strcspn(plainTXT, "\n")] = 0;

        keys = (int*) malloc(strlen(plainTXT) * sizeof(int));

        encryptTXT = encrypt(plainTXT, keys);

        printf("Encrypted Message: %s\n", encryptTXT);
    }

    decryptTXT = malloc(strlen(encryptTXT) + 1);
    for (int i = 0; i < strlen(encryptTXT); i++) {
        printf("%d ", keys[i]);
        if (encryptTXT[i] >= 'a' && encryptTXT[i] <= 'z') {
            decryptTXT[i] = (encryptTXT[i] - 'a' - keys[i] + 26) % 26 + 'a';
        } else if (encryptTXT[i] >= 'A' && encryptTXT[i] <= 'Z') {
            decryptTXT[i] = (encryptTXT[i] - 'A' - keys[i] + 26) % 26 + 'A';
        } else {
            decryptTXT[i] = encryptTXT[i];
        }
    }

    printf("Decrypted Message: %s\n", decryptTXT);
    
    return 0;
}