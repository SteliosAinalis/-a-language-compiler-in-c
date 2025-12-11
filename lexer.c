#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Token *init_token(TokenType type, char *value) {
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    return token;
}


char *str_copy(const char *src) {
    int length = strlen(src);
    char *dest = malloc(length + 1); 
    strcpy(dest, src);
    return dest;
}

Token *read_number(char current, FILE *file) {
    char *value = malloc(sizeof(char) * 20);
    int value_index = 0;

    while (isdigit(current) && current != EOF) {
        value[value_index++] = current;
        current = fgetc(file);
    }
    value[value_index] = '\0';
    ungetc(current, file); 
    return init_token(TOKEN_INT_LITERAL, value);
}

Token *read_identifier(char current, FILE *file) {
    char *value = malloc(sizeof(char) * 20);
    int value_index = 0;

    while (isalnum(current) || current == '_') {
        value[value_index++] = current;
        current = fgetc(file);
    }
    value[value_index] = '\0';
    ungetc(current, file);

    if (strcmp(value, "exit") == 0) {
        return init_token(TOKEN_EXIT, value);
    }
    else if (strcmp(value, "int") == 0) {
        return init_token(TOKEN_INT, value);
    }
    return init_token(TOKEN_IDENTIFIER, value); 
}

Token **tokenize(FILE *file) {
    int capacity = 2;
    int size = 0;
    Token **tokens = malloc(sizeof(Token*) * capacity);
    char current = fgetc(file);

    while (current != EOF) {
        if (current == ' ' || current == '\n' || current == '\t') {
            current = fgetc(file);
            continue;
        }
        Token *found_token = NULL;
        if (isdigit(current)) {
            found_token = read_number(current, file);
        } 
        else if (isalpha(current)) {
            found_token = read_identifier(current, file);
        } 
        else if (current == '(') {
            found_token = init_token(TOKEN_OPEN_PAREN, str_copy("("));
        }
        else if (current == ')') {
            found_token = init_token(TOKEN_CLOSE_PAREN, str_copy(")"));
        }
        else if (current == '=') { 
            found_token = init_token(TOKEN_EQUALS, str_copy("="));
        }
        else if (current == ';') {
            found_token = init_token(TOKEN_SEMI, str_copy(";"));
        }

        if (found_token != NULL) {
            tokens[size] = found_token;
            size++;
            if (size >= capacity) {
                capacity *= 2;
                tokens = realloc(tokens, sizeof(Token*) * capacity);
            }
        }

        current = fgetc(file);
    }
    tokens[size] = init_token(TOKEN_EOF, "");
        size++;
    if (size >= capacity) {
        tokens = realloc(tokens, sizeof(Token*) * capacity);
    }
    tokens[size-1] = NULL; 

    return tokens;
}