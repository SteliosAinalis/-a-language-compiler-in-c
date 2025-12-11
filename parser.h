#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "node.h"

typedef struct {
    Token **tokens; 
    int index;      
} Parser;


Parser *parser_init(Token **tokens);

NodeExit *parser_parse(Parser *parser);

#endif