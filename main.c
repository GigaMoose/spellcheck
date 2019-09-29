#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>


int main(int argc, char * argv[]) {
    node * hashtable[HASH_SIZE];
    //char *misspelled[MAX_MISSPELLED];
    load_dictionary(argv[2], hashtable);
    //printf("%s\n", hashtable[30]->word);
    //printf("%s\n", hashtable[15]->word);
    //printf("%s\n", hashtable[33]->word);

    //check_word(argv[1], hashtable);

    FILE * fp;

    fp = fopen(argv[1], "r");

    /*If dict_file is NULL:
        return false.*/
    if (fp == NULL) {
        printf("Text File NOT Opened Succesfully\n");
        return false;
    }
    if (fp != NULL) {
        printf("Text File Opened Succesfully\n");
    }

char *misspelled[MAX_MISSPELLED];
	int num_misspelled = check_words(fp, hashtable, misspelled); 

    printf("mispelled: #%d\n", num_misspelled);
    //create misspelled array
    
	node * new_node;

    for (int i=0; i< HASH_SIZE; i++ )
    {
        if ( hashtable[i] == NULL ) { continue; }
        //printf ("%s %i \n", hashtable[i]->word, i) ;
        new_node = hashtable[i] ;
        while ( new_node->next != NULL )
        {
            //printf ("new_word is: %s \n", new_node->word);
            new_node = new_node->next ;
            //printf ("%s %i \n", new_node->word, i) ;
        }
    }
}

