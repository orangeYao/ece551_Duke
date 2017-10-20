#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE *f = fopen(filename, "r");
  if (f == NULL)
  {
    perror("can't open file to write!");
    exit(EXIT_FAILURE);
  }

  counts_t * c = createCounts();
  size_t s = 0;
  char * r_in = NULL;
  while(getline(&r_in, &s, f) > 0)
  {
    int l = strlen(r_in);
    r_in[l - 1] = '\0';
    addCount(c, lookupValue(kvPairs, r_in));
  }

  free(r_in);

  if(fclose(f) != 0)
  {
    perror("can't close file!");
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
 
  if (argc < 2)
  {
    perror("at least two file as input!");
    return EXIT_FAILURE;
  }

  kvarray_t * pairs = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
 for (int i=2; i<argc; i++)
 {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t* c = countFile(argv[i], pairs); 

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);


    //open the file named by outName (call that f)
    FILE *f = fopen(outName, "w");
    if (f == NULL)
    {
      perror("can't open file to write!");
      return EXIT_FAILURE;
    }

    //print the counts from c into the FILE f

//    printCounts(c, NULL);
    printCounts(c, f);

    //close f
    if(fclose(f) != 0)
    {
      perror("can't close file!");
      return EXIT_FAILURE;
    }

    //free the memory for outName and c
    free(outName);
    freeCounts(c);


 }
 //free the memory for kv
  freeKVs(pairs);
  
  return EXIT_SUCCESS;
}
