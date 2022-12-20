#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Using Linked List

// Contraints 
// 0<num<100
// 0<SIZE<256
// No Memory Leak

#define SIZE 256

typedef struct node{
	char val[SIZE];
	struct node *next;
} node_t;

//print
void print_list(node_t * head){
	node_t *current = head;
	while (current != NULL){
		printf("%s", current->val);
		current = current->next;
	}
}

//add
void push(node_t * head, char val[]){
	node_t *current = head;
	while( current->next != NULL) {
		current = current->next;
	}
	current->next = (node_t *) calloc(1, sizeof(node_t));
	strcpy(current->next->val, val);
	current->next->next = NULL;
}

//remove
int pop(node_t ** head){
	node_t *next_node = NULL;

	if(*head == NULL){
		return 1;
	}

	next_node = (*head)->next;
	free(*head);

	*head = next_node;
	return 0;
}

//removing the last node
int remove_last(node_t * head){
	if(head->next == NULL){
		free(head);
		return 0;
	}
	node_t * current = head;
	while(current->next->next != NULL){
		current = current->next;
	}
	free(current->next);
	current->next = NULL;
	return 0;
}


void lastnumlines(FILE * inputfp, int num){
	int count=0;

	node_t *head = NULL;

	head = (node_t *) calloc(1, sizeof(node_t));

	// printf("\n");

	// Reading till EOF
	while(!feof(inputfp)){

		if(count>=num){
			pop(&head);
		}
		char temp[SIZE];
		fgets( temp, SIZE, inputfp);
		push(head,temp);
		count++;
	}
	// printf("\n");

	// Because feof iterates 1 extra time
	count--;
	remove_last(head);

	// printf("\n Count=%d Num=%d \n",count, num);

	// printf("\n OUTPUT \n");
	// Only printing if given input is less than the total size of the file
	// printf("%d %d\n", count, num);

	// print_list(head);

	if(num <= count){
		print_list(head);
		// printf("\n");
	}
	else
	{
		printf("Given input is greater than the total number of lines in the Input File\n");
	}

	for(int i=0;i<=count;i++){
		pop(&head);
	}
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
		printf("Input should be lesser than 100 or greater than 0\n");
		// printf("\n");
		fclose(inputfp);
		return 1;
	}

	if(inputfp != NULL){
		lastnumlines(inputfp,num);
		fclose(inputfp);
		return 0;
	}
	else{
		printf("File Input is NULL\n");
		fclose(inputfp);
		return 1;
	}
}
