#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int i = 0;
 // int i = 1; <- opción 2
 // int i = 50; <- opción 3

    while (i < 50)//(true) infinte loop, never stops
 // while (i <= 50) <- opción 2
 // while (i > 0) <- opción 3
    {
        printf("hello, world\n");
        i++;
     // i--; <- opción 3
    }
}
