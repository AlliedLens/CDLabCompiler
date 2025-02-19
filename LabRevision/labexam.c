#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <stdbool.h>
#include "preprocessor.h"

typedef enum TokTypes {
    TOK_EOF = 0,
    OPCODE = 1,
    REG = 2,
    CONST = 3,
    LITERAL = 4,
    LABELS = 5
} TokTypes;

typedef struct Token {
    char tokenName[1024];
    int index;
    int position;
    TokTypes type;
} Token;

typedef struct Symbol{
    Token* tok;
    int size;
    char type[128];
}Symbol;


Token* createToken(char* name, int index, int position, TokTypes type) {
    Token* t = (Token*)malloc(sizeof(Token));    
    strncpy(t->tokenName, name, sizeof(t->tokenName) - 1);
    t->tokenName[sizeof(t->tokenName) - 1] = '\0'; 
    t->index = index;
    t->position = position;
    t->type = type;
    
    return t;
}

char* TokStringMap(Token* t){
    char* m[6] = {
        "xxx",
        "opcode",
        "reg",
        "const",

        "literal",
        "labels",

    };

    return m[t->type];
}

void printToken(Token* t) {
    if (!t) return;
    printf("Name: %s, Index: %d, Position: %d, Type: %s\n", t->tokenName, t->index, t->position, TokStringMap(t) );
}

void createSymbol(Symbol* symbol, Token* tok, int size, const char* type) {
    symbol->tok = tok;  
    symbol->size = size;
    strncpy(symbol->type, type, sizeof(symbol->type) - 1);
    symbol->type[sizeof(symbol->type) - 1] = '\0';
}

void printSymbol(Token* t) {
    if (!t) return;
    printf("Name: %s, Position: %d, Type: %s\n", t->tokenName,  t->position,TokStringMap(t));
}

bool isOpcode(char* rawToken) {
    char* OPCODES[6] = {"MOVLW", "MOVWF", "ADDWF","SUBWF", "CALL", "GOTO" };

    for (int i = 0; i < 6; i++) {
        if (strcmp(rawToken, OPCODES[i]) == 0) return 1;
    }
    return 0;
}

bool isReg(char* rawToken) {
    char* REGISTERS[4] = {"WREG", "STATUS","PORTB", "RISB"};

    for (int i = 0; i < 4; i++) {
        if (strcmp(rawToken, REGISTERS[i]) == 0) return 1;
    }
    return 0;
}

TokTypes checkType(char* rawToken) {
    if (isOpcode(rawToken)) return OPCODE;
    if (isReg(rawToken)) return REG;
    if (strstr(rawToken, ":") != NULL) return LABELS;
    if (strstr(rawToken, "0x") != NULL) return CONST;
    return LITERAL;
}

int main() {
    char c = '\0';      
    FILE* fp = fopen("examsample.txt", "r");

    char txt[2048];
    int i = 0;

    while ( c != EOF){
        c = fgetc(fp);
        txt[i] = c;
        i++;
    }

    runPreprocessor(txt); 
    printf("preprocesesd text is %s \n", txt);

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

    printf("\n----------------\n");
    printf("tokens are \n");

    // put tokens in their categories
    Token* tokens[1024];

    for (int i = 0; i < tokenCount; i++) {
        TokTypes type = checkType(rawTokens[i]);
        tokens[i] = createToken(rawTokens[i], i, positions[i], type);
        printToken(tokens[i]);
    }

    printf("\n--------------\n");
    printf("symbols are \n");

    // get symbols from tokens
    Symbol* table[1024];

    i = 0;
    int symbolCount = 0;

    for (int i = 0; i < 1024; i++){
        table[i] = (Symbol*)malloc(sizeof(Symbol));
        strcpy(table[i]->type, "NULL");
    }

    while ( i < tokenCount){
        if (tokens[i]->type == REG || tokens[i]->type == LABELS){
            printSymbol(tokens[i]);
            symbolCount++;
        }
        i++;
    }

    return 0;
}
