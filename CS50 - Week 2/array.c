#include <cs50.h>
#include <stdio.h>

bool array[] = {1, 2, 3} // I'm creating an boolean array, called "array" that includes the arguments "1", "3" and "3". I don't need in this case, to include how many arguments there will be.

bool array[3] // an array itself is NOT a variable. To duplicate an array, I have to use a loop to duplicate each argument.
{
    int array[0] = 1; // each argument of an array is a variable
    int array[1] = 2;
    int array[2] = 3;
    
}

int foo[5] = {1,2,3,4,5}
int bar[5];
// bar = foo <- NOT ALLOWED
for(int j=0; j < 5, j++)
{
    bar[j] = foo[j]; // <- I have to iterate the js elements in "foo" to create js elements in "bar".
}

// A function that uses an array, actually modifies the array. Different from a function that uses a local variable, gets a copy of the variable.