// Any variable I define globally (outside a specific function) may be used by any function in the pgm.

#include <stdio.h>
#include <cs50.h>

float global = 0.505; // define variable: global
void triple(void); // declare function: triple
void twice(void); // declare function: twice

int main (void)
{
    triple(); // do function triple
    printf ("%f\n", global); // prints out: 1.515 (0.505 * 3)
    // If I also ask the pgm to do function twice:
    // twice();
    // printf ("%f\n", global);
    // it would print out 3.030 (0.505 * 3 * 2)
}

void triple(void) // define function: triple
{
    global *= 3;
}

void twice(void) // define function twice
{
    global *= 2;
}
