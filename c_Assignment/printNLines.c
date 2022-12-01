#include <stdio.h>
#include <stdlib.h>


//char ** firstnumlines(FILE * inputfp, unsigned int num){
char ** firstnumlines(FILE * inputfp, unsigned int num){
	char ** headbuff = (char **) calloc(num, sizeof(char *));
	int i=0;
	//char c;
	while(i<num ){
		//c = fgetc(inputfp);
		if(feof(inputfp)){
				printf("EOF REACHED\n");
				break;
			}
		headbuff[i] = (char *) calloc(255, sizeof(char));
		fgets(headbuff[i],255,inputfp);
		/*if(headbuff[i] != NULL){
		printf("%s",headbuff[i]);
	    }*/	
		//c = getc(inputfp);
		i++;
		//free(headbuff[i]);
	}
	return headbuff;
	
}



int main() {
	FILE * inputfp = fopen("input.txt", "r");

	int num;
	scanf("%d",&num);
	char ** firstlines = firstnumlines(inputfp,num);

    //firstnumlines(inputfp,num);
	
	for(int i=0;i<num;i++){
		if(firstlines[i] != NULL){
			printf("%s",firstlines[i]);
		}
	}


/*	
 	for(int i =0;i<num;i++){
		free(firstlines[i]);
		}
*/

	free(firstlines);
	//printf("\n");
	fclose(inputfp);
}
