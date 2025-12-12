#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

Token **tokenize(FILE *file);
void read(FILE *file);

#endif
