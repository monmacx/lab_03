#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	int sock = 0, connfd = 0;
	struct sockaddr_in serv_addr; 

	char sendBuff[1025];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&server_address, '0', sizeof(server_address));
	memset(sendBuff, '0', sizeof(sendBuff)); 

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(5000); 

	bind(sock, (struct sockaddr*)&server_address, sizeof(server_address)); 

	listen(sock, 1); 

    connfd = accept(sock, (struct sockaddr*)NULL, NULL); 

    write(connfd, sendBuff, ); 

    close(connfd);
    sleep(1);
}