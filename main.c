#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

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

    c = fgetc(fa);
    char text[4096];

    Token* alltokens[1024];
    int i = 0;

    while (c != EOF){
        text[i] = c;
        i++;
        c = fgetc(fa);
    }

    text[i] = '\0';

    printf("%s \n is the code to be passed through the lexical analyzer\n", text);

    getTokens(text, alltokens);
}