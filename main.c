#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <check.h>
#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


bool check_word(const char* word, hashmap_t hashtable[]);

int main(int argc, char * argv[])
{
    node * hashtable[HASH_SIZE];
    load_dictionary(argv[2], hashtable);
   // printf("%s\n", hashtable[30]->word);
   // printf("%s\n", hashtable[15]->word);
   // printf("%s\n", hashtable[33]->word);

    check_word(argv[1], hashtable);

    node * new_node;

    for (int i=0; i< HASH_SIZE; i++ )
    {
        if ( hashtable[i] == NULL ) { continue; }
        //printf ("%s %i \n", hashtable[i]->word, i) ;
        new_node = hashtable[i] ;
        while ( new_node->next != NULL )
        {
            new_node = new_node->next ;
            //printf ("%s %i \n", new_node->word, i) ;
        }
    }

    
 }
