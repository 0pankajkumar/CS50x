// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"

char mug[LENGTH + 1] = {'\0'};  //Temporary mug for one dict words
unsigned int track_of_dict_words = 0;
int c, k = 0, j = 0, index = 0, p = 0;

//Creating nodes
struct node *getNode(void)
{
    struct node *pNode = NULL;
    pNode = (struct node *)calloc(1, sizeof(struct node));
    if (pNode)
    {
        pNode -> is_word = false;
        for(int i = 0; i < 27; i++)
            pNode -> children[i] = NULL;
    }
    return pNode;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    struct node *pCrawl = root;
    while(word[p] != '\0')
    {
        if (isalpha(word[p]) || (word[p] == '\''))
        {
            if(isalpha(word[p]))
                index = ((int)(tolower(word[p])) - (int)'a');
            else
            {
                index = 26;
            }
            //printf("%i ", index);


            if ((pCrawl -> children[index]) != NULL)
            {
                pCrawl = pCrawl -> children[index];
            }
            else
            {
                return false;
            }
        }
        ++p;
    }
    //printf("\n-----  ");

    return pCrawl -> is_word;
}


//Inserting values in dictionary in the memory
void insert(const char *key)
{

    //Determining the length of the current word
    int length = 0;
    index = 0;
    for(int i = 0; i < LENGTH; i++)
    {
        if (key[i] == '\0')
            break;
        ++length;
    }

    struct node *pCrawl = root;

    for(int l = 0; l < length; l++)
    {
        if (isalpha(key[l]) || (key[l] == '\''))
        {
            if(isalpha(key[l]))
                index = ((int)tolower(key[l]) - (int)'a');
            else
                index = 26;
                //printf("%d\n", index);
            /*for(int asp = 0; asp < 26 ; asp++)
            {
                if (index == asp)
                    printf("%i", asp);
                else
                    printf("^");
            }*/


            if ((pCrawl -> children[index]) == NULL)
                pCrawl -> children[index] = getNode();

            pCrawl = pCrawl->children[index];
        }
    }

    //Marking last index as true to make it a word in dictionary
    pCrawl -> is_word = true;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    root = getNode();

    //Opening dictionary file
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        fclose(inptr);
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
            insert(mug);  //Inserting into Trie
            j = 0;
            /*for(int i = 0; i < LENGTH + 1; i++) //Reinitializing all elements with null
                mug[i] = '\0';*/
        }
        if (isalpha(c))
        {
            mug[j] = c;
            ++j;
        }
    }

    if (c == EOF)
    {
        printf("\nLoad Successful.");
        return true;
    }

    else
        return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return track_of_dict_words;
}

bool flush(struct node *voot)
{
    if (root == NULL)
        return true;
    for (int i = 0; i < 26; i++)
    {
        flush(voot -> children[i]);

    }
    free(voot);
    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    flush(root);
    return true;
}
