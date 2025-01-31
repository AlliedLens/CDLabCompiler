#include "utils.h"


typedef enum TokTypes{
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

char* TokStringMap(Token* t){
    char* m[11] = {
        "xxx",
        "xxx",
        "eof",
        "id",

        "num",
        "key",
        
        "relop",
        "arithop",
        "logicalop",
        "assignop",
        
        "punct",
    };

    return m[t->type];
}

void printToken(Token* t){
    if (t != NULL) {
        printf("<'%s',", t->token_name);
        printf("%d,", t->index);
        printf("x %d,", t->pos);
        printf(" %s", TokStringMap(t));
        printf("> ; ");
    }else{
        printf("token is null");
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
                }else if ( isKeyword(buff) ){
                    allTokens[i] = createToken(buff, i, pos, KEYWORD); 
                }else{
                    allTokens[i] = createToken(buff, i, pos, IDENTIFIER);
                }
                i++;
                left = right;
            }

            // Handle delimiter (single operator/punctuation)
            if (isDelimiter(input[right])) {

                if (isArithmeticOperator(input[right])) {
                    buff[0] = input[right];
                    buff[1] = '\0';
                    pos = right;
                    allTokens[i] = createToken(buff, i, pos, ARITHOP);
                    i++;
                }else if (isOperator(input[right])) {
                    buff[0] = input[right];
                    buff[1] = '\0';
                    pos = right;
                    allTokens[i] = createToken(buff, i, pos, RELOP);
                    i++;
                } 
                else if (isPunctuation(input[right])) {
                    buff[0] = input[right];
                    buff[1] = '\0';
                    pos = right;
                    allTokens[i] = createToken(buff, i, pos, PUNCTUATION);
                    i++;
                }
                right++;
                left = right;
            }
        }    
    }
}