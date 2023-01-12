#include "../header.h"

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("[-]Usage: %s <IP Address>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	printf("IP Address: %s\n",argv[1]);
	int clientSocket;
	struct sockaddr_in serverAddress;
	char buff[MAXLINE];
	clientSocket = Socket(AF_INET, SOCK_STREAM, 0);

	memset( &serverAddress, '\0', sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(11111);

	if(inet_pton(AF_INET, argv[1], &serverAddress.sin_addr)<=0){
		printf("[-]inet_pton() Error for %s\n", argv[1]);
		close(clientSocket);
		exit(EXIT_FAILURE);
	}

	Connect( clientSocket, (SA *)&serverAddress, sizeof(serverAddress));

	while(1){
		memset( buff,'\0', sizeof(buff));
		printf("Client: \t");
		scanf("%[^\n]%*c", &buff[0]);
		send( clientSocket, buff, strlen(buff), 0);
		if(strncmp( buff, ":exit", 5) == 0){
			close(clientSocket);
			printf("[-]Disconnected from server.\n");
			exit(1);
		}
		if(recv( clientSocket, buff, MAXLINE, 0) < 0){
			printf("[-]Error in receiving data.\n");
		}else{
			printf("Server: \t%s\n", buff);
		}	
		if(strncmp( buff, ":exit", 5) == 0){
			close(clientSocket);
			printf("[-]Removed from server.\n");
			exit(1);
		}
	}
	return (EXIT_SUCCESS);
}
