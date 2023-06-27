// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <cs50.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash the word
    int h = hash(word);
    // find words in hash table
    node *hashed = table[h];
    while (hashed != NULL)
    {
        // compare word with words in hash location of the table
        if (strcasecmp(word, hashed->word) != 0)
        {
            hashed = hashed->next;
        }
        else
        {
            return true;
        }
    }
    return false;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function: it counts every letter from the word and gets the sum of each letter's value as well, then it multiplies these two values to assing the hash value (I did it by myself)
    int h1 = 0;
    int h2 = 0;
    if (isalpha(word[0]) || strcmp(&word[0], "'") == 0)
    {
        for (int i = 0; i < strlen(word + 1); i++)
        {
            if (word[i] != 0)
            {
                h1++;
                h2 = h2 + tolower(word[i]);
            }
        }
        return (h1 * h2) % N;
    }
    return 1;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open file
    FILE *dic = fopen(dictionary, "r");
    if (dic != NULL)
    {
        // Read every word
        char dic_word[LENGTH + 1];
        while (fscanf(dic, "%s", dic_word) != EOF)
        {
            // Create a new node for each word
            node *n = malloc(sizeof(node));
            if (n != NULL)
            {
                strcpy(n->word, dic_word);
                // Hash the word and locate it at the linked list
                int h = hash(dic_word);
                if (table[h] == NULL)
                {
                    n->next = NULL;
                    table[h] = n;
                }
                else
                {
                    n->next = table[h];
                    table[h] = n;
                }
            }
        }
    }
    // Close dictionary:
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    int s = 0;
    if (&load)
    {
        for (int i = 0; i < N; i++)
        {
            node *count = table[i];
            while (count != NULL)
            {
                count = count->next;
                s++;
            }
        }
        return s;
    }
    return s;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Create a new temporary node:
    node *tmp = NULL;
    // Loop into the hash table, and free each node:
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            tmp = table[i];
            table[i] = table[i]->next;
            free(tmp);
        }
    }
    return true;
}