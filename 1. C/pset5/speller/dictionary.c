// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//Number of words in the dictionary
int total_words = 0;

// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    node *cursor = table[index];

    if (cursor != NULL)
    {
        while (cursor != NULL)
        {
            if (strcasecmp(cursor->word, word) == 0)
            {
                return true;
            }
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c = *word;
    c = tolower(c);

    while (*word)
    {
        hash = ((hash << 5) + hash) + c;
        c = *word++;
        c = tolower(c);
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Opening the file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("It wasn't possible to open the file.\n");
        return false;
    }

    //Starting the whole hash table with NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    char words[LENGTH + 1]; //array that will store the words

    while (fscanf(file, "%s", words) != EOF)
    {
        //allocate a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            free(new_node);
            return false;
        }
        //if it was able to allocate, then the *N word will receive the word read of the file
        //and will inicializate the pontier with NULL
        else
        {
            strcpy(new_node->word, words);
            new_node->next = NULL;
        }
        unsigned int index = hash(words);
        if (table[index] != NULL)
        {
            new_node->next = table[index];
        }
        table[index] = new_node;
        total_words++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return total_words;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
