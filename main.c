#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

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

/* returns an array of what characters appear in the
   other string */
char *wrong_place_in_string_mask(char *guess, char *word) {
    /* TODO: check if letter was previously mapped */
    /* TODO: make is so if a letter repeats more than twice
       the code doesn't break */
    char *res = calloc(WORD_LENGTH, sizeof char);
    int i, j, k, letter_count;
    for (i=0; i<WORD_LENGTH; i++) {
        for (j=0; j<WORD_LENGTH; j++) {
            if (guess[i] == word[j]) {
                for (k=0; k<WORD_LENGTH; k++) {
                    /* where I left off... trying to map
                       repeating letters of the guess
                       to the correspondin letter in the
                       word */
                    /* eg
                       hello
                         ||
                        / |
                       xlxlx */
                }
                res[i] = guess[i];
                break;
            } else res[i] = '\0';
        }
break_outer_loop:
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
    char guess[WORD_LENGTH] = "xxoox";
    char *mask = wrong_place_in_string_mask(guess, word);

    display_word(mask);
    puts("");

    /* char *is_null = NULL;
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
