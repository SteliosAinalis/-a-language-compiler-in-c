#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

Parser *parser_init(Token **tokens){
    Parser *parser = malloc(sizeof(Parser));
    parser->tokens = tokens;
    parser->index = 0;
    return parser;
}

Token *parser_get_current_token(Parser *p){
    return p->tokens[p->index];
}

Token *parser_consume_token(Parser *p){
    return p->tokens[p->index++];
}

const char* token_type_to_str(TokenType type) {
    switch (type) {
        case TOKEN_EXIT: return "exit";
        case TOKEN_INT: return "integer";
        case TOKEN_SEMI: return ";";
        case TOKEN_OPEN_PAREN: return "(";
        case TOKEN_CLOSE_PAREN: return ")";
        case TOKEN_IDENTIFIER: return "identifier";
        case TOKEN_EQUALS: return "=";
        case TOKEN_INT_LITERAL: return "integer literal";
        case TOKEN_EOF: return "EOF";
        default: return "UNKNOWN";
    }
}


void parser_consume(Parser *p, TokenType type) {
    Token *t = parser_get_current_token(p);
    
    if (t == NULL) {
        printf("Syntax Error: Unexpected end of file. Expected token type %s\n", token_type_to_str(type));
        exit(1);
    }

    if (t->type != type) {
        printf("Syntax Error: Expected '%s', but got '%s' ('%s')\n", 
               token_type_to_str(type),       
               token_type_to_str(t->type),    
               t->value);                     
        exit(1);
    }

    parser_consume_token(p); 
}




NodeExpr *parser_parse_expr(Parser *p) {
    Token *t = parser_get_current_token(p);

    if (t->type == TOKEN_INT_LITERAL) {
        NodeExpr *node_expr = calloc(1, sizeof(NodeExpr));
        node_expr->int_token_literal = parser_consume_token(p);
        return node_expr;
    } 
    else if (t->type == TOKEN_IDENTIFIER) {
        NodeExpr *node_expr = calloc(1, sizeof(NodeExpr));
        node_expr->identifier = parser_consume_token(p);
        return node_expr;
    }
    else {
        printf("Syntax Error: Expected integer or identifier, got '%s'\n", t->value);
        exit(1);
    }
}


NodeStmt *parser_parse(Parser *p) {
    Token *t = parser_get_current_token(p);

    if (t->type == TOKEN_EOF) {
        return NULL; 
    }
    if (t->type == TOKEN_EXIT) {

        //consume while checking if required grammar is given for token exit
        parser_consume_token(p);         
        parser_consume(p, TOKEN_OPEN_PAREN); 
        NodeExpr *expr = parser_parse_expr(p);
        parser_consume(p, TOKEN_CLOSE_PAREN);         
        parser_consume(p, TOKEN_SEMI); 

        NodeExit *node_exit = malloc(sizeof(NodeExit));
        node_exit->expr = expr;

        NodeStmt *stmt = malloc(sizeof(NodeStmt));
        stmt->type = NODE_STMT_EXIT;
        stmt->data.exit = node_exit;
        return stmt;

    }else if(t->type == TOKEN_INT){

        //consume while checking if required grammar is given for token int
        parser_consume_token(p);         
        Token *ident = parser_get_current_token(p);
        parser_consume(p, TOKEN_IDENTIFIER);
        
        parser_consume(p, TOKEN_EQUALS); 
        
        NodeExpr *expr = parser_parse_expr(p); 
        parser_consume(p, TOKEN_SEMI); 

        NodeVarDecl *var_node = malloc(sizeof(NodeVarDecl));
        var_node->identifier = ident;
        var_node->expr = expr;

        NodeStmt *stmt = malloc(sizeof(NodeStmt));
        stmt->type = NODE_STMT_VAR_DECL;
        stmt->data.var_decl = var_node;
        return stmt;
    }

    printf("Syntax Error: Unexpected token '%s'\n", t->value);
    exit(1);
}