#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

void start_client() {
    const char* host = "127.0.0.1";
    const int port = 5001;

    int client_socket;
    struct sockaddr_in server_addr;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return;
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(host);
    server_addr.sin_port = htons(port);

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Connection to server failed." << std::endl;
        close(client_socket);
        return;
    }
    std::cout << "Connected to server at " << host << ":" << port << std::endl;

    char buffer[1024];
    std::string message;
    while (true) {
        // Send message to server
        std::cout << "Client: ";
        std::getline(std::cin, message);
        send(client_socket, message.c_str(), message.size(), 0);

        // Receive reply from server
        memset(buffer, 0, sizeof(buffer));
        int recv_len = recv(client_socket, buffer, sizeof(buffer), 0);
        if (recv_len <= 0) {
            std::cout << "Server disconnected." << std::endl;
            break;
        }
        std::cout << "Server: " << buffer << std::endl;
    }

    // Close the connection
    close(client_socket);
    std::cout << "Client closed." << std::endl;
}

int main() {
    start_client();
    return 0;
}

