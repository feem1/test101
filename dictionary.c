/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
#define SIZE 27
#define LENGTH 26
int hash(const char *word);
char word[LENGTH + 1];
int cnt = 0;
typedef struct node 
{
    char *word;
    struct node *next;
} node;
node *hashs[SIZE];

// check if word is in dictionary

bool check(const char *word)
{
    node *newnode = malloc(sizeof(newnode));
    int hashi = hash(word);
    newnode = hashs[hashi];
    
    while(newnode != NULL) 
    {
        if (strcasecmp(word, newnode->word) == 0)
        {
	        return true;
        }
        newnode =newnode->next;
    }
    return false;
}


// loads dictionary

bool load(const char *dictionary)
{
    FILE *fp = NULL;
	for (int i=0;i<SIZE ;i++ )
	{
		hashs[i]=NULL;
	}
    if (!(fp = fopen(dictionary,"r")))
    {
        return false;
    }
	int h=0;
	while (fscanf(fp,"%s\n",word)!= EOF)
    {
        node *push =malloc(sizeof(node));
        push->word =malloc(strlen(word) +1);
        strcpy(push->word,word);
		h = hash(word);
		cnt++;
		if(hashs[h] ==NULL)
		{
    		hashs[h]=push;
			push->next=NULL;
		}
		else 
		{
			push->next=hashs[h];
			hashs[h]=push;
		}
	}
  
  return true;
}

// # of words loaded in dictionary

unsigned int size(void)
{
  return cnt;
}

//unloads the dictionary
bool unload(void)
{
    for (int i = 0; i < SIZE; i++)
    {
        node *nodep;
        nodep = hashs[i];

        while (nodep)
        {
            node* nodetmp = nodep;
            nodep = nodep->next;
            free(nodetmp);
            return true;
        }
        hashs[i] = NULL;
    }

    return false;
}


int hash(const char *word) 
{
    int len=strlen(word);
    int hash=0;
	for(int i=0;i<len; i++)
    {
        int x = word[i];
        if (x>64&&x<91)
        {
            hash+=word[i]+32;
        }
        else
        {
            hash+=word[i];
        }
    }
    
    return hash %SIZE; 
}