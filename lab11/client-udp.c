#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define IP_ADDRESS "127.0.0.1"
#define PORT 8080
 
int main() {
    char *ip = IP_ADDRESS;

    // Define variables
    struct sockaddr_in addr;
    int sock = 0;
    socklen_t addr_size;
    char buffer[1024] = {0};
    char *message = "Hello World.";

    // Create UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("[-]Socket error");
        return -1;
    }
    printf("[+]UDP client socket created.\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(ip);

    // Send message to server
    printf("Client: %s\n", message);
    sendto(sock, message, strlen(message), 0, (struct sockaddr*)&addr, sizeof(addr));
    
    // Receive reply message from server
    recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &addr_size);
    printf("Server: %s\n", buffer);

    // Close socket connection
    close(sock);
    printf("[+]Disconnected from the server.\n");

    return 0;
}