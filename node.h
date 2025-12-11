#ifndef NODE_H
#define NODE_H

#include "token.h"

typedef struct {
    Token *int_token_literal; 
    Token *identifier;      
} NodeExpr;

typedef struct {
    NodeExpr *expr;
} NodeExit;


typedef struct {
    Token *identifier; 
    NodeExpr *expr;    
} NodeVarDecl;

typedef enum {
    NODE_STMT_EXIT,
    NODE_STMT_VAR_DECL
} NodeStmtType;

typedef struct {
    NodeStmtType type;
    union {
        NodeExit *exit;
        NodeVarDecl *var_decl;
    } data;
} NodeStmt;

#endif