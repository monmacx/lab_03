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
	if(argc != 2) {
		printf("Expected commandline parameter with file name was not specified.\n");
		return 1;
	} else {
		FILE *pFile;
		int lSize;
		char * buffer;
		size_t result;

		pFile = fopen(argv[1], "r");
		if (pFile == NULL) {
			fputs("Opening file error", stderr);
			exit(1);
		}

		// Obtaining file size
		fseek(pFile, 0, SEEK_END);
		lSize = ftell(pFile);
		rewind(pFile);

		buffer = (char*)malloc(sizeof(char)*lSize);
		if (buffer == NULL) {
			fputs("Memory error", stderr);
			exit(2);
		}

		result = fread(buffer, 1, lSize, pFile);
		if (result != lSize) {
			fputs("Reading error", stderr);
			exit(3);
		}

		int sock = 0, connfd = 0;
		struct sockaddr_in server_address; 

		sock = socket(AF_INET, SOCK_STREAM, 0);
		memset(&server_address, '0', sizeof(server_address));

		server_address.sin_family = AF_INET;
		server_address.sin_addr.s_addr = htonl(INADDR_ANY);
		server_address.sin_port = htons(5000); 

		bind(sock, (struct sockaddr*)&server_address, sizeof(server_address)); 

		listen(sock, 1); 

		connfd = accept(sock, (struct sockaddr*)NULL, NULL); 

		write(lSize, &lSize, sizeof(lSize));
		write(connfd, buffer, lSize); 

		close(connfd);
		fclose(pFile);
		free(buffer);
		return 0;
	}
}