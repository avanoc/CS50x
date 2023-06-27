#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get positive integer from user.
    int n;
    do
    {
        n = get_int("Width: ");
    }
    while (n < 1 || n > 8);

    //Print out how wide is the wall
    for (int i = 0; i < n; i++) // genero un loop de n repeticiones
    {
        for (int k = n - i - 2; k >= 0; k--)
        {
            printf(" ");
        }
        for (int j = 0; j < i + 1; j++) // genero un loop de i + 1 repeticiones de otra variable
        {
            printf("#"); // cada repetición va a generar un "#"
        }
        printf("\n"); // al final del loop, se imprime un salto de renglón.
    }
}