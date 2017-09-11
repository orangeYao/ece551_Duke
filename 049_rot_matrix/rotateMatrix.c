#include <stdio.h>
#include <stdlib.h>

#define N 10

void rotateMatrix(FILE *f)
{
  char c[N+2][N+2]; // consider \n and \0
  int idx = 0;
  while(fgets(c[idx], N+2, f) !=NULL)
    idx++;

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
  {
    fprintf(stderr, "Provide one input file \n");
    return 1;
  }

  FILE * f = fopen(argv[1], "r"); 
  if (f == NULL)
  {
    fprintf(stderr, "Failed to open file \n");
    return 1;
  }

  rotateMatrix(f);

  if (fclose(f) != 0)
  {
    fprintf(stderr, "Failed to close file \n");
    return 1;
  }

  return 0;
}
