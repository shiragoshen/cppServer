#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>


// Function to handle communication with each client
void handle_client(int client_sock) {
    char buffer[4096];
    int read_bytes;

    // Receive data from the client
    while ((read_bytes = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[read_bytes] = '\0'; // Null-terminate the received data
        std::cout << "Received from client: " << buffer << std::endl;

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
    std::cout << "Socket created" << std::endl;

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

    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);

    while (true) {
        std::cout << "Waiting for a client to connect..." << std::endl;
        int client_sock = accept(sock, (struct sockaddr*)&client_sin, &addr_len);
        if (client_sock < 0) {
            perror("Error accepting client");
            continue;
        }

        // Create a new thread for each client
        std::thread client_thread(handle_client, client_sock);
        client_thread.detach(); // Detach the thread so it can run independently
    }

    close(sock);
    return 0;
}