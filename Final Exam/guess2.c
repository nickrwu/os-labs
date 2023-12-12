
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

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

    // Guessing the key based on the most frequent character
    // Initialize the frequency array
    int freq[256] = {0};
    
    // Initialize the most frequent character
    int i, max = -1;
    char most_freq_char;


    for(i = 0; i < strlen(cipher); i++) {
        // For each character, increment the frequency
        freq[(int)cipher[i]]++;

        // Update the most frequent character
        if(max < freq[cipher[i]]){
            max = freq[cipher[i]];
            most_freq_char = cipher[i];
        }
    }

    // Guess the key based on the most frequent character being letter 'e'
    int key = (most_freq_char - 'e' + 26) % 26;

    printf("Guessed key is: %d\n", key);

    return 0;
}