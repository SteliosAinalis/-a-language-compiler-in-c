#include "generateCode.h"
#include <stdio.h>
#include <stdlib.h>

void generate_code_asm(NodeExit *root) {
    FILE *file = fopen("exit.s", "w");
    if (file == NULL) {
        printf("Error: Could not create output file.\n");
        exit(1);
    }
    fprintf(file, ".global _main\n");
    fprintf(file, ".align 2\n"); 
    
    fprintf(file, "_main:\n");

    fprintf(file, "    mov X0, #%s\n", root->expr->int_token->value);
    fprintf(file, "    mov X16, #1\n");
    fprintf(file, "    svc #0\n");

    fclose(file);
}
