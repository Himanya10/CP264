/*
 --------------------------------------------------
 Project: a3q2
 File:    myword.c
 Author:  Himanya Verma
 Version: 2025-01-31
 --------------------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include "mystring.h"
#include "myword.h"

#define MAX_LINE_LEN 1000
#define MAX_WORDS 1000


int create_dictionary(FILE *fp, char *dictionnary) {
	char line[1000];
	char delimiters[] = ".,\n\t\r";
	char *token;
	int count = 0;
	dictionnary[0] = '\0';
	while (fgets(line, 1000, fp) != NULL) {

		str_lower(line);
		str_trim(line);
		token = strtok(line, delimiters);
		while (token != NULL) {
			strcat(dictionnary, token);
			strcat(dictionnary, ",");
			count++;
			token = strtok(NULL, delimiters);
		}
	}
	return count;
}

BOOLEAN contain_word(char *dictionary, char *word) {
	BOOLEAN contain = 0;
	if (word == NULL || *word == '\0') {
		return 0;
	} else {
		char temp[20] = { 0 };
		strcat(temp, ",");
		strcat(temp, word);
		strcat(temp, ",");
		if (strstr(dictionary, temp)) {
			contain = 1;
		}
	}
	return contain;
}

WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary) {
	WORDSTATS ws = { 0 };
	char line[MAX_LINE_LEN];
	char delimiters[] = " .,\n\t\r";
	char *word_token;

	while (fgets(line, MAX_LINE_LEN, fp) != NULL) {
		ws.line_count++;

		str_lower(line);

		word_token = strtok(line, delimiters);

		while (word_token != NULL) {
			ws.word_count++;

			if (contain_word(dictionary, word_token) == 0) {
				int contain = 0;

				for (int i = 0; i < ws.keyword_count; i++) {
					if (strcmp(words[i].word, word_token) == 0) {
						words[i].count++;
						contain = 1;
						break;
					}
				}

				if (!contain) {
					strcpy(words[ws.keyword_count].word, word_token);
					words[ws.keyword_count].count = 1;
					ws.keyword_count++;
				}
			}

			word_token = strtok(NULL, delimiters);
		}
	}

	return ws;

}