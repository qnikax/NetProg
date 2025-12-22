#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Socket error\n";
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12241);
    inet_pton(AF_INET, "172.16.40.1", &server_addr.sin_addr);

    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Connect error\n";
        close(sock);
        return 1;
    }

    std::string message = "Hello, echo!";
    send(sock, message.c_str(), message.size(), 0);

    char buffer[1024];
    int len = recv(sock, buffer, sizeof(buffer), 0);
    if (len > 0) {
        buffer[len] = 0;
        std::cout << "Echo from server: " << buffer << std::endl;
    }

    close(sock);
    return 0;
}
