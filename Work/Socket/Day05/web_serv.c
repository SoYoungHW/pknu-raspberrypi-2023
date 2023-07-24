#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void handle_request(int client_socket) {
    char response[] = "HTTP/1.1 200 OK\r\n"
                      "Server: Linux Web Server\r\n"
                      "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                      "<!DOCTYPE html>\r\n"
                      "<html><head><title>My Web Page</title>\r\n"
                      "<style>body {background-color: #FFFF00}</style></head>\r\n"
                      "<body><center><h1>Hello world!!</h1><br>\r\n"
                      "<img src=\"image.jpg\"></center></body></html>\r\n";

    write(client_socket, response, strlen(response));
    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length;

    // 소켓 생성
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // 소켓 설정
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = 9998;

    // 소켓에 주소 할당
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }

    // 연결 수신 대기 상태로 진입
    if (listen(server_socket, 3) < 0) {
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }

   // printf("Server listening on port %d\n", PORT);

    while (1) {
        // 클라이언트 연결 수락
        client_address_length = sizeof(client_address);
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length);
        if (client_socket < 0) {
            perror("Failed to accept");
            exit(EXIT_FAILURE);
        }

        // 클라이언트 요청 처리
        handle_request(client_socket);
    }

    // 소켓 닫기
    close(server_socket);

    return 0;
}
