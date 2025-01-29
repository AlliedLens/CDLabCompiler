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
    int row;
    int col;
    TokTypes type;
}Token;

Token initToken(){
    Token t;
    t.token_name[0] = '\0';
    t.index = -1;
    t.row = -1;
    t.col = -1;
    t.type = TOK_EOF;
    return t;
}

void createToken(Token* t, const char* name, int index, int row, int col, TokTypes type) {

    if (t != NULL) {
        strcpy(t->token_name, name);
        t->token_name[sizeof(t->token_name) - 1] = '\0'; 
        t->index = index;
        t->row = row;
        t->col = col;
        t->type = type;
    }else{
        printf("token is null\n");
    }

}

void printToken(Token* t){
    if (t != NULL) {
        printf("Token Info:\n");
        printf("Name: %s\n", t->token_name);
        printf("Index: %d\n", t->index);
        printf("Row: %d\n", t->row);
        printf("Col: %d\n", t->col);
        printf("Type: %d\n", t->type);
    }else{
        printf("token is null\n");
    }
}

Token* getTokenFromText(int index, int* col, int* row, char* c){
    char buff[1024];
    *c = fgetc(fa);
    Token* t = (Token*)malloc(sizeof(Token));

    if (fa == NULL){
        printf("file not accessed \n");
        exit(0);
    }


    while (*c==' ' || *c == '\t'){
        *col = *col + 1;
        *c = fgetc(fa);
    }   

    while (*c=='\n'){
        *col = 0;
        *row = *row + 1;
        *c = fgetc(fa);
    }


    

    if (*c == EOF){
        t->type = TOK_EOF;
        createToken(t, "EOF", index, *row, *col, t->type);
        printToken(t);
        return t;
    }

    createToken(t, "INVALID", index, *row, *col, INVALID);
    printToken(t);

    return t;

    // createToken(t, )
    
}