#include "../header.h"

int main(int argc, char **argv){

	if(argc != 2){
		printf("Usage: %s <port>\n",argv[1]);
		exit(0);
	}
	char *ip = "127.0.0.1";
	int port = atoi(argv[1]);
	int sockfd;
	struct sockaddr_in addr;
	char buffer[MAXLINE];
	sockfd = Socket(AF_INET, SOCK_DGRAM, 0);

	bzero( &addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(ip);

	bzero(buffer, sizeof(buffer));
	printf("Type your message: ");
	scanf("%[^\n]s",buffer);
	sendto( sockfd, buffer, sizeof(buffer), 0, (SA *)&addr, sizeof(addr));
	printf("[+]Data Sent: %s\n", buffer);

	return 0;
}
