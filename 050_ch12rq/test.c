#include <stdio.h>
#include <stdlib.h>

int main()
{
    //char *a = malloc(7 * sizeof(char));
	//free(a);    
    //free(NULL);
    //printf("test\n");
  size_t sz = 0;
  char * line = NULL;
  getline(&line, &sz, stdin);

  printf("%zu\n", sz);
  printf("%s", line);
  return EXIT_SUCCESS;
}
