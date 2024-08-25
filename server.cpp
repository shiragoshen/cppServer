#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/json.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

mongocxx::instance instance{}; // This should exist for the lifetime of your application

// Function to handle communication with each client
void handle_client(int client_sock, mongocxx::client& mongo_client) {
    char buffer[4096];
    int read_bytes;

    // MongoDB collection access
    auto collection = mongo_client["yourDatabase"]["yourCollection"];

    // Receive data from the client
    while ((read_bytes = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[read_bytes] = '\0'; // Null-terminate the received data
        std::cout << "Received from client: " << buffer << std::endl;

        // Example MongoDB operation: find documents
        auto cursor = collection.find(make_document(kvp("key", "value")));

        for(auto&& doc : cursor) {
            std::cout << bsoncxx::to_json(doc) << std::endl;
        }

        // Echo the data back to the client
        int sent_bytes = send(client_sock, buffer, read_bytes, 0);
        if (sent_bytes < 0) {
            perror("Error sending to client");
            break;
        }
    }

    if (read_bytes == 0) {
        std::cout << "Client disconnected" << std::endl;
    } else if (read_bytes < 0) {
        perror("Error reading from client");
    }

    // Close the client socket after communication is done
    close(client_sock);
}

int main() {
    const int server_port = 5555;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        return 1;
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("Error binding socket");
        close(sock);
        return 1;
    }

    if (listen(sock, 5) < 0) {
        perror("Error listening on socket");
        close(sock);
        return 1;
    }

    // MongoDB Client
    mongocxx::client mongo_client{mongocxx::uri{"mongodb://localhost:27017"}};

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);

    while (true) {
        std::cout << "Waiting for a client to connect..." << std::endl;
        int client_sock = accept(sock, (struct sockaddr*)&client_sin, &addr_len);
        if (client_sock < 0) {
            perror("Error accepting client");
            continue;
        }

        // Create a new thread for each client, pass MongoDB client as well
        std::thread client_thread(handle_client, client_sock, std::ref(mongo_client));
        client_thread.detach(); // Detach the thread so it can run independently
    }

    close(sock);
    return 0;
}