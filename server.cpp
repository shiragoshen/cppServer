// #include <iostream>
// #include <fstream>
// #include <string>
// #include <thread>
// #include <map>
// #include <vector>
// #include <sstream>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <unistd.h>
// #include <unordered_map>
// #include <unordered_set>

// // Maps video ID to a set of users who have watched it
// std::unordered_map<std::string, std::unordered_set<std::string>> videoWatchers;

// // Port the server will listen on
// const int SERVER_PORT = 5555;

// // Path to the watch history file
// const std::string WATCH_HISTORY_FILE = "watch_history.txt";

// void handle_client(int client_sock) {
//     char buffer[4096];
//     int read_bytes;

//     while ((read_bytes = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
//         buffer[read_bytes] = '\0'; // Null-terminate the received data
//         std::string request(buffer);

//         std::istringstream iss(request);
//         std::string command, user_id, video_id;
//         iss >> command >> user_id >> video_id;

//         if (command == "WATCH") {
//             // Record the video watch history
//             videoWatchers[video_id].insert(user_id);
//             std::ofstream file(WATCH_HISTORY_FILE, std::ios::app);
//             if (file.is_open()) {
//                 file << user_id << " " << video_id << std::endl;
//                 file.close();
//             }
//             std::string response = "Recorded: " + user_id + " watched " + video_id;
//             send(client_sock, response.c_str(), response.size(), 0);
//         } else if (command == "RECOMMEND") {
//             std::unordered_map<std::string, int> recommendations;
//             // Find other videos watched by the same users
//             for (const auto& uid : videoWatchers[video_id]) {
//                 for (const auto& vid_pair : videoWatchers) {
//                     if (vid_pair.first != video_id && vid_pair.second.find(uid) != vid_pair.second.end()) {
//                         recommendations[vid_pair.first]++;
//                     }
//                 }
//             }

//             // Convert recommendations map to sorted vector to send top recommendations
//             std::vector<std::pair<std::string, int>> sorted_recommendations(recommendations.begin(), recommendations.end());
//             std::sort(sorted_recommendations.begin(), sorted_recommendations.end(),
//                       [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
//                           return a.second > b.second;
//                       });

//             std::ostringstream oss;
//             oss << "Recommendations for " << video_id << ": ";
//             for (const auto& rec : sorted_recommendations) {
//                 oss << rec.first << " (" << rec.second << " views), ";
//             }

//             std::string response = oss.str();
//             send(client_sock, response.c_str(), response.size(), 0);
//         } else {
//             std::string response = "Unknown command: " + command;
//             send(client_sock, response.c_str(), response.size(), 0);
//         }
//     }

//     if (read_bytes == 0) {
//         std::cout << "Client disconnected" << std::endl;
//     } else if (read_bytes < 0) {
//         perror("Error reading from client");
//     }

//     close(client_sock);
// }


// int main() {
//     int server_sock = socket(AF_INET, SOCK_STREAM, 0);
//     if (server_sock < 0) {
//         perror("Error creating socket");
//         return 1;
//     }

//     struct sockaddr_in server_addr;
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.s_addr = INADDR_ANY;
//     server_addr.sin_port = htons(SERVER_PORT);

//     if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
//         perror("Error binding socket");
//         close(server_sock);
//         return 1;
//     }

//     if (listen(server_sock, 5) < 0) {
//         perror("Error listening on socket");
//         close(server_sock);
//         return 1;
//     }

//     std::cout << "Server is listening on port " << SERVER_PORT << std::endl;

//     while (true) {
//         struct sockaddr_in client_addr;
//         socklen_t client_len = sizeof(client_addr);
//         int client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_len);
//         if (client_sock < 0) {
//             perror("Error accepting client connection");
//             continue;
//         }

//         std::thread client_thread(handle_client, client_sock);
//         client_thread.detach(); // Detach the thread to handle multiple clients
//     }

//     close(server_sock);
//     return 0;
// }