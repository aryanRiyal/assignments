#include "header.h"

int main( int argc, char **argv){

	if(argc != 2){
		printf("[-]Usage: %s <port>\n",argv[0]);
		exit(0);
	}

	int port = atoi(argv[1]);
	printf("Port: %d\n",port);

	int sockfd;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	char response[MAXLINE+1];

	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);

	Connect(sockfd, (SA *)&serverAddress, sizeof(serverAddress));

	// recv(sockfd, response, 30, 0);
	// printf("Time from server: %s",response);

	/*
	int n;
	while((n = read(sockfd, response, MAXLINE)) > 0) {
		response[n] = 0;
		if(fputs(response,stdout) == EOF){
			perror("[-]fputs() Error");
			exit(1);
		}
	}
	if(n<0){
		perror("[-]read() Error");
		exit(1);
	}
	*/

	Read(sockfd, response, MAXLINE);

	if(fputs(response,stdout)==EOF){
		perror("[-]fputs() Error");
		exit(1);
	}

	close(sockfd);
	printf("[+]Disconnected from the server.\n");

	return 0;
}
