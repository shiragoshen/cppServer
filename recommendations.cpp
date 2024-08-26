#include "server.h"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <sstream>

// Function to generate and return video recommendations in JSON format
std::string get_recommendations(const std::string& user_id, const std::string& video_id) {
    std::unordered_map<std::string, int> recommendations; // Map to track recommended videos and their shared viewers
    std::unordered_set<std::string> already_watched;  // Set to track videos the user has already watched

    // Check if the user has watched videos
    if (videoWatchers.find(user_id) != videoWatchers.end()) {
        already_watched = videoWatchers[user_id];  // Retrieve the user's watched videos
    }

    // Check if the video_id is watched by other users
    if (videoWatchers.find(video_id) != videoWatchers.end()) {
        for (const auto& user : videoWatchers[video_id]) {  // Loop over all users who watched the given video
            for (const auto& entry : videoWatchers) {  // Loop over all videos
                if (entry.first != video_id && entry.second.find(user) != entry.second.end()) {  // If it's a different video and the user watched it
                    if (already_watched.find(entry.first) == already_watched.end()) {  // Only recommend videos the user hasn't seen
                        recommendations[entry.first]++;  // Increment the count of shared viewers for this video
                    }
                }
            }
        }
    }

    // Convert the map of video recommendations to a sorted vector to return top recommendations
    std::vector<std::pair<std::string, int>> sorted_recommendations;
    for (const auto& rec : recommendations) {
        sorted_recommendations.emplace_back(rec.first, rec.second);
    }

    // Sort the recommendations by the number of shared viewers, descending
    std::sort(sorted_recommendations.begin(), sorted_recommendations.end(),
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });

    // Prepare the vector of video IDs to return
    std::vector<std::string> recommended_video_ids;
    for (const auto& rec : sorted_recommendations) {
        recommended_video_ids.push_back(rec.first);  // Push only the video IDs into the vector
    }

    // Convert the vector of video IDs into a JSON array string
    std::ostringstream oss;
    oss << "[";
    for (size_t i = 0; i < recommended_video_ids.size(); ++i) {
        oss << "\"" << recommended_video_ids[i] << "\"";
        if (i != recommended_video_ids.size() - 1) {
            oss << ", ";
        }
    }
    oss << "]";

    return oss.str();
}
