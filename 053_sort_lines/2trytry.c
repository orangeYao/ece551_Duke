#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char a[40] = "abcd";
    size_t s =0;
    char **b;
    b = malloc(sizeof(char*)*50);
    b[0] = malloc(128);

    strcpy(b[0], a);
    printf("%s\n", b[0]);



    free(b);
    return 0;
}

