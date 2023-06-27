#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int count_letters(string t); // Declare function count_letters.

int count_words(string t); // Declare function count_words.

int count_sentences(string t); // Declare function count_sentences.

int main(void)
{
    // Prompt user for text.
    string text = get_string("Text: ");
    // Calculate Coleman-Liau index.
    float L = count_letters(text) * 100.0 / count_words(text);
    float S = count_sentences(text) * 100.0 / count_words(text);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    // Print result.
    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}
int count_letters(string t) // Define function count_letters.
{
    char l = '\0';
    int letter_count = 0;
    for (int i = 0, n = strlen(t); i < n; i++)
    {
        l = t[i];
        if (isalpha(l))
        {
            letter_count ++;
        }
    }
    return letter_count;
}
int count_words(string t) // Define function count_words.
{
    char l = '\0';
    int word_count = 1; // word_count starts at 1 because after last word there's no space.
    for (int i = 0, n = strlen(t); i < n; i++)
    {
        l = t[i];
        if (l == ' ') // count spaces, to determine how many words there are.
        {
            word_count++;
        }
    }
    return word_count;
}
int count_sentences(string t) // Define function count_sentences.
{
    char l = '\0';
    int sentence_count = 0;
    for (int i = 0, n = strlen(t); i < n; i++)
    {
        l = t[i];
        if (l == '.' || l == '?' || l == '!')
        {
            sentence_count++;
        }
    }
    return sentence_count;
}