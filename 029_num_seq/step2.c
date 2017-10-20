//This file is for Step 2.
//You should do 
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
// 
// Be sure to #include any header files you need!

#include <stdlib.h>
#include <stdio.h>

int helper1Seq2(int x, int sum)
{
    if (x == -1)
        return sum-1;
    else
    {
        int diff = (x - (-1)) * 2; 
        return helper1Seq2(x-1, sum+diff);
    }
}


int helper2Seq2(int x, int sum)
{
    if (x == -2)
        return sum-1;
    else
    {
        int diff = ((-2) - x) * 2;
        return helper2Seq2(x+1, sum+diff);
    }
}

int seq2(int x)
{
    if (x>=-1)
        return helper1Seq2(x, 0);
    else
        return helper2Seq2(x, 0);
}

int sumSeq2(int low, int high)
{
    int for_return = 0;
    for (int i=low; i<high; i++)
        for_return += seq2(i);
    return for_return;
}


int main()
{

    for (int x=-4; x<4; x++)
        printf("seq2(%d) = %d\n", x, seq2(x));

    int a = 3, b = 6;
    printf("sumSeq2(%d, %d) = %d\n", a, b, sumSeq2(a, b));

    a = 9;
    b = 7; 
    printf("sumSeq2(%d, %d) = %d\n", a, b, sumSeq2(a, b));

    a = -1000;
    b = 100;
    printf("sumSeq2(%d, %d) = %d\n", a, b, sumSeq2(a, b));

	return EXIT_SUCCESS;
}
