// server.h
#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

extern std::unordered_map<std::string, std::unordered_set<std::string>> videoWatchers;
extern const int SERVER_PORT;
extern const std::string WATCH_HISTORY_FILE;

void handle_client(int client_sock);
std::string get_recommendations(const std::string& user_id,const std::string& video_id);
void record_watch_history(const std::string& user_id, const std::string& video_id);


