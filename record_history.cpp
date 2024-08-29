#include "server.h"
#include <fstream>
#include <string>

// Function to record the video watch history
void record_watch_history(const std::string& user_id, const std::string& video_id) {
    // Update the in-memory watch history
    videoWatchers[video_id].insert(user_id);

    // Append the watch event to the watch history file
    std::ofstream file(WATCH_HISTORY_FILE, std::ios::app);
    if (file.is_open()) {
        file << user_id << " " << video_id << std::endl;
        file.close();
    }
}
