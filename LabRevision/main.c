#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <stdbool.h>


typedef enum TokTypes {
    TOK_EOF = 2,
    IDENTIFIER = 3,
    NUMBER = 4,
    KEYWORD = 5,
    RELOP = 6,
    ARITHOP = 7,
    LOGICALOP = 8,
    ASSIGNOP = 9,
    STRING_LITERAL = 10
} TokTypes;

typedef struct Token {
    char tokenName[1024];
    int index;
    int position;
    TokTypes type;
} Token;


Token* createToken(char* name, int index, int position, TokTypes type) {
    Token* t = (Token*)malloc(sizeof(Token));    
    strncpy(t->tokenName, name, sizeof(t->tokenName) - 1);
    t->tokenName[sizeof(t->tokenName) - 1] = '\0'; 
    t->index = index;
    t->position = position;
    t->type = type;
    
    return t;
}

void printToken(Token* t) {
    if (!t) return;
    printf("Name: %s, Index: %d, Position: %d, Type: %d\n", t->tokenName, t->index, t->position, t->type);
}

bool isKeyword(char* rawToken) {
    char* KEYWORDS[3] = {"int", "if","return" };

    for (int i = 0; i < 3; i++) {
        if (strcmp(rawToken, KEYWORDS[i]) == 0) return 1;
    }
    return 0;
}

bool isArithmeticOperator(char* rawToken){
    return(
        strcmp(rawToken, "+") == 0 ||
        strcmp(rawToken, "-")  == 0 ||
        strcmp(rawToken, "*")  == 0
    ); 
}


TokTypes checkType(char* rawToken) {
    if (isKeyword(rawToken)) return KEYWORD;
    if (isArithmeticOperator(rawToken)) return ARITHOP;

    // if (isdigit(rawToken)) return NUMBER;
    return IDENTIFIER;
}

int main() {
    char c = '\0';      
    FILE* fp = fopen("sample.c", "r");

    char txt[2048];
    int i = 0;

    while ( c != EOF){
        c = fgetc(fp);
        txt[i] = c;
        i++;
    }

    // splitting text into uncategorized tokens
    char* delimiters = " ,;#{}()\n\t"; 
    char* rawToken = strtok(txt, delimiters);
    char* rawTokens[1024];
    int positions[1024];
    int tokenCount = 0;

    while (rawToken != NULL) {
        rawTokens[tokenCount] = rawToken;
        positions[tokenCount] = rawToken - txt;  
        rawToken = strtok(NULL, delimiters);
        tokenCount++;
    }

    // put tokens in their categories
    Token* tokens[1024];

    for (int i = 0; i < tokenCount; i++) {
        TokTypes type = checkType(rawTokens[i]);
        tokens[i] = createToken(rawTokens[i], i, positions[i], type);
        printToken(tokens[i]);
    }

    return 0;
}
