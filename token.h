#include "utils.h"

extern FILE* fa;


typedef enum TokTypes{
    INVALID = -1,
    TOK_EOF = 2,
    
    IDENTIFIER = 3,
    NUMBER = 4,
    
    KEYWORD = 5,
    
    RELOP = 6,
    ARITHOP = 7,
    LOGICALOP = 8,
    ASSIGNOP = 9,
    
    PUNCTUATION = 10,
} TokTypes;

typedef struct Token{
    char token_name [1024];
    int index;
    int pos;
    TokTypes type;
}Token;

// Token initToken(){
//     Token t;
//     t.token_name[0] = '\0';
//     t.index = -1;
//     t.row = -1;
//     t.col = -1;
//     t.type = TOK_EOF;
//     return t;
// }

Token* createToken(const char* name, int index, int pos, TokTypes type) {
    Token* t = (Token*)malloc(sizeof(Token));

    strcpy(t->token_name, name);
    t->token_name[sizeof(t->token_name) - 1] = '\0'; 
    t->index = index;
    t->pos = pos;
    t->type = type;

    return t;
}

void printToken(Token* t){
    if (t != NULL) {
        printf("Token Info:\n");
        printf("Name: %s\n", t->token_name);
        printf("Index: %d\n", t->index);
        printf("pos: %d\n", t->pos);
        printf("Type: %d\n", t->type);
    }else{
        printf("token is null\n");
    }
}

void getTokens(char* input, Token* allTokens[1024]){
    int pos = 0;

    int left = 0;
    int right = 0;

    int len = strlen(input);

    int i = 0;
    char buff[1024];
    Token* t;

    while (right <= len && left <= len){
        
        if (!isDelimiter(input[right])){
            right++;
        }

        if (isDelimiter(input[right]) && left == right){
            if (isOperator(input[right])){
                pos = left;
                buff[0] = input[right];
                buff[1] = '\0';
                allTokens[i] = createToken(buff, i, pos, ARITHOP);
                printToken(allTokens[i]);

                right++;
                left = right;
            
            }else if (isPunctuation(input[right])){

                pos = left;
                buff[0] = input[right];
                buff[1] = '\0';
                allTokens[i] = createToken(buff, i, pos, PUNCTUATION);
                printToken(allTokens[i]);

                right++;
                left = right;

            }

        }
    }
}

// Token* getTokenFromText(int index, int* col, int* row, char* c){
//     char buff[1024];
//     *c = fgetc(fa);
//     Token* t = (Token*)malloc(sizeof(Token));

//     if (fa == NULL){
//         printf("file not accessed \n");
//         exit(0);
//     }


//     while (*c==' ' || *c == '\t'){
//         *col = *col + 1;
//         *c = fgetc(fa);
//     }   

//     while (*c=='\n'){
//         *col = 0;
//         *row = *row + 1;
//         *c = fgetc(fa);
//     }


    

//     if (*c == EOF){
//         t->type = TOK_EOF;
//         createToken(t, "EOF", index, *row, *col, t->type);
//         printToken(t);
//         return t;
//     }

//     createToken(t, "INVALID", index, *row, *col, INVALID);
//     printToken(t);

//     return t;

// }
