#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"
#include "generateCode.h" 

void free_tokens(Token **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]->value); 
        free(tokens[i]);        
    }
    free(tokens);
}

void free_stmt(NodeStmt *stmt) {
    if (stmt == NULL) return;

    if (stmt->type == NODE_STMT_EXIT) {
        free(stmt->data.exit->expr);
        free(stmt->data.exit);
    } 
    else if (stmt->type == NODE_STMT_VAR_DECL) {        
        free(stmt->data.var_decl->expr);
        free(stmt->data.var_decl);
    }
    free(stmt);
}



int main() {
    FILE *file = fopen("test.a", "r");
    if (file == NULL) {
        printf("Error: Could not open test.a\n");
        return 1;
    }

    
    FILE *out = fopen("exit.s", "w");
    if (out == NULL) {
        printf("Error: Could not create exit.s\n");
        return 1;
    }
    
    fprintf(out, ".global _main\n");
    fprintf(out, ".align 2\n"); 
    fprintf(out, "_main:\n");
    fclose(out); 


    Token **tokens = tokenize(file);
    Parser *parser = parser_init(tokens);
    NodeStmt *stmt = parser_parse(parser);

    while (stmt != NULL) {
        generate_code_asm(stmt);
        free_stmt(stmt);
        stmt = parser_parse(parser);
    }
    printf("Compiled successfully to 'exit.s'\n");
    
    free(parser);
    free_tokens(tokens);           
    
    
    return 0;
}


