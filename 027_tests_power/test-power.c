#include <stdlib.h>
#include <stdbool.h>
unsigned power (unsigned x, unsigned y);

unsigned real_power(unsigned x, unsigned y)
{
    if (x==0 && y ==0)
        return 1;

    if (x == 0)
        return 0;

    unsigned ans = 1;
    while (y--)
        ans *= x;
    return ans;
}


void run_check(unsigned x, unsigned y)
{
    unsigned expected_ans = real_power(x, y);
    if (power(x, y) != expected_ans)
        exit(EXIT_FAILURE);
    return;
}

int main(void)
{
    run_check(5, 8);
    run_check(1, 1);
    run_check(0, 1);
    run_check(12, 12);
    run_check('a', 'a');
    run_check(1.1, 1.1);

    run_check('1', '1');
    run_check('1', 1);
    run_check(1, '1');
    run_check(0, 0);
    run_check(-1, 0);


    return EXIT_SUCCESS;
}
