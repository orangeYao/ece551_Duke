#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define alpha_N 26
const int int_e = 'e' - 'a';

int breaker(FILE * f)
{
  int freq[alpha_N] = {0};
  int c, max = 0, max_i;
  while((c = fgetc(f)) != EOF)
  {
    if (isalpha(c))
    {
      c = tolower(c) - 'a';
      freq[c]++;
    }
  }
  for (int i=0; i<alpha_N; i++)
    if(freq[i] > max)
    {
       max = freq[i]; 
       max_i = i;
    }

  if (max_i - int_e >= 0)
      return max_i - int_e;
  else
      return 26 + max_i - int_e;
}


int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }

  printf("%d\n", breaker(f));

  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
