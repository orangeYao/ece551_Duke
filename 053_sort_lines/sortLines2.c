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

  stringss = realloc(stringss, (i+1) *sizeof(char *));

  if (f != NULL)
      output = getline(&stringss[i], &s, f);
  else
      output = getline(&stringss[i], &s, stdin);
  s = 0;


  while(output >= 0) 
  {
    i++;
    stringss = realloc(stringss, (i+1) *sizeof(char *));


    if (f != NULL)
      output = getline(&stringss[i], &s, f);
    else
      output = getline(&stringss[i], &s, stdin);
//    printf("%zu\n", s);
    s = 0;
  }

  sortData(stringss, i);

  for(int j=0; j<i; j++)
      printf("%s", stringss[j]);

  for(int j=0; j<=i; j++)  // why equal?
      free(stringss[j]);
  free(stringss);
}


int main(int argc, char ** argv) {
  FILE *f = NULL;

  if (argc == 1)
    readStdin(f);

  for (int i=1; i<argc; i++)
  {
    f = fopen(argv[i], "r"); 
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
