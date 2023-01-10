#include "../header.h"

/*
   int inetPton(int family, const char *strptr, void *addrptr){
   if(family == AF_INET){
   struct in_addr in_val;

   if (inet_aton(strptr, &in_val)) {
   memcpy(addrptr, &in_val, sizeof(struct in_addr));
   return (1);
   }
   return 0;
   }
   errno = EAFNOSUPPORT;
   return -1;
   }
   */

int inetPton(int family, const char *strptr, void *addrptr){
	if(family == AF_INET){
		int n = inet_pton( family, strptr, addrptr);
		printf("%d\n",n);
		if(n<0){
			printf("[-]inet_pton Error for %s",strptr);
			return -1;
		}
		else if (n==0) {
			struct in_addr in_val;
			if(inet_aton(strptr, &in_val)){
				memcpy( addrptr, &in_val, sizeof(struct in_addr));
				printf("[-]trying inet_aton incase of inet_pton returning 0");
				return (1);
			}
		}
	}
	else if (family == AF_INET){
		return -1;
	}
	return 0;
}


int main(int argc, char *argv[]){

	if(argc != 2){
		printf("[-]Usage ./run <IP Address>\n");
		exit(1);
	}
	struct sockaddr_in serverAddress;
	bzero(&serverAddress, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(9999);

	int n;
	if((n=inetPton(AF_INET, argv[1], &serverAddress.sin_addr))<0){
		printf("[-]inet_pton() Error for %s\n%d\n",argv[1],n);
		printf("error: %d %s\n",errno, strerror(errno));
		exit(1);
	}

	printf("[+]inet from presentation to numeric conversion successful for \nIP <%s>\n", argv[1]); 

	return 0;
}
