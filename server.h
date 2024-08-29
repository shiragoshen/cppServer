#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

// A map to keep track of which users have watched which videos
extern std::unordered_map<std::string, std::unordered_set<std::string>> videoWatchers;

// The port number on which the server listens for incoming connections
extern const int SERVER_PORT;

// The file where watch history is stored
extern const std::string WATCH_HISTORY_FILE;

// Function to handle communication with a connected client
void handle_client(int client_sock);

// Function to generate video recommendations for a user
std::string get_recommendations(const std::string& user_id,const std::string& video_id);

// Function to record the watch history of users and videos
void record_watch_history(const std::string& user_id, const std::string& video_id);


