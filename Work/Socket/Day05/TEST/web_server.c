#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>
void error_handling(char *message);

#define BUF_SIZE 1024

char webpage[] = "HTTP/1.1 200 OK\r\n"
				"Server:Linux Web Server\r\n"
				"Content-Type: text/html; charset=UTF-8\r\n\r\n"
				"<!DOCTYPE html>\r\n"
				"<html><head><title> My Web Page </title>\r\n"
				"<style>body {background-color: #FFFF00}</style></head>\r\n"
				"<body><center><h1>Hello world!!</h1><br>\r\n"
				"<img src=\"image.jpg\" /></center></body></html>\r\n";

char* buffer = (char*)malloc(*)

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_adr;
	struct sockaddr_in clnt_adr;
	socklen_t clnt_adr_size;

	if (argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	// 소켓
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
			error_handling("socket() error");

	// 설정
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	// 바인드
	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
			error_handling("bind() error");

	// 리슨
	if (listen(serv_sock, 5) == -1)
			error_handling("listen() error");

	printf("Server Listening...");
			
	while(1)
	{
		// 엑셉트
		clnt_adr_size = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&serv_adr, &clnt_adr_size);
		if (clnt_sock == -1)
			error_handling("accept() error");

		// 이미지 (클라이언트 요청처리)
		long img_size;
		char buffer[BUF_SIZE];
		memset(buffer, 0, sizeof(buffer));
		read(clnt_sock, buffer, sizeof(buffer), 0);
			
		if (strstr(buffer,"GET /image.jpg") != NULL)
		{
			int file = open("image.jpg", O_RDONLY);

			if (file == -1)
				error_handling("open() error");
			else
			{
				char image_header[] = "HTTP/1.1 200 OK\r\n"
									"Server: Linux Web Server\r\n"
									"Content-Type: image/jpg\r\n\r\n",
									"Content_Length: %ld\r\n\r\n",
									img_size
									

				write(clnt_sock, image_header, sizeof(image_header));

				while(1)
				{
					int reader = read(file, buffer, sizeof(buffer));
					if (reader == -1)
					{
						error_handling("read() error");
						break;
					}
	
					write(clnt_sock, buffer, reader);
				}

				close(file);
			}
		}

		else
		{
			write(clnt_sock, webpage, sizeof(webpage));
		}
			
		close(clnt_sock);
	}

	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
		fputs(message, stderr);
		fputc('\n', stderr);
		exit(1);
}
