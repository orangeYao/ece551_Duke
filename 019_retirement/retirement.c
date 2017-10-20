#include <stdlib.h>
#include <stdio.h>

struct _retire_info
{
    int months;
    double contribution;
    double rate_of_return;
};
typedef struct _retire_info retire_info;

typedef struct
{
    int year;
    int month;
}timeStrc;

timeStrc convert(int m)
{
    timeStrc t;
    t.year = m/12;
    t.month = m%12;
    return t;
}


void retirement (int startAge,   //in months
				   double initial, //initial savings in dollars
				   retire_info working, //info about working
				   retire_info retired) //info about being retired
{
    double balance = initial;
    for (int i=0; i<working.months; i++)
    {
        timeStrc t = convert(startAge + i); 
        printf("Age %3d month %2d you have $%.2lf\n", t.year, t.month, balance);
        balance += balance * working.rate_of_return; 
        balance += working.contribution;
    }
    
    for (int i=0; i<retired.months; i++)
    {
        timeStrc t = convert(startAge + working.months + i);
        printf("Age %3d month %2d you have $%.2lf\n", t.year, t.month, balance);
        balance += balance * retired.rate_of_return;
        balance += retired.contribution;
    }
}


int main(void)
{
    retire_info working, retired;
    working.months = 489;
    working.contribution = 1000;
    working.rate_of_return = 0.045/12;

    retired.months = 384;
    retired.contribution = -4000;
    retired.rate_of_return = 0.01/12;

    retirement(327, 21345, working, retired);
    return 0;
}
