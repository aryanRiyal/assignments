#include "header.h"

int main( int argc, char **argv){

	int n_client = 0;
	int serverSock, clientSock;
	serverSock = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serverAddress;
	char buff[MAXLINE];
	time_t ticks;

	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(9999);

	Bind( serverSock, (SA *)&serverAddress, sizeof(serverAddress));

	Listen(serverSock, BACKLOG);
	printf("\n");

	int i=1;
	while(i){
		clientSock = Accept(serverSock, (SA *) NULL, NULL);
		n_client++;
		time(&ticks);

		printf("Client %d is requesting for Day and Time Information.\n", n_client);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		Write(clientSock, buff, strlen(buff));

		close(clientSock);
		printf("[+]Client Disconnected\n\n");
	}

	return 0;
}
