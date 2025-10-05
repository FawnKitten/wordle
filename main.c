#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define WORD_LENGTH 6
/* five characters and one null byte */
#define COLOR_RESET "\033[0m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"

void display_word(char *word);

/* returns an array of what characters are the same in
   both strings difirent characters are represented
   by null in the result array */
char *right_place_mask(char *guess, char *word) {
    char *res = malloc(WORD_LENGTH);
    int i;
    for (i=0; i<WORD_LENGTH; i++)
        if (guess[i] == word[i]) res[i] = word[i];
        else res[i] = '\0';
    res[WORD_LENGTH-1] = '\0';
    return res;
}

char *errase_mask(char *dest, char *source_mask, char *word) {
    int i;
    for (i=0; i<WORD_LENGTH; i++) {
        if (source_mask[i] == '\0') dest[i] = word[i];
        else dest[i] = '\0';
    }
    return dest;
}

/* returns an array of what characters appear in the
   other string */
char *wrong_place_in_string_mask(char *guess, char *word) {
    char *res = calloc(WORD_LENGTH, sizeof (char));
    char *word_cpy = calloc(WORD_LENGTH, sizeof (char));
    int guess_index, word_index;
    strcpy(word_cpy, word); /* make a copy of word into word_cpy */

    for (guess_index=0; guess_index<WORD_LENGTH-1 /* exclude trailing null */; guess_index++) {
        for (word_index=0; word_index<WORD_LENGTH-1; word_index++) {
            if (guess[guess_index] == word_cpy[word_index]) {
				/* if the current letter in guess maps to another letter
				   in the word */
                res[guess_index] = guess[guess_index];
                word_cpy[word_index] = '\0';
				/* ^ this change is made so the letter won't be mapped to again */
				break;
            } else {
				res[guess_index] = '\0';
			}
        }
    }
    return res;
}

/* displays the masks replacing \0 with . */
void display_word(char *word) {
    int i;
    for (i=0; i<WORD_LENGTH-1; i++) {
        if (word[i] == '\0') putc('.', stdout);
        else putc(word[i], stdout);
	}
	puts("");
}

void results(char *word, char *guess) {
    char *right = right_place_mask(guess, word);
    char *almost = wrong_place_in_string_mask(guess, word);
    int i;

    for (i=0; i<WORD_LENGTH; i++) {
        if (right[i] != '\0') {
            printf(GREEN "%c" COLOR_RESET, right[i]);
        } else if (almost[i] != '\0') {
            printf(YELLOW "%c" COLOR_RESET, almost[i]);
        } else {
            printf("%c", guess[i]);
        }
    }
    puts("");
}

int is_all_alpha(char *str) {
    while (isalpha(*str)) str++;
    if (*str == '\0') return 1;
    else return 0;
}

int is_all_null(char *str, int size) {
    for(;size>0; size--)
        if (str[size-1] != '\0') return 0;
    return 1;
}

int main() {
    char word[WORD_LENGTH] =  "crane";
    char guess[WORD_LENGTH] = "";
    int i;
    puts("Welcome to wordle! You have 6 attempts to guess the 5-letter word.");

    for (i=0; i<6; i++) {
        fputs("> ", stdout);
        if (fgets(guess, WORD_LENGTH, stdin) == NULL)
            break;
        getc(stdin);
        if (strlen(guess) != WORD_LENGTH-1) {
            puts("Please enter a five leter word");
            continue;
        }
        results(word, guess);
        if (strcmp(word, guess) == 0) {
            puts("You win!");
            return 0;
        }
    }
    printf("You lost! The word is %s.\n", word);

    return 0;
}
