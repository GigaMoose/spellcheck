#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Returns true if all words are spelled correctly, false otherwise. Array misspelled is populated with words that are misspelled.

int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {

	return 0;
}


// Returns true if word is in dictionary else false.

bool check_word(const char* word, hashmap_t hashtable[]) {

	return false;
}


// Loads dictionary into memory.  Returns true if successful else false.

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {
    /**Open FILE
    read in a string at a time.  Word string.  only lowercase words.  Strip off punctionaries trailing.  Anything seperated by whitespace.  fscanf fgetf fgetc any of those.  
    Once you call in those words, you call his hashfunction, then it returns back a number (hash).  You want ot use the hash to put in to a linked __builtin_va_list
	You that word and that hash, in the linked list dictionary
    look for \n \r \feof(fptr)
    */

   
    //Initialize all values in hash table to NULL.
    for (int i = 0; i < HASH_SIZE; i++){
        hashtable[i] = NULL; 
    }

    //Open dict_file from path stored in dictionary.
    FILE * fp; 

    fp = fopen(dictionary_file, "r");

    /*If dict_file is NULL:
        return false.*/
    if (fp == NULL){
        return false;
    }


    /* While word in dict_file is not EOF (end of file):
        Set hashmap_t new_node to a new node.
        Set new_node->next to NULL.
        Set new_node->word equal to word.
        Set int bucket to hash_function(word).
        if hashtable[bucket] is NULL:
            Set hashtable[bucket] to new_node.
        else:
            Set new_node->next to hashtable[bucket].
            Set hashtable[bucket] to new_node.
    Close dict_file.
    */
    


    //return false;
}

