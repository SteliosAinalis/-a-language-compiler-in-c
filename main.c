#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

int main() {
    FILE *file = fopen("test.a", "r");
    if (file == NULL) return 1;

    Token **tokens = tokenize(file);

    Parser *parser = parser_init(tokens);
    NodeExit *root = parser_parse(parser);

    if (root != NULL) {
        printf("Parsed successfully!\n");
        printf("Exit code: %s\n", root->expr->int_token->value);
    }

    free(tokens);
    fclose(file);
    return 0;
}