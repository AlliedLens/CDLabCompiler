#include "token.h"
#include "string.h"

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

extern int SYMBOL_TABLE_SIZE;
extern int TOKEN_TABLE_SIZE;

typedef struct Symbol{
    Token* tok;
    int size;
    char type[128];
}Symbol;

void initializeSymbol(Symbol* symbol, Token* tok, int size, const char* type) {
    symbol->tok = tok;  
    symbol->size = size;
    strncpy(symbol->type, type, sizeof(symbol->type) - 1);
    symbol->type[sizeof(symbol->type) - 1] = '\0';
}

void printSymbol(const Symbol* symbol) {
    printf(" { ");
    printToken(symbol->tok);
    printf(" Size: %d, Type: %s }", symbol->size, symbol->type);
}

void initializeSymbolTable(Symbol* table[SYMBOL_TABLE_SIZE]){
    for (int i = 0; i < SYMBOL_TABLE_SIZE;i++){
        table[i] = (Symbol*)malloc(sizeof(Symbol));
        strcpy(table[i]->type, "NULL");
    }
}

void getSymbolTableFromTokens(Symbol* table[SYMBOL_TABLE_SIZE], Token* alltokens[TOKEN_TABLE_SIZE]){
    int i = 0;
    int r = 0;

    while (i < TOKEN_TABLE_SIZE){
        if (alltokens[i]->type == KEYWORD){ 
            i++;
            if (alltokens[i]->type == IDENTIFIER){ // I.E if it is a variable
                initializeSymbol(table[r], alltokens[i], 8, alltokens[i-1]->token_name);     
                // printSymbol(table[r]);
                r++;
            }
        }
        
        i++;
    }
}

#endif