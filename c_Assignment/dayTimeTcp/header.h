#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<unistd.h>
#include	<sys/un.h>
#include	<time.h>

#define MAXLINE	4096
#define MAXSOCKADDR	128
#define BUFFSIZE	8192
#define BACKLOG 10

#define SA struct sockaddr

int Socket(int family, int type, int protocol){
	int n;
	if((n= socket(family, type, protocol)) < 0){
		perror("[-]socket() Error");
		exit(1);
	}
	printf("[+]Socket Created\n");
	return (n);
}

int Connect(int sockfd, SA *addr, socklen_t addrlen){
	int n;
	if((n= connect(sockfd, addr, addrlen))<0){
		perror("[-]connect() Error");
		exit(1);
	}
	printf("[+]Connection Established\n\n");
	return (n);
}

int Bind(int sockfd, SA *addr, socklen_t addrlen){
	int n;
	if((n= bind(sockfd,addr, addrlen))<0){
		perror("[-]bind() Error");
		exit(1);
	}
	printf("[+]Bind Successful\n");
	return (n);
}

int Listen(int sockfd, int backlog){
	int n;
	if((n= listen(sockfd, backlog))<0){
		perror("[-]listen() Error");
		exit(1);
	}
	printf("[+]Listening for the Client...\n");
	return (n);
}

int Accept(int sockfd, SA *addr, socklen_t *addrlen){
	int n;
	if((n= accept(sockfd, addr, addrlen))<0){
			perror("[-]accept() Error");
			exit(1);
	}
	printf("[+]Client Connected\n");
	return (n);
}

ssize_t Write(int sockfd, void *buff, size_t count){
	ssize_t n;
	if((n= write(sockfd, buff, count))<0){
		perror("[-]write() Error");
		exit(1);
	}
	printf("[+]Write implemented\n");
	return (n);
}

ssize_t Read(int sockfd, void *buff, size_t count){
	ssize_t n;
	if((n= read(sockfd, buff, count))<0){
		perror("[-]read() Error");
		exit(1);
	}
	printf("[+]Read Successful\n");
	return (n);
}
