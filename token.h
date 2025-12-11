#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_EXIT,
    TOKEN_INT,
    TOKEN_SEMI,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_EOF 
} TokenType;

typedef struct {
    TokenType type;
    char *value; 
} Token;

#endif