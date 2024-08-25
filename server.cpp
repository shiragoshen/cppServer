#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {
    const int server_port = 5555;
    const int buffer_size = 4096;
    
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        return 1;
    }

    // Define server address
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    // Bind the socket to the address
    if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        close(sock);
        return 1;
    }

    // Listen for incoming connections
    if (listen(sock, 5) < 0) {
        perror("error listening on socket");
        close(sock);
        return 1;
    }

    // Accept a client connection
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr*)&client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
        close(sock);
        return 1;
    }

    // Receive data from the client
    char buffer[buffer_size];
    int read_bytes = recv(client_sock, buffer, buffer_size, 0);
    if (read_bytes == 0) {
        // Client closed the connection
        cout << "Client disconnected" << endl;
        close(client_sock);
    } else if (read_bytes < 0) {
        // Error occurred
        perror("error reading from client");
        close(client_sock);
    } else {
        // Print received data
        cout << "Received: " << buffer << endl;

        // Send data back to the client (echo)
        int sent_bytes = send(client_sock, buffer, read_bytes, 0);
        if (sent_bytes < 0) {
            perror("error sending to client");
        }
    }

    // Close the sockets
    close(client_sock);
    close(sock);

    return 0;
}