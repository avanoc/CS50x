#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1; // global variable representing the number of candidates in the election. Copies CLA.
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: "); // Asks the user to type in the number of voters.

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: "); // lets everyone type in their vote.

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0) // check if name given is a valid candidate.
        {
            candidates[i].votes ++; // assign 1 vote to the candidate.
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election.
void print_winner(void)
{
    // TODO
    // Sort the vote count from more votes to less votes.
    candidate temp;
    for (int j = 0; j < candidate_count; j++)
    {
        for (int i = 0; i < candidate_count - 1; i++)
        {
            if (candidates[i].votes < candidates[i + 1].votes)
            {
                temp = candidates[i];
                candidates[i] = candidates[i + 1];
                candidates[i + 1] = temp;
            }
        }
    }

    // Print (first) winner.
    string winner = candidates[0].name;
    printf("%s\n", winner);

    //Print other winners if there's a tie.
    string tie;
    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[0].votes == candidates[i].votes)
        {
            tie = candidates[i].name;
            printf("%s\n", tie);
        }
    }
    return;
}