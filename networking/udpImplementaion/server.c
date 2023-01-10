#include "../header.h"

int main(int argc, char **argv){

	if(argc != 2){
		printf("Usage: %s <port>\n",argv[0]);
		exit(0);
	}
	char *ip = "127.0.0.1";
	int port = atoi(argv[1]);
	int sockfd;
	struct sockaddr_in serverAddress, clientAddress;
	char buffer[MAXLINE];
	socklen_t addr_size;
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero( &serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = inet_addr(ip);

	Bind( sockfd, (SA *)&serverAddress, sizeof(serverAddress));
	bzero(buffer, sizeof(buffer));
	addr_size = sizeof(clientAddress);
	recvfrom( sockfd, buffer, sizeof(buffer), 0, (SA *)&clientAddress, &addr_size);
	printf("[+]Data Received: %s\n", buffer);

	return 0;
}
