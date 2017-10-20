#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "kv.h"

void printPair(kvpair_t* pair)
{
  if (pair == NULL)
    printf("null !\n");
  else
    printf( "key = '%s' value = '%s'\n", pair->key, pair->value);
}

void getPairs(kvpair_t **pair, char * c)
{
  ssize_t s = strlen(c);
  char * ptr = strchr(c, '=');
  if (ptr == NULL)
    perror("no equal sign found");


  *pair = malloc(2*sizeof(char*));
  (*pair)->key = malloc(ptr - c + 6);
  (*pair)->value = malloc(s - (ptr - c) + 6);

  strcpy((*pair)->value, ptr+1);

  *ptr = '\0';
  strcpy((*pair)->key, c);
  printPair(*pair);
}

int main()
{
    char a[] = "asdf=iiii";
	kvpair_t * p = NULL;
    getPairs(&p, a);
	printPair(p);

    free(p->key);
    free(p->value);
    free(p);


    return 0;
}
