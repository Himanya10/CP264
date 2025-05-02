/*
 --------------------------------------------------
 Project: a3q2
 File:    myword.h
 Author:  Himanya Verma
 Version: 2025-01-31
 --------------------------------------------------
 */
#ifndef MYWORD_H
#define MYWORD_H

#include <stdio.h>

typedef enum boolean {

	FALSE = 0,
	TRUE = 1

} BOOLEAN;

typedef struct word {

	char word[100];
	int count;
} WORD;

typedef struct wordstats {
// your code
	int line_count;
	int word_count;
	int keyword_count;
} WORDSTATS;

int create_dictionary(FILE *fp, char *dictionary);

BOOLEAN contain_word(char *dictionary, char *word);

WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary);

#endif
