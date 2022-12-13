#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tailbuff Brute Force

#define SIZE 256

char ** lastnumlines(FILE * inputfp, int num){

	char ** tailbuff = (char **) calloc(num, sizeof(char *));
	char ** temp = (char **) calloc(100, sizeof(char *));	

	int i=0,count = 0;
	while(!feof(inputfp)){
		temp[i]= (char *) calloc(SIZE, sizeof(char));
		fgets(temp[i],SIZE,inputfp);
		count++;
		i++;
	}

	count--;

	if(num<=count){
		int j=count-num,k=0;
		while(j<count){
			tailbuff[k]=(char *) calloc(SIZE, sizeof(char));
			strcpy(tailbuff[k],temp[j]);
			j++;
			k++;
		}
	}
	else{
		printf("Given Input is greater than the total number of lines in the input file.\n");
	}
	
	for(int i=0;i<=count;i++){
		free(temp[i]);
	}
	free(temp);
	
	return tailbuff;
}



int main(void) {
	FILE * inputfp = fopen("input.txt", "r");

	int num;
	scanf("%d",&num);

	if(num>100 || num<=0){
		printf("Input is greater than 100 or lesser than 0\n");
		fclose(inputfp);
		return 1;
	}

	printf("\n");

	if(inputfp != NULL){
		char ** printtail = lastnumlines(inputfp,num);

		for(int i=0;i<num;i++){
			if(printtail[i]!=NULL){
				printf("%d %p --> %s",i,printtail[i],printtail[i]);
			}
			else
				break;
		}
		
		for(int i=0;i<num;i++){
			free(printtail[i]);
		}

		free(printtail);

		fclose(inputfp);
		return 0;
	}
	else{
		printf("File Input is NULL\n");
		fclose(inputfp);
		return 1;
	}
}
