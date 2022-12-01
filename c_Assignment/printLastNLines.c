#include<stdio.h>
#include<stdlib.h>

char ** lastnumlines(FILE * inputfp, unsigned int num)
{
  char ** tailbuf = calloc(num, sizeof(char *));
  
  while(){

  }

  return tailbuf;
}

int main()
{
   FILE * fp = fopen("input.txt", "r");
   char ** lastlines = lastnumlines(fp, 10);
   for (int i = 0; i < 10; i++) {
        if (lastlines[i] != NULL) {
            printf("%s", lastlines[i]);
        }
   }
   free(lastlines);
   fclose(fp);
}
