#ifndef NODE_H
#define NODE_H

#include "token.h"

typedef struct {
    Token *int_token;
} NodeExpr;

typedef struct {
    NodeExpr *expr;
}NodeExit;

typedef struct {
    Token *identifier;
    NodeExpr *expr;
}NodeVarDecl;


#endif