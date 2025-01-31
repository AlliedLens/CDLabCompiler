#include "utils.h"


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
        printf("Name: '%s' , ", t->token_name);
        printf("Index: %d, ", t->index);
        printf("pos: %d, ", t->pos);
        printf("Type: %d, \n", t->type);
        printf("---------\n");
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
        
        if (right <= len && !isDelimiter(input[right])) {
            right++;
        
        } else {
            // Extract token if left < right (non-delimiter lexeme)
            if (left < right) {
                strncpy(buff, input + left, right - left);
                buff[right - left] = '\0';
                pos = left;

                if ( isInteger(buff) ){
                    allTokens[i] = createToken(buff, i, pos, NUMBER);
                }else{

                    allTokens[i] = createToken(buff, i, pos, IDENTIFIER); 
                }

                printToken(allTokens[i]);
                i++;
                left = right;
            }

            // Handle delimiter (single operator/punctuation)
            if (isDelimiter(input[right])) {
                if (isOperator(input[right])) {


                    buff[0] = input[right];
                    buff[1] = '\0';
                    pos = right;
                    allTokens[i] = createToken(buff, i, pos, ARITHOP);
                    printToken(allTokens[i]);
                    i++;
                } else if (isPunctuation(input[right])) {
                    buff[0] = input[right];
                    buff[1] = '\0';
                    pos = right;
                    allTokens[i] = createToken(buff, i, pos, PUNCTUATION);
                    printToken(allTokens[i]);
                    i++;
                }
                right++;
                left = right;
            }
        }    
    }
}