#include "server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>

// Global map to track which users have watched which videos
std::unordered_map<std::string, std::unordered_set<std::string>> videoWatchers;

const int SERVER_PORT = 5555; // The port number the server will listen on
const std::string WATCH_HISTORY_FILE = "watch_history.txt"; // File to store watch history

int main() {
    // Create a TCP socket
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Error creating socket");
        return 1;
    }

    // Define the server address
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    // Bind the socket to the specified IP and port
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        close(server_sock);
        return 1;
    }

    // Start listening for incoming connections
    if (listen(server_sock, 5) < 0) {
        perror("Error listening on socket");
        close(server_sock);
        return 1;
    }

    std::cout << "Server is listening on port " << SERVER_PORT << std::endl;

    // Main server loop to accept and handle incoming client connections
    while (true) {
        struct sockaddr_in client_addr;

        // Accept an incoming client connection
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("Error accepting client connection");
            continue;
        }

        // Handle the client connection in a new thread
        std::thread client_thread(handle_client, client_sock);
        client_thread.detach();
    }

    close(server_sock);
    return 0;
}
