#include<stdio.h>
#include<stdlib.h>

#define WORD_LENGTH 6
/* five characters and one null byte */

/* returns an array ofwhat characters are the same in
   both strings difirent characters are reprezented
   by null in the result array */
char* right_place_mask(char* guess, char* word) {
    char* res = malloc(WORD_LENGTH);
    int i;
    for (i=0; i<WORD_LENGTH; i++)
        if (guess[i] == word[i]) res[i] = word[i];
        else res[i] = '\0';
    res[WORD_LENGTH-1] = '\0';
    return res;
}

char* wrong_place_in_string_mask(char* guess, char* word) {
    /* TODO: not let multiple letters map to the same letter */
    char* res = malloc(WORD_LENGTH);
    int i, j;
    for(i=0; i<WORD_LENGTH; i++) {
        for (j=0; j<WORD_LENGTH; j++) {
            if (guess[i] == word[j]) res[i] = guess[i];
            else res[i] = '\0';
        }
    }
    return res;
}

void display_word(char* word) {
    int i;
    for (i=0; i<WORD_LENGTH; i++)
        if (word[i] == '\0') putc(' ', stdout);
        else putc(word[i], stdout);
}

void results(char* word, char* guess) {
    char* right = right_place_mask(guess, word);
    char* almost = wrong_place_in_string_mask(guess, word);
    printf("the guess: %s\n", guess);
    printf("the word : %s\n", word);
    printf("matching : ");
    display_word(right);
    puts(""); /* new line */
}

void is_all_alpha(char* str) {
    while (isalpha(*str)) str++;
    if (*str == '\0') return true;
    else return false;
}

int main() {
    char word[WORD_LENGTH] = "hello";
    char guess[WORD_LENGTH];
    char *is_null = NULL;
    while (1) {
        fputs("> ", stdout);
        is_null = fgets(guess, WORD_LENGTH, stdin);
        if (is_null == NULL)
            break;
        getc(stdin);
        results(word, guess);
    }

    /* printf("> ");
    fgets(guess, WORD_LENGTH, stdin);
    printf("your guess was: ");
    puts(guess); */
}
