// main.cpp
#include "server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <unistd.h>

std::unordered_map<std::string, std::unordered_set<std::string>> videoWatchers;
const int SERVER_PORT = 5555;
const std::string WATCH_HISTORY_FILE = "watch_history.txt";

int main() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        close(server_sock);
        return 1;
    }

    if (listen(server_sock, 5) < 0) {
        perror("Error listening on socket");
        close(server_sock);
        return 1;
    }

    std::cout << "Server is listening on port " << SERVER_PORT << std::endl;

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("Error accepting client connection");
            continue;
        }

        std::thread client_thread(handle_client, client_sock);
        client_thread.detach();
    }

    close(server_sock);
    return 0;
}
