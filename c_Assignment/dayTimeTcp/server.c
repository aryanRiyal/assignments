#include "header.h"

int main( int argc, char **argv){

	if(argc != 2){
		printf("[-]Usage: %s <port>\n",argv[0]);
		exit(0);
	}
	int port = atoi(argv[1]);
	printf("Port: %d\n",port);

	int n_client = 0;
	int serverSock, clientSock;
	serverSock = Socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in serverAddress;
	char buff[MAXLINE];
	time_t ticks;

	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);

	Bind( serverSock, (SA *)&serverAddress, sizeof(serverAddress));

	Listen(serverSock, BACKLOG);
	printf("\n");

	int i=1;
	while(i){
		clientSock = Accept(serverSock, (SA *) NULL, NULL);
		n_client++;
		time(&ticks);

		// printf("Client %d requested for time at %s",n_client, ctime(&ticks));
		// send(clientSock, ctime(&ticks), 29, 0);

		printf("Client %d is requesting for Day and Time Information.\n", n_client);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		Write(clientSock, buff, strlen(buff));

		close(clientSock);
		printf("[+]Client Disconnected\n\n");
	}

	return 0;
}
