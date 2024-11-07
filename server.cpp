#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

void start_server() {
    const char* host = "127.0.0.1";
    const int port = 5001;

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Failed to create socket." << std::endl;
        return;
    }

    // Set server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(host);
    server_addr.sin_port = htons(port);

    // Bind the socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Binding failed." << std::endl;
        close(server_socket);
        return;
    }

    // Listen for incoming connections
    if (listen(server_socket, 1) < 0) {
        std::cerr << "Listening failed." << std::endl;
        close(server_socket);
        return;
    }
    std::cout << "Server listening on " << host << ":" << port << std::endl;

    // Accept a client connection
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
    if (client_socket < 0) {
        std::cerr << "Failed to accept client connection." << std::endl;
        close(server_socket);
        return;
    }
    std::cout << "Connection established with client." << std::endl;

    char buffer[1024];
    std::string reply;
    while (true) {
        // Receive message from client
        memset(buffer, 0, sizeof(buffer));
        int recv_len = recv(client_socket, buffer, sizeof(buffer), 0);
        if (recv_len <= 0) {
            std::cout << "Client disconnected." << std::endl;
            break;
        }
        std::cout << "Client: " << buffer << std::endl;

        // Send reply to client
        std::cout << "Server: ";
        std::getline(std::cin, reply);
        send(client_socket, reply.c_str(), reply.size(), 0);
    }

    // Close the connections
    close(client_socket);
    close(server_socket);
    std::cout << "Server closed." << std::endl;
}

int main() {
    start_server();
    return 0;
}

