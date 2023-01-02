#include "header.h"

int main( int argc, char **argv){

	
	if(argc != 2){
		printf("[-]Usage: %s <IP Address>\n",argv[0]);
		exit(0);
	}
	char *ip = argv[1];
	printf("IP Address: %s\n",ip);
	

	int sockfd,count=0,n;
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);
	char response[MAXLINE+1];

	struct sockaddr_in serverAddress;

	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(9999);

	if(inet_pton(AF_INET, argv[1], &serverAddress.sin_addr)<=0){
		printf("[-]inet_pton() Error for %s", argv[1]);
		exit(1);
	}

	Connect(sockfd, (SA *)&serverAddress, sizeof(serverAddress));

	/*
	Q 1.3
	if(connect(sockfd, (SA *)&serverAddress, sizeof(serverAddress))<0){
		printf("[-]Connection Failed\nError No: %d, Error: %s\n", errno, strerror(errno));
		exit(1);
	}
	*/
	
	while((n = read(sockfd, response, MAXLINE)) > 0) {
		/*
		Q 1.4
		*/
		count++;
		// printf("\n%d ",n);
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

	/*
	Read(sockfd, response, MAXLINE);

	if(fputs(response,stdout)==EOF){
		perror("[-]fputs() Error");
		exit(1);
	}
	*/
	printf("\nCount = %d\n",count);

	close(sockfd);
	printf("[+]Disconnected from the server.\n");

	return 0;
}
