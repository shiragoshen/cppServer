// recommendations.cpp
#include "server.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <sstream>

// Function to generate and return video recommendations
std::string get_recommendations(const std::string& user_id, const std::string& video_id) {
    std::unordered_map<std::string, int> recommendations; // Map to track recommended videos and their shared viewers
    std::unordered_set<std::string> already_watched;  // Set to track videos the user has already watched
    if (videoWatchers.find(user_id) != videoWatchers.end()) {
        already_watched = videoWatchers[user_id];  // Assume each user's watched videos are tracked
    }

    if (videoWatchers.find(video_id) != videoWatchers.end()) {
    for (const auto& user : videoWatchers[video_id]) {  // Loop over all users who watched the given video
        for (const auto& entry : videoWatchers) {  // Loop over all videos
            if (entry.first != video_id && entry.second.find(user) != entry.second.end()) {  // If it's a different video and the user watched it
                recommendations[entry.first]++;  // Increment the count of shared viewers for this video
            }
        }
    }
}

    // Convert the map of video recommendations to a sorted vector to send top recommendations
    std::vector<std::pair<std::string, int>> sorted_recommendations;
    for (const auto& rec : recommendations) {
        sorted_recommendations.emplace_back(rec.first, rec.second);
    }

    std::sort(sorted_recommendations.begin(), sorted_recommendations.end(),
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second > b.second; // Sort by the number of shared viewers, descending
              });

    // Formulate the recommendation string
    std::ostringstream oss;
    oss << "Personalized Recommendations for " << user_id << ": ";
    for (const auto& rec : sorted_recommendations) {
        oss << rec.first << " (" << rec.second << " views), ";
    }

    return oss.str();
}
