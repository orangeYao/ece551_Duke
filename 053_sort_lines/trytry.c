#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char *a = NULL;
    size_t s;
    char **b = NULL;
    b = realloc(b, sizeof(a) * 5);

    char *c, *d;

    getline(&a, &s, stdin);
    b[0] = a;
    c = a;
    getline(&a, &s, stdin);
    b[1] = a;
    d = a;
//getline(&a, &s, stdin);
//    a = "testing";

    printf("%s\n", a);
    printf("%s\n", b[0]);
    printf("%s\n", b[1]);
    printf("%s\n", c);
    printf("%s\n", d);
    
    free(a);
    free(b);
    return 0;
}
