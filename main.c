#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
    SEMI,
    OPEN_PAREN,
    CLOSE_PAREN,
} TypeSeperator;

typedef enum {
    EXIT,
} TypeKeyword;


typedef enum {
    INT,
} TypeLiteral;

typedef struct 
{
    TypeKeyword type;
} TokenSeperator;

typedef struct 
{
    TypeKeyword type;
} TokenKeyword;

typedef struct
{
    TypeLiteral type;
    char* value;
} TokenLiteral;


TokenLiteral *read_number(char current, FILE *file){
    TokenLiteral *token = malloc(sizeof(TokenLiteral));
    token -> type = INT;
    char *value = malloc(sizeof(char) * 8);
    int value_index = 0;
    while(isdigit(current) &&  current != EOF){
        if(!isdigit(current)){
            break;
        }
        value[value_index] = (int) current;
        value_index ++;
        current = fgetc(file);
    }

    token -> value = value;
    // free(value);
    return(token);
}

TokenKeyword *read_keyword(char current, FILE *file){
    TokenKeyword *token = malloc(sizeof(TokenKeyword));
}

void read(FILE *file){
    char current = fgetc(file);
     while(current != EOF){
        if(current == '('){
            printf("OPEN PAREN FOUND\n");
        }else if(current == ')'){
            printf("CLOSE PAREN FOUND\n");
        }else if(current == ';'){
            printf("SEMICOLON FOUND\n");
        }else if(isdigit(current)){
            TokenLiteral *test_token = read_number(current, file);
            printf("TEST TOKEN VALUE: %s\n", test_token -> value);
            // printf("FOUND DIGIT: %i\n", current - '0');
        }else if (isalpha(current)){
            printf("FOUND CHARACTER: %c\n", current);

        }
        
        current = fgetc(file);        
    }
}

int main(){
    FILE *file;
    file = fopen("test.a", "r");
    read(file);
    printf("\n");


    
}

