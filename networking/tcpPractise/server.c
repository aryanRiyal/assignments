#include "../header.h"

int main(void){
	int n_client = 0;
	const int opt = 1;
	int serverSock, clientSock;
	serverSock = Socket(AF_INET, SOCK_STREAM, 0);

	// Forcefully attaching socket to the port 54321 or Reused Port and address (optional)
	/*
	   if (setsockopt( serverSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
	   perror("setsockopt(SO_REUSEADDR) Error");
	   close(serverSock);
	   exit(EXIT_FAILURE);
	   }
	   */
	if(setsockopt( serverSock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (char *)&opt, sizeof(opt)) < 0 ){
		perror("setsockopt(SO_REUSEADDR) Error\n");
		close(serverSock);
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in serverAddress;
	char buff[MAXLINE];
	time_t ticks;

	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); 
	serverAddress.sin_port = htons(9999);

	Bind( serverSock, (SA *)&serverAddress, sizeof(serverAddress));
	Listen(serverSock, BACKLOG);

	const int i=1;
	while(i){ 
		clientSock = Accept(serverSock, (SA *) NULL, NULL);
		n_client++;
		time(&ticks);
		printf("Client %d connected to the Server on: %.24s\r\n\n", n_client,ctime(&ticks));
		while(i){
			bzero(buff, sizeof(buff));
			Read( clientSock, buff, MB);
			printf("Client %d: %s", n_client, buff);
			if(!strncmp("bye", buff, 3)){
				break;
			}
			bzero( buff, sizeof(buff));
			printf("Server: ");
			fgets( buff, sizeof(buff), stdin);
			Write( clientSock, buff, MB);
			if(!strncmp("bye", buff, 3)){
				break;
			}
		}
		close(clientSock);
		printf("\n[+]Client Disconnected from the server.\n\n");
	}
	return 0;
}
