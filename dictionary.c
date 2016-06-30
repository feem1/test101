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
#include "dictionary.h"
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
    int h;
	for (int i=0;i<SIZE ;i++ )
	{
		hashs[i]=NULL;
	}
    if (!(fp = fopen(dictionary,"r")))
    {
        return false;
    }
  

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
    node *nextnode,*nodei;
    for (int i=0;i<SIZE;i++)
    {
        nodep =hashs[i];
        while (nodei)
        {
	        free(nodei->word);
	        nextn = nodei->next;
	        free(nodei);
	        nodei = nextnode;
        }   
        hashs[i] = NULL;
    }
  return true;
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