#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

// Returns a pointer to an array of Token pointers (Token**)
Token **tokenize(FILE *file);
void read(FILE *file);

#endif