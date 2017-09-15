#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the stringss in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void readStdin(FILE* f)
{
  size_t s=0, i=0; 
  ssize_t output;
  char **stringss = NULL;
  char *tmp = NULL;

  if (f != NULL)
      output = getline(&tmp, &s, f);
  else
      output = getline(&tmp, &s, stdin);


  while(output >= 0) 
  {
    stringss = realloc(stringss, (i+1) *sizeof(char *));
    stringss[i] = malloc(s);

    strcpy(stringss[i], tmp);

    i++;

    if (f != NULL)
      output = getline(&tmp, &s, f);
    else
      output = getline(&tmp, &s, stdin);
  }

  sortData(stringss, i);

  for(int j=0; j<i; j++)
      printf("%s", stringss[j]);

  for(int j=0; j<i; j++)
      free(stringss[j]);
  free(tmp);
  free(stringss);
}


int main(int argc, char ** argv) {
  FILE *f = NULL;
  if (argc == 3)
  {
    perror("Damn it!");
    return EXIT_FAILURE;
  }

  if (argc == 1)
    readStdin(f);

  if (argc == 2)
  {
    f = fopen(argv[1], "r"); 
    if (f == NULL)
    {
      perror("can't open input file");
      return EXIT_FAILURE;
    }

    readStdin(f);

    if (fclose(f) != 0)
    {
      perror("can't close file");
      return EXIT_FAILURE;
    }

  }
  
  
  return EXIT_SUCCESS;
}
