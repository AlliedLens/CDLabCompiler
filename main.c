#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "preprocessor.h"

FILE* fa;

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

    Token* alltokens[1024];
    for (int i = 0; i < 1024; i++){
        alltokens[i] = createToken("EOF", -1, -1, TOK_EOF);
    } 

    getTokens(text, alltokens);

    for (int i = 0;  i < 1024; i++){
        if (alltokens[i]->type == 2 ){
            break;
        }else{
            printToken(alltokens[i]);
        }
    }

    printf("\n------\n are the tokens needed for symbol table");
}