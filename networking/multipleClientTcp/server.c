#include "../header.h"

int main(void){

	int serverSocket;
	struct sockaddr_in serverAddress;
	int clientSocket;
	struct sockaddr_in clientAddress;
	socklen_t addr_size;
	int n_client=0;

	char buff[MAXLINE];
	int childpid;

	serverSocket = Socket( AF_INET, SOCK_STREAM, 0);
	memset( &serverAddress, '\0', sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(11111);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	Bind( serverSocket, (SA *)&serverAddress, sizeof(serverAddress));
	Listen( serverSocket, BACKLOG);

	while(1){
		n_client++;
		clientSocket = Accept( serverSocket, (SA *)&clientAddress, &addr_size);

		if((childpid = fork()) == 0){
			close(serverSocket);
			serverSocket = -1;

			printf("[+]Connection Established with %s:%d - Client(%d) with Child Pid - %d\n\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port), n_client, getpid());
			while(1){
				memset( buff,'\0',sizeof(buff));
				recv(clientSocket, buff, MAXLINE, 0);
				if(strcmp(buff, ":exit")==0){
					printf("\n[+]Disconnected from %s:%d - Client(%d)\n\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port), n_client);
					break;
				}else{
					printf("Client(%d): %s\n",n_client, buff);
					send( clientSocket, buff, strlen(buff), 0);
					memset( buff, '\0', sizeof(buff));
				}
			}
			close(clientSocket);
			clientSocket = -1;
			exit(EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}
