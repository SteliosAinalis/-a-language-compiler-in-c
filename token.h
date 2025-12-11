#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_EXIT,
    TOKEN_INT,
    TOKEN_SEMI,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_IDENTIFIER,
    TOKEN_EQUALS,
    TOKEN_INT_LITERAL,
    TOKEN_EOF 
} TokenType;

typedef struct {
    TokenType type;
    char *value; 
} Token;

#endif