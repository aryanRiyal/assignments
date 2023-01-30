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
    serverAddress.sin_port = htons(54321);

    if(inet_pton(AF_INET, argv[1], &serverAddress.sin_addr)<=0){
        printf("[-]inet_pton() Error for %s\n", argv[1]);
        close(clientSocket);
        exit(EXIT_FAILURE);
    }
    Connect( clientSocket, (SA *)&serverAddress, sizeof(serverAddress));
    while(1){
        memset( buff,'\0', sizeof(buff));
        printf("Client: ");
        scanf("%[^\n]%*c", buff);
        Send( clientSocket, buff, strlen(buff), 0);
        if(strncmp( buff, "bye", 3) == 0){
            close(clientSocket);
            printf("[-]Disconnected from server.\n");
            exit(1);
        }
        Recv( clientSocket, buff, MAXLINE, 0);
        printf("\n%s\n\n", buff);	
    }
    return (EXIT_SUCCESS);
}
