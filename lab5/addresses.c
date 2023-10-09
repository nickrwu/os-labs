#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    if (argc != 2 || atoi(argv[1]) < 1) {
        printf("Usage: ./addresses {address}\n");
        exit(1);
    }

    unsigned long address = atoi(argv[1]);

    // 32-bit virtual addresses; 4 KB page size
    // 2^32 = 4,294,967,296 bytes; 2^12 = 4,096 bytes = 4 KB
    // 4,294,967,296/4,096 = 1,048,576 pages
    // sqrt(4,294,967,296/4,096) = 1,024 bits for page number, 12 bits for offset

    // Right shift address by 12 bits to get page number 
    uint32_t page_number = address >> 12;
    // Mask address with 0xFFF (4095) to get offset
    uint32_t offset = address & 0xFFF;   

    printf("Page Number: %d, Offset: %d\n", page_number, offset);

    return 0;
}