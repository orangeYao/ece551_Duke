#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10


void reportError(char * e)
{
  fprintf(stderr,"%s", e);
  exit(EXIT_FAILURE);
}

void rotateMatrix(FILE *f)
{
  char c[N+2][N+2]; // consider \n and \0
  int idx = 0;
  while(fgets(c[idx], N+2, f) !=NULL)
  {
    char * newline_ptr = strchr(c[idx], '\n');

    if(newline_ptr - &(c[idx][0]) != 10)
      reportError("Line length in file mismatch expectation \n");
    idx++;
  }

  if (idx != 10)
    reportError("Lines in file mismatch expectation \n");

  for (int j=0; j<10; j++)
  {
    for (int i=9; i>-1; i--)
      printf("%c", c[i][j]);

    printf("\n");
  }

  return;
}

int main(int argc, char ** argv)
{
  if (argc != 2)
    reportError("Provide one input file \n");

  FILE * f = fopen(argv[1], "r"); 
  if (f == NULL)
    reportError("Failed to open file \n");

  rotateMatrix(f);

  if (fclose(f) != 0)
    reportError("Failed to close file \n");

  return EXIT_SUCCESS;
}
