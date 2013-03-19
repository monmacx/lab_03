#ifndef FILE_SENDER_H
#define FILE_SENDER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

struct _message
{
	char * file;
	int size;
	int index;
};

// Function to send file to client
void *send_file_to_client(void *ptr);

#endif