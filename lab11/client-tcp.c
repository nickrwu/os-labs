#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define IP_ADDRESS "127.0.0.1";
#define PORT 8080;
 
int main() {
    char *ip = IP_ADDRESS;

    // Define variables
    struct sockaddr_in addr;
    int sock = 0;
    socklen_t addr_size;
    char buffer[1024] = {0};
    char *message = "Hello World.";

    // Create TCP socket
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("[-]Socket error");
        return -1;
    }
    printf("[+]TCP server socket created.\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = PORT;
    addr.sin_addr.s_addr = inet_addr(ip);

    // Send connection request to server
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("[-]Connect failed");
        return -1;
    } else {
        printf("[+]Connection request sent.\n");
    }

    // Send message to server
    printf("Client: %s\n", message);
    send(sock, message, strlen(message), 0);
    
    // Receive reply message from server
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // Close socket connection
    close(sock);
    printf("[+]Disconnected from the server.\n");

    return 0;
}