## Usage
To compile all the files, run `make build`

## Program Description
**Caesar**: `./caesar <key> [text]`
* `caesar.c` takes an inputted key and shifts each character of the inputted text by that amount of characters. It provides the encrypted and decrypted message to the user.

**Crack:** `./crack [text]`
* `crack.c` uses a brute force method. It takes in an encrypted text as an input and prints out all 26 possible caesar cipher key shifts. The user can then browse through and analyze the decrypted text for anything meaningful.

**Shift:** `./shift [text]`
* `shift.c` is an improved version of the Caesar Cipher which takes in an plain text input and shifts each character by a randomly generated key.