#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE] = {0};

    // 소켓 생성
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // 서버 설정
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // 주소 변환
    if (inet_pton(AF_INET, SERVER_IP, &(server_address.sin_addr)) <= 0) {
        perror("Failed to convert IP address");
        exit(EXIT_FAILURE);
    }

    // 서버에 연결
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Failed to connect");
        exit(EXIT_FAILURE);
    }

    // 서버로부터 응답 받기
    ssize_t bytes_received = 0;
    while ((bytes_received = read(client_socket, buffer, BUFFER_SIZE)) > 0) {
        printf("%s", buffer);
        memset(buffer, 0, BUFFER_SIZE);
    }
    if (bytes_received == -1) {
        perror("Failed to receive response");
        exit(EXIT_FAILURE);
    }

    // 소켓 닫기
    close(client_socket);

    return 0;
}
