#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"

START_TEST(test_dictionary_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(TESTDICT, hashtable));
    // Here we can test if certain words ended up in certain buckets
    // to ensure that our load_dictionary works as intended. I leave
    // this as an exercise.

    char * word1 = "first";
    char * word2 = "second";
    char * word3 = "third";
    char * word4 = "test";

    int hash1 = hash_function(word1);
    int hash2 = hash_function(word2);
    int hash3 = hash_function(word3);
    int hash4 = hash_function(word4);  

    char * tableword1 = hashtable[hash1]->word;
    char * tableword2 = hashtable[hash2]->word;
    char * tableword3 = hashtable[hash3]->word;
    char * tableword4 = hashtable[hash4]->word;

    ck_assert(strcmp(tableword1, word1) == 0); 
    ck_assert(strcmp(tableword2, word2) == 0);
    ck_assert(strcmp(tableword3, word3) == 0);
    ck_assert(strcmp(tableword4, word4) == 0);

}
END_TEST


START_TEST(test_check_word_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char* correct_word = "Justice";
    const char* punctuation_word_2 = "pl.ace";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(punctuation_word_2, hashtable));
}
END_TEST


START_TEST(test_check_words_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* expected[3];
    expected[0] = "sogn";
    expected[1] = "skyn";
    expected[2] = "betta";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("test1.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 3);
    bool test = strlen(misspelled[0]) == strlen(expected[0]);
    int len1 = strlen(misspelled[0]);
    int len2 = strlen(expected[0]);
    ck_assert_msg(test, "%d!=%d", len1, len2);
    ck_assert_msg(strcmp(misspelled[0], expected[0]) == 0);
    ck_assert_msg(strcmp(misspelled[1], expected[1]) == 0);
    ck_assert_msg(strcmp(misspelled[2], expected[2]) == 0);
}
END_TEST

START_TEST(test_check_words_multiple_lines)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("tests/test1.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 4);
}
END_TEST

START_TEST(test_check_words_single_line)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("tests/test2.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 0);
}
END_TEST

START_TEST(test_check_words_ucase_lcase)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("tests/test6.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 0);
}
END_TEST

START_TEST(test_check_words_numbers_and_words)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("tests/test4.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 44);
}
END_TEST

START_TEST(test_check_words_remove_punctuation)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("tests/test5.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 2);
}
END_TEST

START_TEST(test_check_words_longwords)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("tests/test9.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 6);
}
END_TEST

Suite *
check_word_suite(void)
{
    Suite * suite;
    TCase * check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_check_word_normal);
    tcase_add_test(check_word_case, test_check_words_normal);
    tcase_add_test(check_word_case, test_dictionary_normal);
    tcase_add_test(check_word_case, test_check_words_multiple_lines);
    tcase_add_test(check_word_case, test_check_words_single_line);
    tcase_add_test(check_word_case, test_check_words_ucase_lcase);
    tcase_add_test(check_word_case, test_check_words_numbers_and_words);
    tcase_add_test(check_word_case, test_check_words_longwords);
    suite_add_tcase(suite, check_word_case);

    return suite;
}

int
main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;
    
    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}


