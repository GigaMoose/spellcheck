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
/* 
Open file
read a word from the file
get a hash for the word
check hash array to see if the word is a real word
if the word comes back true, it is real word, go to next word.  If false, add that word to the misspelled array and increase the # of mispelled word counter
close file
return should be the # of mispelled words (from the counter)

    Set int num_misspelled to 0.
    While line in fp is not EOF (end of file):
        Read the line.
        Split the line on spaces.
        For each word in line:
            Remove punctuation from beginning and end of word.
            If not check_word(word):
                Append word to misspelled.
                Increment num_misspelled.
    Return num_misspelled.
*/


// Set int num_misspelled to 0.
int num_misspelled = 0;
size_t len = 60;
char * line = NULL;
char * found_words;

line = (char *)malloc(len * sizeof(char));

//While line in fp is not EOF (end of file):
// I tried to get this line to work for hours, and it would only read the first word, switching to fgets
while (getline(&line, &len, fp) != -1) {
//while (fgets(line, HASH_SIZE, fp) != NULL) {
    //Read the line.
    //printf("read the line - %s\n", line);


    //Split the line on spaces.
    found_words = strtok(line, " \t\r\n");
    //printf("found words - %s\n", found_words);

    while (found_words != NULL) {
        //printf("found words - not null\n");
        int p = strlen(found_words);
        //printf("strlen: %i    word: %s\n", p, found_words);
        if (strlen(found_words) > LENGTH) {
            found_words = strtok(NULL, " \n");
            continue;
        }
       //Remove Punctionation - Front and Back of word.
        int i;
        char * fixed_word;
        //printf("The current FOUND word is - %s\n", found_words); 
        for(i=strlen(found_words)-1; ispunct(found_words[i]);--i)
            found_words[i]='\0';

        for(fixed_word=found_words;ispunct(*fixed_word);++fixed_word); 

        //fixed_word = found_words;
        found_words = fixed_word;

        
        //printf("The current fixed word is - %s\n", found_words); 

        //If not check_word(word):
        if(!check_word(found_words, hashtable)) {
            //Append word to misspelled.
            misspelled[num_misspelled] = (char *)malloc(sizeof(char)*(LENGTH+1));
            strcpy(misspelled[num_misspelled],found_words);
            //misspelled[num_misspelled] = found_words;
        
            //printf("Mispelled word - %s.  This is mispelled word # %d\n", found_words, num_misspelled+1);

            //Increment num_misspelled.
            num_misspelled++;
        }   
        found_words = strtok(NULL, " \n");
    }

    
}
    //Return num_misspelled.
	return num_misspelled; 

}


// Returns true if word is in dictionary else false.

bool check_word(const char* word, hashmap_t hashtable[]) {
    /* NOTES: Function called hash.  Going to have to figure out which bucket it's in.  Search for the bucket that matches the hash.  if that word is not in that bucket, return a fals (it does not exist)
    a hash function could return a negative number, it will crash - check that hashvalue >0 and < hash limit.
    When you take the word, make sure it's < limit.  Not guarenteed that what is passed is within limits.  If it's >, it's mispelled.  Return false.  Strlen on the constant, and if > length - send false
    If the hash <0 or beyond limit, send false
    If found, true.

    Set int bucket to the output of hash_function(word).
    Set hashmap_t cursor equal to hashmap[bucket].
    While cursor is not NULL:
        If word equals cursor->word:
            return True.
        Set curosr to cursor->next.
    Set int bucket to the output of hash_function(word).
    Set hashmap_t cursor equal to hashmap[bucket].
    While cursor is  not NULL:
        If lower_case(word) equals curosr->word:
            return True.
        Set curosr to cursor->next.
    return False.
*/
    //printf("Check word\n");
    //printf("What is my word - %s\n", word);

    char lcword[LENGTH+1];
    int wordsize;

    wordsize = strlen(word);


    
    //lowercase the word, prof said this is ok
    for (int i=0; i <= wordsize; i++) {
        lcword[i] = tolower(word[i]);
    }
    
    //Set int bucket to the output of hash_function(word).
    int bucket = hash_function(lcword);
    
    


    //caseresult = strcasecmp(word, cursor->word);
    //printf("return: %d\n", caseresult);

    lcword[wordsize] = '\0';

    //Set hashmap_t cursor equal to hashmap[bucket].
    hashmap_t cursor = hashtable[bucket];
    //printf("Starting - lcword: %s    bucket word: %s\n", lcword, cursor->word);

    if (cursor != NULL) {
        //printf("Cursor is not NULL\n");
    }
    //While cursor is not NULL:
    while (cursor != NULL) {
        //If word equals cursor->word:
        if (strcmp(lcword, cursor->word) == 0) {
            //printf("Found! lcword: %s    bucket word: %s\n", lcword, cursor->word);
            //return True.
            return true;
        }
        //Set curosr to cursor->next.
        cursor = cursor->next;
        //printf("Looking - lcword: %s    bucket word: %s\n", lcword, cursor->word);
        //printf("NEXT CURSOR\n");
    }
    //return False.
	return false;
}


// Loads dictionary into memory.  Returns true if successful else false.

bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {
    /**Open FILE
    NOTES: read in a string at a time.  Word string.  only lowercase words.  Strip off punctionaries trailing.  Anything seperated by whitespace.  fscanf fgetf fgetc any of those.  
    Once you call in those words, you call his hashfunction, then it returns back a number (hash).  You want ot use the hash to put in to a linked __builtin_va_list
	You that word and that hash, in the linked list dictionary
    look for \n \r \feof(fptr)
    
    Initialize all values in hash table to NULL.
    Open dict_file from path stored in dictionary.
    If dict_file is NULL:
        return false.
    While word in dict_file is not EOF (end of file):
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

    char line[LENGTH] = "";
    int bucket;
    //int len = LENGTH;
    int wordsize = 0;
    node * last_node;
    
    //line = (char*) malloc(LENGTH*sizeof(char));
    //Initialize all values in hash table to NULL.
    for (int i = 0; i < HASH_SIZE; i++) {
            hashtable[i] = NULL;
        }
    //printf("Null Hashtable\n");

    //Open dict_file from path stored in dictionary.
    FILE * fp;

    fp = fopen(dictionary_file, "r");

    /*If dict_file is NULL:
        return false.*/
    if (fp == NULL){
        //printf("Dictionary File NOT Opened Succesfully\n");
        return false;
    }
    //printf("Dictionary File Opened Succesfully: %s \n", dictionary_file);


    // While word in dict_file is not EOF (end of file):
    //while ((getline(&line, &len, fp)) != -1) {
    while (fgets(line, HASH_SIZE, fp) != NULL) {
        //Set hashmap_t new_node to a new node.
        //printf("Not EOF\n");

        


        //strip contrl characters at the end.
        line[strcspn(line, "\r\n")] = 0;
        wordsize = strlen((const char *)line);
        //wordsize = 4;
        

        //lowercase
        for (int i=0; i <= wordsize; i++) {
            line[i] = tolower(line[i]);
        }
        
        if (line[wordsize] != '\0') {
            line[wordsize] = '\0';
        }

        //Set new_node->word equal to word.
        
        //printf("Word is: %s     word size is:  %i\n", line, wordsize);
        

        
        //Set int bucket to hash_function(word).
        bucket = hash_function(line);

        if ((bucket < 0) || (bucket > HASH_SIZE)) {
            continue;
        }

        if (hashtable[bucket] == NULL) {        
            hashtable[bucket] = (node*)malloc(sizeof(node));
            //printf("malloc\n");
            hashtable[bucket]->next = NULL;
        }
        else {
            last_node = hashtable[bucket];
            hashtable[bucket] = (node*)malloc(sizeof(node));
            hashtable[bucket]->next = last_node;
        }


        if(hashtable[bucket] == NULL){
            //printf("Unable to create new_node.\n");
            exit(0);
        }
        //Set new_node->next to NULL.
        strcpy(hashtable[bucket]->word,line);
        //printf("Set new_node next to null\n");

        //printf("wordsize: %ld\n", wordsize);
        //printf("bucket is Hashed now\n");
        //make sure not to overrun the bucket  Make sure it's >0 and <HASHSIZE, if it is, continue
       
        //printf("this is a test\n");
        //if hashtable[bucket] is NULL:
            //Set hashtable[bucket] to new_node.
        //else:
            //Set new_node->next to hashtable[bucket].
            //Set hashtable[bucket] to new_node. */

        //printf("%i\n", bucket);

    }
    // Close dict_file.
    //free(line);
    //printf("free line\n");

    //line = NULL;
    //printf("NULL line\n");

    fclose(fp);
    //printf("close file\n");
    
    return true;
}

