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
    int index = 0;

    Token* alltokens[1024];

    while (c != EOF){
        
        alltokens[index] = getTokenFromText(index, &col, &row, &c);

        index++;
    }
}