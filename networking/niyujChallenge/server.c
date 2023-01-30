#include "../header.h"

int getPwd(char *buff){
    getcwd( buff, 100);
    if(buff != NULL){
        printf( "\n%s\n",buff);
    }else{
        perror("getcwd() Error");
        return (EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

int getLs(char *buff){
    struct stat sb;
    DIR *path;
    char date[100];
    char *dirName = ".";
    struct dirent *d;
    path = opendir(dirName);
    int f=0;
    if(path==NULL){
        perror("Cannot find directory");
        return (EXIT_FAILURE);
    }
    printf("\n");
    while((d = readdir(path)) != NULL){
        if (lstat(d->d_name, &sb) == -1) {
                perror("lstat()");
                return (EXIT_FAILURE);
        }
        switch (sb.st_mode & S_IFMT) {
            case S_IFDIR:{	
                             printf("directory\n");
                             f=1;
                             break;
                         }
            case S_IFREG:{	
                             printf("regular file\n");
                             f=2;
                             break;
                         }
        }
      printf("Last file modification:   %s", ctime(&sb.st_mtime));
      strlcpy(date, ctime(&sb.st_mtime), sizeof(date));

     if(f==1)
        strlcat( buff,"DIR ",MB);
     else if(f==2)
        strlcat( buff,"REG ",MB);
     strlcat( buff, d->d_name, MB);
     strlcat( buff, " ", MB);
     strlcat( buff, date, MB);
     strlcat( buff, "\n", MB);
     printf("%s\n", buff);
    }
    return EXIT_SUCCESS;
}

int changeDir(char *dirName,char *buff){
    if(chdir( dirName) == -1){
        printf("No Such Directory\n");
        return  EXIT_FAILURE;
    }

    memset( buff, '\0', sizeof(buff));
    getcwd(buff,100);
    if(buff != NULL){
        printf( "\n%s\n", buff);
    }else{
        perror("getcwd() Error");
        return (EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}


int main(void){
    int serverSocket;
    struct sockaddr_in serverAddress;
    int clientSocket;
    struct sockaddr_in clientAddress;
    socklen_t addr_size;
    int n_client=0;

    char buff[MAXLINE];
    char commandName[50], dirName[50];
    pid_t childpid;

    serverSocket = Socket( AF_INET, SOCK_STREAM, 0);
    const int opt = 1;
    if( setsockopt( serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (char *)&opt, sizeof(opt))<0){
        perror("setsockopt(SO_REUSEADDR | SO_REUSEPORT) Error\n");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    memset( &serverAddress, '\0', sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(54321);        
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind( serverSocket, (SA *)&serverAddress, sizeof(serverAddress));
    Listen( serverSocket, BACKLOG);
    do{
        n_client++;
        clientSocket = Accept( serverSocket, (SA *)&clientAddress, &addr_size);
        if((childpid = fork())==0){
            close(serverSocket);
            serverSocket = -1;
            printf("[+]Connection Established with %s:%d - Client(%d) with Child Pid - %d\n\n", inet_ntop( AF_INET, &clientAddress.sin_addr, buff, sizeof(buff)), ntohs(clientAddress.sin_port), n_client, getpid());
            printf("\nChildpid(%d)=%d\n", n_client, childpid);
            while(1){
                memset( buff,'\0',sizeof(buff));
                Recv(clientSocket, buff, MAXLINE, 0);
                if(strncmp(buff, "bye",3)==0){
                    printf("\n[+]Disconnected from %s:%d - Client(%d)\n\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port), n_client);
                    break;
                }
                else if(strncmp( buff, "ls",2)==0){
                    memset( buff, '\0', sizeof(buff));
                    getLs( buff);
                    printf("\ngetLs() success\n");
                    Send( clientSocket, buff, strlen( buff), 0);
                }
                else if(strncmp( buff, "pwd", 3)==0){
                    memset( buff, '\0', sizeof(buff));
                    getPwd( buff);
                    printf("\ngetPwd() success\n");
                    Send( clientSocket, buff, strlen( buff), 0);
                }
                else if(strncmp( buff, "cd", 2)==0){
                    sscanf( buff, "%s %s", commandName, dirName);
                    changeDir(dirName, buff);
                    printf("\ncahngeDir() success\n");
                    Send( clientSocket, buff, strlen(buff), 0);
                }else{
                    printf("Client(%d): %s\n",n_client, buff);
                    Send( clientSocket, buff, strlen(buff), 0);
                    memset( buff, '\0', sizeof(buff));
                }
            }
            close(clientSocket);
            clientSocket = -1;
            exit(EXIT_SUCCESS);
        }
        else{
            printf("\nChildpid(%d)=%d\n", n_client, childpid);
        }
        close(clientSocket);
    }
    while(1);
    close(serverSocket);
    printf("\n...Terminating the session...\n");
    return (EXIT_SUCCESS);
}
