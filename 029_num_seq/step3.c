//This file is for Step 3.
//You should do 
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
// 
// Be sure to #include any header files you need!

#include <stdlib.h>
#include <stdio.h>

int seq3(int x, int y)
{
    int for_return = 0;
    for_return += 2 * y;
    int x_diff = -3 + y;
    for_return += x * x_diff;
    return for_return;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi)
{
    int count = 0;
    for (int i=xLow; i<xHi; i++)
        for (int j=yLow; j<yHi; j++)
            if (seq3(i, j) % 2 == 0)
                count ++;
    return count;
}

int main()
{

    int a = -4, b = -5;
    printf("seq3(%d, %d) = %d\n", a, b, seq3(a,b));

    a = 5; 
    b = -5;
    printf("seq3(%d, %d) = %d\n", a, b, seq3(a,b));

    int xLow=0, xHi=2, yLow=0, yHi=3;
    int result = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
    printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, result);

    xLow=-100;
    yLow=-100;
    xHi=101;
    yHi=101;
    result = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
    printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, result);


    return EXIT_SUCCESS;
}
