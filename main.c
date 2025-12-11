#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"

int main() {
    FILE *file = fopen("test.a", "r");

    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    Token **tokens = tokenize(file);

    for (int i = 0; tokens[i] != NULL; i++) {
        Token *t = tokens[i];
        if (t->type == TOKEN_INT) {
            printf("INT: %s\n", t->value);
        } else if (t->type == TOKEN_EXIT) {
            printf("KEYWORD: %s\n", t->value);
        } else if (t->type == TOKEN_SEMI) {
            printf("SEMI: %s\n", t->value);
        } else {
            printf("TOKEN: %s\n", t->value);
        }  
        free(t->value);
        free(t);
    }

    free(tokens);
    fclose(file);
    return 0;
}