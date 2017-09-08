#include <stdio.h>
#include <stdlib.h>

size_t  maxSeq(int * array, size_t n);

size_t  ownMaxSeq(int * array, size_t n)
{
	if (n==0)
		return 0;

    size_t max=1, tmp_max=1;
    for (int i=1; i<n; i++)
    {
        if (array[i] > array[i-1])
            tmp_max++;
        else
        {
            if (max < tmp_max)
                max = tmp_max;
            tmp_max=1;
        }
    }
    return max;
}

void compare(int * array, size_t n)
{
	if (ownMaxSeq(array, n) != maxSeq(array, n))
		exit(EXIT_FAILURE);
    return;
}


int main()
{
    int a[] = {1,2,3,4,5,6,-1,9}; 
    compare(a, 8);

    int b[] = {1,-1,-3,498,5,6,-1,9}; 
    compare(b, 8);

    int c[] = {1};
    compare(c, 1);
    compare(c, 0);

    int d[] = {1,2,2,4,4,6,-1,9}; 
    compare(d, 8);

    int e[] = {1,2,2,4,4,6,-1,9}; 
    compare(e, 8);

    return EXIT_SUCCESS;
}

