// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

// Temporary mug for one dict words
char mug[LENGTH + 1] = {'\0'};
unsigned int track_of_dict_words = 0;
int c;
int k = 0;
int j = 0;
int index = 0;
int p = 0;

// Creating nodes
struct node *getNode(void)
{
    struct node *pNode = (struct node *)calloc(1, sizeof(struct node));
    if (pNode)
    {
        pNode -> is_word = false;
        for(int i = 0; i < 27; i++)
        {
            pNode -> children[i] = NULL;
        }
    }
    return pNode;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    if (root == NULL)
    {
        return 0;
    }

    struct node *curr = root;

    while (*word)
    {
        if (!isalpha(*word))
        {
            index = 26;
        }
        else
        {
            index = tolower(*word) - 'a';
        }

        curr = curr -> children[index];

        if (curr == NULL)
        {
            return 0;
        }
        word++;
    }
    return curr -> is_word;
}

// Inserting values in dictionary in the memory
void insert(const char *key)
{
    index = 0;

    struct node *pCrawl = root;
    // Loop to add items
    while (*key)
    {
        if (!isalpha(*key))
        {
            index = 26;
        }
        else
        {
            index = tolower(*key) - 'a';
        }
        if ((pCrawl -> children[index]) == NULL)
        {
            pCrawl -> children[index] = getNode();
        }
        pCrawl = pCrawl -> children[index];

        key++;
    }
    pCrawl -> is_word = true;
}

// Loads dictionary returning true if successful
bool load(const char *dictionary)
{
    root = getNode();

    // Opening dictionary file
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return 3;
    }
    j = 0;
    for (c = fgetc(inptr); (c != EOF); (c = fgetc(inptr)))
    {
        if ((c == '\n') || (c == EOF))
        {
            ++track_of_dict_words;
            mug[j] = '\0';
            // Inserting into Trie
            insert(mug);
            j = 0;
        }
        else
        {
            mug[j] = c;
            ++j;
        }
    }
    fclose(inptr);
    if (c == EOF)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Returns number of words in dictionary
unsigned int size(void)
{
    return track_of_dict_words;
}

// Implements unload functionality
bool flush(struct node *voot)
{
    if (voot == NULL)
    {
        return true;
    }
    for (int i = 0; i < 27; i++)
    {
        flush(voot -> children[i]);
    }
    free(voot);
    return true;
}

// Unloads dictionary from memory
bool unload(void)
{
    flush(root);
    return true;
}
