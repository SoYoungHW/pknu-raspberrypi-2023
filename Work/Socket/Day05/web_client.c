#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *message);

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
		int sock;
		struct sockaddr_in serv_adr;
		char message[30];
		int str_len;

		if (argc != 3)
		{
				printf("Usage : %s <IP> <port> \n", argv[0]);
				exit(1);
		}

		sock = socket(PF_INET, SOCK_STREAM, 0);
		if (sock == -1)
				error_handling("socket() error");

		memset(&serv_adr, 0, sizeof(serv_adr));
		serv_adr.sin_family = AF_INET;
		serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
		serv_adr.sin_port = htons(atoi(argv[2]));

		if (connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
				error_handling("connect() error");

		str_len = read(sock, message, sizeof(message)-1);
		if (str_len == -1)
				error_handling("read() error");

		printf("Message from server : %s \n", message);
		close(sock);
		return 0;
}

void error_handling(char *message)
{
		fputs(message, stderr);
		fputc('\n', stderr);
		exit(1);
}

