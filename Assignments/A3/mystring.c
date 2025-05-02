/*
 --------------------------------------------------
 Project: a3q1
 File:    mystring.c
 Author:  Eric Luo, 169060595, luox0595@mylaurier.ca
 Version: 2025-01-31
 --------------------------------------------------
 */

/**
 * Count the number words of given simple string. A word starts with an English charactor end with a charactor of space, tab, comma, or period.
 *
 * @param s - char pointer to a string
 * @return - return the number of words.
 */
int str_words(char *s) {
	char *c = s;
	int count = 0;
	int a = 1;
	while (*c) {
		if ((*c >= 'A' && *c <= 'Z') || (*c >= 'a' && *c <= 'z')) {
			if (a) {
				a = 0;
				count++;

			}
		} else if (*c == ' ' || *c == ',' || *c == '.') {
			a = 1;
		}

		c++;
	}
	return count;
}

/**
 * Change every upper case English letter to its lower case of string passed by s
 *
 * @param s - char pointer to a string
 * @return - return the number of actual flips.
 */
int str_lower(char *s) {

	int flips = 0;
	while (*s) {
		if (*s >= 'A' && *s <= 'Z') {
			*s = *s + 32;
			flips++;
		}
		s++;
	}

	return flips;
}

/**
 * Remove unnecessary space characters in a simple string passed by `s`
 *
 * @param s - char pointer to a string
 */
void str_trim(char *s) {
	char *c = s;
	char *dc = s;
	while (*c) {
		if (*c != ' ' || (c > s && *(c - 1) != ' ')) {
			*dc = *c;
			dc++;
		}
		c++;

	}
	if (dc > s && *(dc - 1) == ' ') {
		*(dc - 1) = '\0'; // Remove trailing space
	} else {
		*dc = '\0'; // Null terminate string
	}
}
