#include <stdio.h>
#include <stdlib.h>


//void ** firstnumlines(FILE * inputfp, unsigned int num){
char ** firstnumlines(FILE * inputfp, unsigned int num){
	char ** headbuff = (char **) calloc(num, sizeof(char *));
	int i=0;
	int j=1;
	//char c;
	while(j<=num){
		//c = fgetc(inputfp);

		if(feof(inputfp)){
			printf("\nGiven Size is Greater than the input file\n\n");
			//break;
			for(int i =0;i<num;i++){
				free(headbuff[i]);
			}
			free(headbuff);

			return NULL;
		}
		else{
			headbuff[i] = (char *) calloc(255, sizeof(char));
			fgets(headbuff[i],255,inputfp);
			//printf("%d %d\n",i,j);
			i++;
			j++;
		}
		/*if(headbuff[i] != NULL){
		  printf("%s",headbuff[i]);
		  }*/	

		// c = getc(inputfp);
		// i++;

		//printf("%d\n",i);
		//i++;
		//free(headbuff[i]);
	}
	return headbuff;

}



int main() {
	FILE * inputfp = fopen("input.txt", "r");

	int num;
	scanf("%d",&num);
	printf("\n");

	char ** firstlines = firstnumlines(inputfp,num);

	//firstnumlines(inputfp,num);

	if(firstlines==NULL){
		return 0;
	}

	for(int i=0;i<num;i++){
		if(firstlines[i] != NULL){
			printf("%s",firstlines[i]);
		}
	}

	for(int i =0;i<num;i++){
		free(firstlines[i]);
	}
	free(firstlines);

	//printf("\n");
	fclose(inputfp);

}
