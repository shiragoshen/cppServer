#include "server.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <sys/socket.h>
#include <unistd.h>

// Function to handle communication with a connected client
void handle_client(int client_sock) {
    char buffer[4096];
    int read_bytes;

    // Continuously read data from the client
    while ((read_bytes = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[read_bytes] = '\0';
        std::string request(buffer);
        std::istringstream iss(request);
        std::string command, user_id, video_id;
        // Parse the request to extract the command, user ID, and video ID
        iss >> command >> user_id >> video_id;

        std::cout << "Received command: " << command << " from user: " << user_id << " for video: " << video_id << std::endl;

        // Handle the "WATCH" command
        if (command == "WATCH") {
            // Record the user's watch history
            record_watch_history(user_id, video_id);
            std::string response = "Recorded: " + user_id + " watched " + video_id;
            // Send confirmation back to the client
            send(client_sock, response.c_str(), response.size(), 0);

        // Handle the "RECOMMEND" command
        } else if (command == "RECOMMEND") {
            std::string recommendations = get_recommendations(user_id, video_id);

            // Send the recommendations back to the client
            send(client_sock, recommendations.c_str(), recommendations.size(), 0);

        // Handle unknown commands
        } else {
            std::string response = "Unknown command: " + command;
            send(client_sock, response.c_str(), response.size(), 0);
        }
    }

    if (read_bytes == 0) {
        std::cout << "Client disconnected" << std::endl;
    } else if (read_bytes < 0) {
        perror("Error reading from client");
    }

    // Close the client socket after communication is complete
    close(client_sock);
}
