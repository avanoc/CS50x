#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Ask for user's name
    string name = get_string("What's your name: ");
    // Greet user using their name
    printf("hello, %s\n", name);
}