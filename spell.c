/*
Matt Saner - NYU
AppSec - Assignment 1
references and credits in references.txt
*/

#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
//#include <unistd.h>

// Returns true if all words are spelled correctly, false otherwise. Array misspelled is populated with words that are misspelled.

int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {

	return 0;
}


// Returns true if word is in dictionary else false.

bool check_word(const char* word, hashmap_t hashtable[]) {
    /* NOTES: Function called hash.  Going to have to figure out which bucket it's in.  Search for the bucket that matches the hash.  if that word is not in that bucket, return a fals (it does not exist)
    a hash function could return a negative number, it will crash - check that hashvalue >0 and < hash limit.
    When you take the word, make sure it's < limit.  Not guarenteed that what is passed is within limits.  If it's >, it's mispelled.  Return false.  Strlen on the constant, and if > length - send false
    If the hash <0 or beyond limit, send false
    If found, true.

*/
	return false;
}


// Loads dictionary into memory.  Returns true if successful else false.

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {
    /**Open FILE
    NOTES: read in a string at a time.  Word string.  only lowercase words.  Strip off punctionaries trailing.  Anything seperated by whitespace.  fscanf fgetf fgetc any of those.  
    Once you call in those words, you call his hashfunction, then it returns back a number (hash).  You want ot use the hash to put in to a linked __builtin_va_list
	You that word and that hash, in the linked list dictionary
    look for \n \r \feof(fptr)
    */

    char * line = NULL;
    int bucket;
    size_t len = 0;


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
        //printf("Dictionary File NOT Opened Succesfully\n");
    }
    //printf("Dictionary File Opened Succesfully: %s \n", dictionary_file);

    for(int i = 0; i < HASH_SIZE; i++){
            hashtable[i] = NULL;
        }
    //printf("Null Hashtable\n");

    // While word in dict_file is not EOF (end of file):
    while ((getline(&line, &len, fp)) != -1){
        //Set hashmap_t new_node to a new node.
        //printf("Not EOF\n");

        node * new_node = (node*)malloc(sizeof(node));
        //printf("malloc\n");

        if(new_node == NULL){
            //printf("Unable to create new_node.\n");
            exit(0);
        }


        //Set new_node->next to NULL.
        new_node->next = NULL;
        //printf("set new node next to null\n");


        //Set new_node->word equal to word.
        line[strcspn(line, "\r\n")] = 0;


        strncpy(new_node->word,line,strlen(line));
        //printf("Dictionary word: %s...  Bucket #: %d\n", line, bucket);

        //Set int bucket to hash_function(word).
        bucket = hash_function(new_node->word);
        //printf("bucket is Hash\n");


        //if hashtable[bucket] is NULL:
            //Set hashtable[bucket] to new_node.
        //else:
            //Set new_node->next to hashtable[bucket].
            //Set hashtable[bucket] to new_node. */

        if(hashtable[bucket] != NULL){
            new_node->next = hashtable[bucket];
        }
        hashtable[bucket] = new_node;
    }

    // Close dict_file.
    free(line);
    //printf("free line\n");

    line = NULL;
    //printf("NULL line\n");

    fclose(fp);
    //printf("close file\n");

    return true;
}

