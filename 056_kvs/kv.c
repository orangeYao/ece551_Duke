#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


void printPair(kvpair_t* pair)
{
  printf( "key = '%s' value = '%s'\n", pair->key, pair->value);
}

kvpair_t * getPairs(char * c)
{
  kvpair_t *pair;
  ssize_t s = strlen(c);
  char * ptr = strchr(c, '=');
  if (ptr == NULL)
  {
    perror("no equal sign found");
    exit(EXIT_FAILURE);
  }

  pair = malloc(2*sizeof(char*));
  pair->key = malloc(ptr - c + 1);
  pair->value = malloc(s - (ptr - c) + 1);

  *(c + s -1) = '\0'; //remove \n
  strcpy(pair->value, ptr + 1);
  *ptr = '\0';
  strcpy(pair->key, c);
  return pair;
}


kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE *f = fopen(fname, "r");
  if (f == NULL)
  {
    perror("can't open file");
    exit(EXIT_FAILURE);
  }

  char * readin = NULL;
  size_t s = 0;
  int i = 0;
  kvarray_t * pairs;
  pairs = malloc(sizeof(*pairs));
  pairs->array = NULL;
  pairs->length = 0;


  while(getline(&readin, &s, f)>0)
  {
    pairs->length ++;
    pairs->array = realloc(pairs->array, pairs->length * sizeof(kvpair_t*));
    //array of pair pointers

    pairs->array[i] = getPairs(readin);
    i++;
  }

  free(readin);
  if(fclose(f) != 0)
  {
    perror("can't close file");
    exit(EXIT_FAILURE);
  }
  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i=0; i<pairs->length; i++)
  {
    free(pairs->array[i]->key);
    free(pairs->array[i]->value);
    free(pairs->array[i]);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i=0; i<pairs->length; i++)
  {
    printPair(pairs->array[i]);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i=0; i<pairs->length; i++)
    if(strcmp(pairs->array[i]->key, key) == 0)
      return pairs->array[i]->value;

  return NULL;
}

