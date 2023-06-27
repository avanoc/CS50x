// Any variable I define locally (within a specific function) will only be recognized by that function.

#include <stdio.h>
#include <cs50.h>

int triple(int); // declare function: triple
int twice(int); // declare function: twice

int main (void)
{
    int foo = 4;
    // triple(foo); // do function triple with varibale foo
    // printf ("%i\n", foo); // prints out: 4, because local variables are not overwritten by other functions.
    // To get 12 I need to tell the pgm that foo will change by using the function "triple".
    foo = triple (foo),
    printf ("%i\n", foo);
}

int triple(int x) // define function: triple
{
    return x*=3;
}

int twice(int x) // define function twice
{
    return x*=2;
}
