#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME

  char * ptr = strstr(inputName, ".txt");
  if (ptr == NULL)
      return NULL;

  char * for_return;

  size_t len = strlen(inputName);  
  for_return = malloc(len + 10);

  strncpy(for_return, inputName, len);
  strcpy(for_return + len, ".count");
  return for_return;
}
