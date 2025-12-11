#include "generateCode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char name[32]; 
    int stack_offset; 
} Var;

Var variables[100];
int var_count =0;
int current_stack_size =0;

void push_var(char *name) {
    Var v;
    strcpy(v.name, name);
    v.stack_offset = current_stack_size;
    current_stack_size += 16;
    variables[var_count++] = v;
}

int get_var_offset(char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].stack_offset;
        }
    }
    printf("Error: Undefined variable '%s'\n", name);
    exit(1);
}


void generate_code_asm(NodeStmt *root) {
    FILE *file = fopen("exit.s", "a");
    if (file == NULL) exit(1);
    if (root->type == NODE_STMT_VAR_DECL) {

        NodeVarDecl *decl = root->data.var_decl;    
        char *val = decl->expr->int_token_literal->value;
        fprintf(file, "    mov x0, #%s\n", val);
        push_var(decl->identifier->value);
        fprintf(file, "    str x0, [sp, #-16]!\n");

    }else if (root->type == NODE_STMT_EXIT) {

        NodeExit *exit_node = root->data.exit;        
        if (exit_node->expr->int_token_literal != NULL) {
            fprintf(file, "    mov x0, #%s\n", exit_node->expr->int_token_literal->value);
        } 
        else if (exit_node->expr->identifier != NULL) {
            char *var_name = exit_node->expr->identifier->value;
            int offset = get_var_offset(var_name);
            int real_offset = (current_stack_size - 16) - offset;            
            fprintf(file, "    ldr x0, [sp, #%d]\n", real_offset);
        }
        fprintf(file, "    mov x16, #1\n"); 
        fprintf(file, "    svc #0\n");  
        
        
    }

    fclose(file);
}
