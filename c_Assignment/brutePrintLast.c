#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tailbuff Brute Force

#define SIZE 256 

char ** lastnumlines(FILE * inputfp, int num){

	char ** tailbuff = (char **) calloc(num, sizeof(char *));
	char ** temp = (char **) calloc(num, sizeof(char *));

	for(int i=0;i<num;i++){
		temp[i] = (char *) calloc(SIZE, sizeof(char));
	}

	int i=0,count = 0;

	while(!feof(inputfp)){
		fgets(temp[i%num],SIZE,inputfp);
		// printf("%d -> %d %s", count, i%num, temp[i%num]);
		count++;
		i++;
	}

	i--;
	count--;

	int l=i%num,a=0;
	// printf("%d %d %d\n",l,i,num);

	if(num<=count){
		while(a<num){
			// printf("%d %s",l,temp[l]);

			tailbuff[a] = (char *) calloc(SIZE, sizeof(char));
			strcpy(tailbuff[a],temp[l]);

			l++;
			l=l%num;
			a++;
		}
	}
	else{
		printf("Given Input is greater than the total number of lines in the input file.\n");
	}

	   for(int i=0;i<num;i++){
	   free(temp[i]);
	   }

	free(temp);

	return tailbuff;
}



int main(int argc, char *argv[]) {
	FILE * inputfp = fopen("input.txt", "r");

	int num=0;

	if(argc<=1){
		num = 10;
	}
	else {
		num = atoi(argv[1]);
	}

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
				printf("%d %p --> %s",i+1,printtail[i],printtail[i]);
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
