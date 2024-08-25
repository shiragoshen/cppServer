#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;

    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        return 1;
    }

    // Define the server address
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
        perror("Error connecting to server");
        close(sock);
        return 1;
    }

    // Send data to the server
    const char* data_addr = "I'm a message";
    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0);
    if (sent_bytes < 0) {
        perror("Error sending data");
        close(sock);
        return 1;
    }

    // Receive data from the server
    char buffer[4096];
    int read_bytes = recv(sock, buffer, sizeof(buffer) - 1, 0); // Leave space for null-terminator
    if (read_bytes == 0) {
        cout << "Connection closed by server" << endl;
    } else if (read_bytes < 0) {
        perror("Error reading data");
    } else {
        buffer[read_bytes] = '\0'; // Ensure null-termination
        cout << "Received from server: " << buffer << endl;
    }

    // Close the socket
    close(sock);
    return 0;
}