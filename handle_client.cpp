// handle_client.cpp
#include "server.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <sys/socket.h>
#include <unistd.h>

void handle_client(int client_sock) {
    char buffer[4096];
    int read_bytes;

    while ((read_bytes = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[read_bytes] = '\0';
        std::string request(buffer);
        std::istringstream iss(request);
        std::string command, user_id, video_id;
        iss >> command >> user_id >> video_id;

        std::cout << "Received command: " << command << " from user: " << user_id << " for video: " << video_id << std::endl;
        if (command == "WATCH") {
            record_watch_history(user_id, video_id);
            std::string response = "Recorded: " + user_id + " watched " + video_id;
            send(client_sock, response.c_str(), response.size(), 0);
            std::cout << response << std::endl;
        } else if (command == "RECOMMEND") {
            std::string response = get_recommendations(user_id, video_id);
            send(client_sock, response.c_str(), response.size(), 0);
            std::cout << response << std::endl;
        } else {
            std::string response = "Unknown command: " + command;
            send(client_sock, response.c_str(), response.size(), 0);
            std::cout << response << std::endl;
        }
    }

    if (read_bytes == 0) {
        std::cout << "Client disconnected" << std::endl;
    } else if (read_bytes < 0) {
        perror("Error reading from client");
    }

    close(client_sock);
}
