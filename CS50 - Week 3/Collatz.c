#include <cs50.h>
#include <stdio.h>

int collatz(int i, int step);

// Calculate how many steps it takes to get to 1, from n, using Collatz conjecture.
int main(void)
{
    int n = get_int("n: ");
    collatz(n, 0);
}

// Collatz conjecture:
int collatz(int i, int step)
{
    if (i == 1)
    {
        printf("steps: %i\n", step);
    }
    else if (i%2 == 0)
    {
        return collatz(i / 2, step + 1);
    }
    else if (i%2 != 0)
    {
        return collatz(3 * i + 1, step + 1);
    }
    return 1;
}