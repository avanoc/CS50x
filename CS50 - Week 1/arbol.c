#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Print out the tree
    for (int a = 0; a < 5; a++) // genero un loop de 5 repeticiones (altura)
    {
        for(int b = 0; b < a; b++)
        {
            printf("|");
            ;
        }
        printf("\n"); // al final del loop, se imprime un salto de renglón.
    }
        
}