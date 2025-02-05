#include "token.h"

typedef struct Symbol{
    Token tok;
    int size;
    char scope[1024];
}Symbol;


