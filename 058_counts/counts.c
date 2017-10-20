#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

void addValue(counts_t * c, const char * name)
{
  c->length ++;
  int len = c->length;
  c->array = realloc( c->array, len * sizeof(one_count_t *)); // store length ptrs
  c->array[len-1] = malloc(sizeof(one_count_t)); // is one ptr
  
  c->array[len-1]->values = malloc(strlen(name) + 2);
  strcpy(c->array[len-1]->values, name);
  c->array[len-1]->cnt = 1;
}

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c;
  c = malloc(sizeof(*c));
  c->array = NULL;

  c->length = 0;

  addValue(c, "<unknown>");
  c->array[0]->cnt = 0;
  return c;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL)
  {
    c->array[0]->cnt ++;
    return;
  }

  for (int i=1; i<c->length; i++)
    if (strcmp(c->array[i]->values, name) ==0)
    {
      c->array[i]->cnt ++;
      return;
    }

  addValue(c, name);
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (outFile == NULL)
  {
    for (int i=1; i<c->length; i++)
      printf("%s: %d\n", c->array[i]->values, c->array[i]->cnt);
  
    if (c->array[0]->cnt > 0)
      printf("%s : %d\n", c->array[0]->values, c->array[0]->cnt);
  } 
  else
  {
    for (int i=1; i<c->length; i++)
      fprintf(outFile, "%s: %d\n", c->array[i]->values, c->array[i]->cnt);
  
    if (c->array[0]->cnt > 0)
      fprintf(outFile, "%s : %d\n", c->array[0]->values, c->array[0]->cnt);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i=0; i<c->length; i++)
  {
    free(c->array[i]->values);
    free(c->array[i]);
  }
  free(c->array);
  free(c);
}
