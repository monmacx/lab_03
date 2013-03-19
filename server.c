#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include "file_read.h"
#include "file_sender.h"

int main(int argc, char *argv[])
{
	if(argc != 2) {
		printf("Expected commandline parameter with file name was not specified.\n");
		return 1;
	} else {
		struct file_info info = read_file(argv[1]); 
		printf("%s\n", info.content);
		// Defining and initializing socket
		int sock = 0, connfd = 0;
		struct sockaddr_in server_address; 

		sock = socket(AF_INET, SOCK_STREAM, 0);
		memset(&server_address, '0', sizeof(server_address));

		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = htonl(INADDR_ANY);
		server_address.sin_port = htons(5000); 

		// Bind socket to address
		bind(sock, (struct sockaddr*)&server_address, sizeof(server_address)); 

		int i = 5;
		// Starting server
		while(i--) {
			// Start listening socket
			listen(sock, 10);

			//Initializing data for starting sending file in the separate thread
			struct _message mes;
			mes.file = info.content;
			mes.size = info.size;

			// Accepting connection and getting connection identifier
			mes.index = accept(sock, (struct sockaddr*)NULL, NULL); 
			pthread_t thread;
			pthread_create(&thread, NULL, send_file_to_client, (void*)&mes);
		}
		

		close(sock);
		free(info.content);
		return 0;
	}
}