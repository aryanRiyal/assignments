#include <stdio.h>
#include <stdlib.h>

//Headbuff latest - 9 dec 11am


void firstnumlines(FILE * inputfp, unsigned int num){
	char ** headbuff = (char **) calloc(num, sizeof(char *));
	int i=0,f=0;
	int count=0;
	printf("%p \n",headbuff);
	while(i<=num){
		if(!feof(inputfp)){
			count++;
		}
		else{
			f=1;
			free(headbuff[i]);
			break;
		}
		headbuff[i] = (char *) calloc(255, sizeof(char));
		fgets(headbuff[i],255,inputfp);
		// printf("\n");
		printf("%d %p %s", i, &headbuff[i], headbuff[i]);
		i++;
	}
	count -=f;
	printf("\n%d %d\n", count, num);

	if(num <= count){
		for(int i=0;i<num;i++){
			if(headbuff[i] != NULL){
				printf("%d %p %s", i, headbuff[i], headbuff[i]);
				// printf("%s",firstlines[i]);
			}
		}
	}
	else{
		printf("\nGiven Size is Greater than the input file\n\n");
		// printf("%d %p %p %s\n", i, &headbuff[i], headbuff[i], headbuff[i]);
	}

	for(int i =0;i<count;i++){
		free(headbuff[i]);
	}
	free(headbuff);
}



int main(void) {
	FILE * inputfp = fopen("dummyInput.txt", "r");

	int num;
	scanf("%d",&num);

	if(num>100 || num<0){
		printf("Input should be lesser than 100 or greater than 0\n");
		return 1;
	}

	printf("\n");

	if(inputfp!=NULL){
		firstnumlines(inputfp,num);
		fclose(inputfp);
		return 0;
	}
	else{
		printf("File is NULL\n");
		fclose(inputfp);
		return 1;
	}
}
