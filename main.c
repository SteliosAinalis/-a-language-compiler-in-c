#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "generateCode.h"

int main() {
    FILE *file = fopen("test.a", "r");
    if (file == NULL) return 1;

    Token **tokens = tokenize(file);
    Parser *parser = parser_init(tokens);
    NodeExit *root = parser_parse(parser);

    if (root != NULL) {
        generate_code_asm(root);
        printf("Compiled to 'exit.s'.\n");
    }

    free(tokens);
    fclose(file);
    return 0;
}