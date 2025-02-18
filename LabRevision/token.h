typedef struct Token{
    char tokenName[1024];
    int index;
    unsigned int row, col;
    char type[1024];
}Token;
