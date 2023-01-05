#include "header.h"

// lsof -i :port
// kill -9 pid

int main( int argc, char **argv){
	int n_client = 0,count = 0;
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

	int i=1,j;
	while(i){
		clientSock = Accept(serverSock, (SA *) NULL, NULL);
		n_client++;
		time(&ticks);
		printf("Client %d is requesting for Day and Time Information.\n", n_client);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		count = strlen(buff);
		printf("%d\n",count);
		// Q 1.5
		for(j=0;j<count;j++){
		Write(clientSock, buff+j, 1);
		}
		close(clientSock);
		printf("[+]Client Disconnected\n\n");
	}

	close(serverSock);
	return 0;
}
