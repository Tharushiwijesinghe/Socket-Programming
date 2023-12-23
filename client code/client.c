#include <stdio.h>
#include <winsock2.h>

#define PORT 1900
#define SERVER_IP "192.168.8.177"
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;

    char buffer[BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("Error creating socket: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Set up server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(PORT);

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Unable to connect to server: %ld\n", WSAGetLastError());
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    // Send and receive messages
    while (1) {
        // Type a message to send to the server
        printf("Client (Type a message): ");
        gets(buffer);

        // Send the message to the server
        send(clientSocket, buffer, strlen(buffer), 0);

        // Receive and display the server's response
        memset(buffer, 0, sizeof(buffer));
        recv(clientSocket, buffer, BUFFER_SIZE, 0);
        printf("Server: %s\n", buffer);
    }

    // Cleanup
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
