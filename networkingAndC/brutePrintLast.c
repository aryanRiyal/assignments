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

	int count = 0;

	while(!feof(inputfp)){
		fgets(temp[count%num],SIZE,inputfp);
		// printf("%d -> %d %s", count, i%num, temp[i%num]);
		count++;
	}

	// because feof iterates one extra time
	count--;

	int l=count%num, i=0;
	// printf("%d %d %d\n",l,i,num);

	if(num <= count){
		while(i<num){
			// printf("%d %s",l,temp[l]);

			tailbuff[i] = (char *) calloc(SIZE, sizeof(char));
			strcpy(tailbuff[i],temp[l]);

			l++;
			l=l%num;
			i++;
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
	FILE * inputfp = fopen("dummyInput.txt", "r");

	int num=0;

	// scanf("%d",&num);
	
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
				// printf("%d %p --> %s",i+1,printtail[i],printtail[i]);
				printf("%s",printtail[i]);
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
