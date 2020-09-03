#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void mergeSort(pair *V, int start, int end);
void merge(pair *V, int start, int middle, int end);
bool cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0) //if the name passed in the function equals to the name of canditate
        {
            ranks[rank] = i; //update the rank array in the position 'rank' passed in the function with the index of the candidate
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[]) //it will receive one rank array at a time
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] ++;  //it will update acording to the voter's rank preference
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count ++;
            }
        }
    }
    return;
}

//function that will do the decresing sort
void merge(pair *V, int start, int middle, int end)
{
    int p1, p2, length, i, j, k;
    pair *temp;
    int end1 = 0;
    int end2 = 0;
    length = end - start + 1;
    p1 = start;
    p2 = middle + 1;
    temp = malloc(length * sizeof(pair));

    if (temp != NULL)
    {
        for (i = 0; i < length; i++)
        {
            if (!end1 && !end2)
            {
                if (preferences[V[p1].winner][V[p1].loser] >= preferences[V[p2].winner][V[p2].loser])
                {
                    temp[i] = V[p1++];
                }
                else
                {
                    temp[i] = V[p2++];
                }
                if (p1 > middle)
                {
                    end1 = 1;
                }
                if (p2 > end)
                {
                    end2 = 1;
                }
            }
            else
            {
                if (!end1)
                {
                    temp[i] = V[p1++];
                }
                else
                {
                    temp[i] = V[p2++];
                }
            }
        }
        for (j = 0, k = start; j < length; j++, k++)
        {
            V[k] = temp[j];
        }
    }
    free(temp);
}

void mergeSort(pair *V, int start, int end)
{
    int middle;
    if (start < end)
    {
        middle = floor((start + end) / 2);
        mergeSort(V, start, middle);
        mergeSort(V, middle + 1, end);
        merge(V, start, middle, end);
    }
    return;
}


// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    mergeSort(pairs, 0, pair_count - 1);
    return;
}

bool cycle(int first, int second)
{
    if (first == second)
    {
        return true;
    }
    else
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][first] == true)
            {
                if (cycle(i, second))
                {
                    return true;
                }
            }
        }
        return false;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser)) //if it does not form a cycle
        {
            locked[pairs[i].winner][pairs[i].loser] = true; //then I can create the arrow
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int winner;
    int k;

    for (int i = 0; i < candidate_count; i++)
    {
        k = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false) //if doesn't have a arrow j -> i
            {
                k++;
            }
        }

        if (k == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

