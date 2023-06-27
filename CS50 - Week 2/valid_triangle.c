#include <cs50.h>
#include <stdio.h>

// DECLARATION OF FUNCTION
bool valid_triangle (float a, float b, float c);

int main (void)
{
    // prompt user to get lengths of the triangle
    float side_1 = get_float ("Type in a real number: ");
    float side_2 = get_float ("Type in another real number: ");
    float side_3 = get_float ("Type in yet another real number: ");

    if (valid_triangle (side_1, side_2, side_3) == true)
    {
        printf ("You can make a triangle\n");
    }
    else
    {
        printf ("You CAN'T make a triangle\n");
    }
}
// DEFINITION OF FUNCTION
bool valid_triangle (float a, float b, float c)
{
    // first condition, all possitive numbers
    if (a >= 0 && b >= 0 && c >= 0)
    {
        // second condition, the sum of two sides must be greater than the third side
        if ((a + b > c) && (b + c > a) && (c + a > b))
        {
            return true;
        }
        else
        {
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
    return true;
}