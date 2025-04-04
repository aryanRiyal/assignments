#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tailbuff Brute Force

#define SIZE 256 

char ** lastnumlines(FILE * inputfp, int num){
	char ** tailbuff = (char **) calloc(num, sizeof(char *));
	for(int i=0;i<num;i++){
		tailbuff[i] = (char *) calloc(SIZE, sizeof(char));
	}
	int count = 0;
	while(fgets(tailbuff[count%num],SIZE,inputfp)!=NULL){
		count++;
	}
	char *temp;
	int top = count%num;
	int start=0; 
	if(top==0 || num > count){
		return tailbuff;
	}
	else{
	int dif = num - top;
	int move;
	while(dif--){
		move = top;
		while(move != start){
			temp = tailbuff[move];
			tailbuff[move] = tailbuff[move-1];
			tailbuff[move-1] = temp;
			move--;
		}
		start++;
		top++;
	}
	}
	return tailbuff;
}

int main(int argc, char *argv[]) {
	FILE * inputfp = fopen("dummyInput.txt","r");

	int num=0;
	if(argc<2){
		num=10;
	}
	else{
		num = atoi(argv[1]);
	}

	if(num>100 || num<=0){
		printf("Input should be greater than 0 and less than 100\n");
		fclose(inputfp);
		return 1;
	}
	printf("\n");
	if(inputfp != NULL){
		char ** printLast = lastnumlines(inputfp,num);
		for(int i=0;i<num;i++){
			if(printLast[i]!=NULL){
				printf("%s",printLast[i]);
			}
		}
		for(int i=0;i<num;i++){
			free(printLast[i]);
		}
		free(printLast);
		fclose(inputfp);
		return 0;
	}
	else{
		printf("File Input is NULL\n");
		fclose(inputfp);
		return 1;
	}
}
