#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "preprocessor.h"
#include "symbolTable.h"

FILE* fa;
int SYMBOL_TABLE_SIZE = 1024;
int TOKEN_TABLE_SIZE = 1024;

void main(){

    fa = fopen("./sample.c", "r");
    int row = 0;
    int col = 0;
    char c;
    
    if (fa == NULL){
        printf("Cannot open file \n");
        return;
    }

    printf("\n----------------\n Getting the raw text \n--------\n");

    c = fgetc(fa);
    char text[4096];


    int i = 0;

    while (c != EOF){
        text[i] = c;
        i++;
        c = fgetc(fa);
    }


    text[i] = '\0';

    printf("%s \n----------\n Passing it through the pre-processor\n----------\n",text);

    runPreprocessor(text);

    printf("%s \n--------\n is the code to be passed through the lexical analyzer \n---------\n", text);

    Token* alltokens[TOKEN_TABLE_SIZE];
    for (int i = 0; i < TOKEN_TABLE_SIZE; i++){
        alltokens[i] = createToken("EOF", -1, -1, TOK_EOF);
    } 

    getTokens(text, alltokens);

    for (int i = 0;  i < TOKEN_TABLE_SIZE; i++){
        if (alltokens[i]->type == 2 ){
            break;
        }else{
            printToken(alltokens[i]);
        }
    }

    printf("\n------\n are the tokens needed for symbol table \n-------\n");

    Symbol* symTable[SYMBOL_TABLE_SIZE];
    initializeSymbolTable(symTable);
    getSymbolTableFromTokens(symTable, alltokens);

    for (int i = 0;  i < TOKEN_TABLE_SIZE; i++){
        if (symTable[i]->size == 0 ){
            break;
        }else{
            printSymbol(symTable[i]);
            printf("\n");
        }
    }

    printf("\n-----\n are the symbols received");

}

