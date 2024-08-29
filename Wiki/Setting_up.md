# Setting Up the Project

## Prerequisites

- **Node.js**: Ensure you have Node.js installed for running the web server.
- **MongoDB**: Required for setting up the database.
- **Android Studio**: Required for running the Android app.
- **Git LFS (Large File Storage)**: Used for managing large files in the project repository.

## Cloning the Repositories

 You will need to clone the following repostitories:

- https://github.com/shiragoshen/cppServer.git
- https://github.com/nogagur/YouTube
- https://github.com/nogagur/YouTubeAndroid

## Cloning the CPP server
1. Clone the server repository:
    ````
   git clone git@github.com:shiragoshen/cppServer.git
   ````
2. Build the server using MakeFile:
   ````
   make
   ````
3. Start the server:
   ````
   ./server_app
   ````
**Port Configuration:**

The server listens on port 5555 by default. If you need to change the port, you can modify the SERVER_PORT constant in the source code and rebuild the project.
   
## Cloning the NodeJS Server Repository (and the web app)

1. Clone the server repository:
    ````
   git clone git@github.com:nogagur/YouTube.git
   // Make sure you're on the branch called mainStage4
   cd server
   ````
2. Install Dependencies and run the NodeJS server:
   ````
   npm install
   npm start
   ````
3. Open the app in browser: go to "http://localhost:8081/" in your browser.

**Configuration:**

For configuration, you can modify the .env.local file in the config folder. You can adjust settings such as PORT, CPP_SERVER_HOST, and CPP_SERVER_PORT.
   
### MongoDB Data Base
1. Install Git Large File Storage:
   ````
   git lfs install
   git pull
   git lfs pull
2. Create a Mongo DB:
   - Create a new connection with this connection string: "mongodb://localhost:27017/"
   - Create a DB called Youtube
   - Create 3 collections in it: users, videos, comments
   - Download the json files from DB directory by clicking the link in the files, and import them accordingly to the MongoDB collections.

## Cloning the Android app repository

1. Clone the repository to your local machine
   ````
    git clone git@github.com:nogagur/YouTubeAndroid.git
   ````
3. open Android Studio and run the app on Pixel 3a API 34

**Configuration:**
* Note: By default, the server URL is set to http://10.0.2.2:8081/api/ and may not require modification unless you are connecting to a different server.

1. Navigate and open res > values > strings.xml file in a text editor or within Android Studio.
2. Find the line <string name="BaseUrl">http://10.0.2.2:8081/api/</string>.
3. Change the URL within the <string> tags to the desired server URL. For example:
   <string name="BaseUrl">http://your-new-server-url.com/api/</string>
4. Save the strings.xml file after making the modifications.
5. rebuild the App to ensure that the changes are applied.
