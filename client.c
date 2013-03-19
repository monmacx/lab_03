#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

int main(int argc, char * argv[]) {
	int sockfd = 0, n = 0;
	char *bufSizeBytes;
	int bufSizeLength = sizeof(int);
    char *recvBuff;
    struct sockaddr_in server_address; 

    if(argc != 2)
    {
        printf("\n Usage: %s <ip of server> \n",argv[0]);
        return 1;
    } 

    bufSizeBytes = (char*)malloc(bufSizeLength);
    memset(bufSizeBytes, '0', sizeof(bufSizeBytes));
    //memset(recvBuff, '0',sizeof(recvBuff));
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&server_address, '0', sizeof(server_address)); 

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(5000); 

    if(inet_pton(AF_INET, argv[1], &server_address.sin_addr)<=0)
    {
        printf("\n Error : wrong address\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    while ( (n = read(sockfd, bufSizeBytes, sizeof(bufSizeBytes)-1)) > 0)
    {
        bufSizeBytes[n] = 0;
        if(fputs(bufSizeBytes, stdout) == EOF)
        {
            printf("\n Error : Fputs error\n");
        }
    } 

    if(n < 0)
    {
        printf("\n Read error \n");
    } 

    return 0;
}