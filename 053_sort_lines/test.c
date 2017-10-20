#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
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

void readStdin2(char ** strings, FILE* f)
{
  int i = 0;
  size_t s; 
  printf("in readStdin2, before loop \n");
  //char **string;
  char *tmp;

  while(getline(&tmp, &s, f) >= 0)
  {
    strings = realloc(strings, (i+1) * sizeof(tmp));
    strings[i] = tmp;
    //strings[i] = malloc(sizeof(tmp + 2));
    //    printf("%d: %s", i, strings[0]);
    printf("%d: %s", i, strings[i]);
    i++;
  }
}

int main(int argc, char ** argv) {
  char ** strings;
//  if (argc == 1)
//    readStdin(strings);

  if (argc == 2)
  {
    FILE *f = fopen(argv[1], "r"); 
    if (f == NULL)
    {
      perror("can't open input file");
      return EXIT_FAILURE;
    }

    readStdin2(strings, f);


    if (fclose(f) != 0)
    {
      perror("can't close file");
      return EXIT_FAILURE;
    }

  }
  printf("finish\n");
  
  //WRITE YOUR CODE HERE!
  
  free(strings);
  return EXIT_SUCCESS;
}
