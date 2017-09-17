//This file is for Step 1.
//You should do 
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
// 
// Be sure to #include any header files you need!

#include <stdlib.h>
#include <stdio.h>

int helper1Seq1(int x, int sum)
{
    if (x == 0)
        return sum-3;
    else
       return helper1Seq1(x-1, sum+4);
}


int helper2Seq1(int x, int sum)
{
    if (x == 0)
        return sum-3;
	else
       return helper2Seq1(x+1, sum-4);
}

int seq1(int x)
{
	if (x>=0)
		return helper1Seq1(x, 0);
	else
		return helper2Seq1(x, 0);
}


void printSeq1Range(int low, int high)
{
    for (int i=low; i<high; i++)
    {
        printf("%d", seq1(i));
        if (i != high - 1)
            printf(",");
    }
    printf("\n");
}

int main()
{

    for (int x=-3; x<4; x++)
        printf("seq1(%d) = %d\n", x, seq1(x));

    int a = -2, b = 6;
    printf("printSeq1Range(%d,%d)\n", a, b);
    printSeq1Range(a, b);

    a = 2; b = 2;
    printf("printSeq1Range(%d,%d)\n", a, b);
    printSeq1Range(a, b);

    a = 7; b = 3;
    printf("printSeq1Range(%d,%d)\n", a, b);
    printSeq1Range(a, b);

    return EXIT_SUCCESS;
}
