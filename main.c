#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define WORD_LENGTH 6
/* five characters and one null byte */

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
char *wrong_place_in_string_mask(char *guess, char *word, char *correct_mask) {
    /* TODO: check if letter was previously mapped */
    /* TODO: make is so if a letter repeats more than twice
       the code doesn't break */

    char *res = calloc(WORD_LENGTH, sizeof (char));
    char *word_cpy = calloc(WORD_LENGTH, sizeof (char));
    int guess_index, word_index;
    strcpy(word_cpy, word); /* make a copy of word into word_cpy */

    errase_mask(word_cpy, correct_mask, word);


    for (guess_index=0; guess_index<WORD_LENGTH; guess_index++) {
        for (word_index=0; word_index<WORD_LENGTH; word_index++) {
            if (guess[guess_index] == word_cpy[word_index]) { /* guess at index in word */
                printf("guess_index %d, word_index %d\n\n", guess_index, word_index);
                res[guess_index] = guess[guess_index];
                word_cpy[word_index] = '\0';
            } else res[guess_index] = '\0';
        }
    }
    return res;
}

int count_letter(char letter, char *word) {
    int res=0;
    while(word) {
        if (*word == letter) res++;
        word++;
    }
    return res;
}

/* displays the masks replacing \0 with . */
void display_word(char *word) {
    int i;
    for (i=0; i<WORD_LENGTH-1; i++)
        if (word[i] == '\0') putc('.', stdout);
        else putc(word[i], stdout);
}

void results(char *word, char *guess) {
    char *right = right_place_mask(guess, word);
    /* char *almost = wrong_place_in_string_mask(guess, word); */
    printf("the guess: %s\n", guess);
    printf("the word : %s\n", word);
    /* printf("almost   : %s\n", almost); */
    printf("matching : ");
    display_word(right);
    puts(""); /* new line */
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
    char word[WORD_LENGTH] = "hello";
    char guess[WORD_LENGTH] = "oxxxx";
    char *correct = right_place_mask(word, guess);
    char *mask = wrong_place_in_string_mask(guess, word, correct);

    display_word(mask);
    puts("");

    /* char *is_null = word_index;
    while (1) {
        fputs("> ", stdout);
        is_null = fgets(guess, WORD_LENGTH, stdin);
        if (is_null == NULL)
            break;
        getc(stdin);
        results(word, guess);
    } */


    /* printf("> ");
    fgets(guess, WORD_LENGTH, stdin);
    printf("your guess was: ");
    puts(guess); */
}
