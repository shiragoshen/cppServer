# YouTube Project - Fourth Part

For complete instructions on setting up and running the project, please visit the wiki directory.

## Video Recommendation System

This project implements a C++ server that provides personalized video recommendations based on user viewing habits. The recommendation algorithm identifies relevant content by analyzing the watch history of users who have watched similar videos.

## Overview

The Video Recommendation System is designed to suggest videos to users based on the viewing patterns of other users with similar interests. The C++ server communicates with a Node.js backend, which in turn interacts with web and Android applications. The primary focus is to enhance user engagement by providing highly relevant video recommendations.

## Recommendation Algorithm

The recommendation algorithm suggests videos to a user by leveraging the viewing habits of other users who have watched similar content. Below is a detailed explanation of how the algorithm works:

1. **User's Watch History**:
    - The algorithm checks the user's watch history to ensure that recommendations exclude any videos the user has already seen.

2. **Identifying Shared Viewers**:
    - It identifies other users who have watched the same video currently being viewed and examines the other videos they have watched.

3. **Generating Recommendations**:
    - The algorithm then recommends videos that these similar users have watched but the current user has not, prioritizing those most relevant.
      
4. **Output**:
    - The recommended video IDs are returned in JSON format, helping users discover new content aligned with their interests.

This collaborative filtering approach delivers personalized video suggestions, enhancing the user experience by promoting content that users are likely to enjoy.
