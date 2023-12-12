#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void strToBin(char* txt, char* binary) {
    // Iterate through each character in the string
    for (int i = 0; i < strlen(txt); i++) {
        unsigned char val = txt[i];
        // Iterate through each bit in the character
        for(int j = 7; j >= 0; j--) {
            // Convert the bit to a string
            char bit[2];
            sprintf(bit, "%d", (val >> j) & 1);

            // Add the bit to the binary string
            strcat(binary, bit);
        }
    }
}

char* binToStr(char* binary) {
    int textLen = strlen(binary) / 8;
    
    // Allocate memory for the decoded text
    char* text = (char*)malloc(sizeof(char) * (textLen + 1));

    // Add null to the end of the string
    text[textLen] = '\0';

    for (int i = 0; i < textLen; i++) {
        char byte[9];
        // Copy the next 8 bits into the byte string
        strncpy(byte, binary + (i * 8), 8);
        byte[8] = '\0';

        int val = 0;
        // Convert the byte string to an integer
        for (int j = 0; j < 8; j++) {
            val = val * 2 + (byte[j] - '0');
        }

        // Convert the integer to a character
        text[i] = (char)val;
    }

    return text;
}

char * xorBinary(char* binary, char* key) {
    char* output = (char*)malloc(sizeof(char) * strlen(binary));
    for (int i=0; i < strlen(binary); i++) {
        // Convert the bit to a string
        char bit[2];
        
        // Perform XOR on the bit with the key
        sprintf(bit, "%d", binary[i] ^ key[i % strlen(key)]);
        
        // Add the bit to the output string
        strcat(output, bit);
    }

    return output;
}

int main(int argc, char *argv[]) {
   if (argc > 3 || argc < 2) {
        printf("Usage: %s <key> [text] \n", argv[0]);
        return 1;
    }

    // Input key (Must be a binary string)
    char* key = argv[1];
    if (strlen(key) < 0) {
        printf("Key must be a non-negative binary string.\n");
        return 1;
    }
    
    char * txt;

    if (argc == 3) {
        // Message passed as argument
        txt = argv[1];

        printf("Message: %s\n", txt);

    } else {
        // Message passed as input
        printf("Enter Encrypted Message: ");
        txt = malloc(100);
        fgets(txt, 100, stdin);
        txt[strcspn(txt, "\n")] = 0;

        printf("Message: %s\n", txt);
    }

    // Initialize empty binary string
    char binary[strlen(txt) * 8 + 1];
    strcpy(binary, "");

    // Encoding the message by applying XOR with the key
    strToBin(txt, binary);
    char * output = xorBinary(binary, key);

    printf("Encoded binary: %s\n", output);

    // Decoding the message by applying XOR with the same key
    xorBinary(binary, key);
    output = binToStr(binary);
    printf("Decoded binary: %s\n", binary);
    printf("Decoded message: %s\n", output);

    return 0;
}