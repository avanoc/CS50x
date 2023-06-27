#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

//declare function: only digits.
bool only_digits(string s);

//declare function: rotate.
char rotate(char c, int k);

//define main, using command line arguments.
int main(int argc, string argv[])
{
    // Check how many arguments were typed in the command line.
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Check that the argument "argv[1]" is a digit.
    string argument = argv[1];
    bool is_digit = only_digits(argument);
    if (is_digit)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Transform argv[1] into digit
    int key = atoi(argv[1]);

    // Prompt user for plaintext.
    printf("plaintext:  ");
    string plaintext = get_string("");
    printf("ciphertext: ");

    // Rotate each character, according to the key entered, and print out the result.
    for (int j = 0, o = strlen(plaintext); j < o; j++)
    {
        char ciphertext = rotate(plaintext[j], key);
        printf("%c", ciphertext);
    }
    printf("\n");
    return 0;
}
// define function: only_digits.
bool only_digits(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        int is_digit = isdigit(s[i]);
        if (is_digit == 0)
        {
            return 1;
        }
    }
    return 0;
}
// define function: rotate.
char rotate(char c, int k)
{
    char cipher;
    if (isupper(c))
    {
        cipher = ((c - 65 + k) % 26) + 65;
    }
    else if (islower(c))
    {
        cipher = ((c - 97 + k) % 26) + 97;
    }
    else
    {
        cipher = c;
    }
    return cipher;
}