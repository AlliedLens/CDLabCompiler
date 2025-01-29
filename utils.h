#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *fa;

static char *identifier;
static double number;

extern char *keywords[7];

bool isDelimiter(char c) { // a delimiter is a piece of data that marks the boundary between lexemes, and can themselves be lexemes
    return (
        c == ' ' ||
        c == '\n' ||
        
        c == '+' ||
        c == '-' ||
        c == '*' ||
        c == '/' ||
        c == '%' ||

        c == ',' ||
        c == ';' ||
        
        c == '>' ||
        c == '<' ||
        c == '=' ||

        c == '(' ||
        c == ')' || 
        c == '[' ||
        c == ']' ||
        c == '{' ||
        c == '}'
    );
}


bool isOperator(char c){
    return(
        c == '+' ||
        c == '-' ||
        c == '*' ||
        c == '/' ||
        c == '>' ||
        c == '<' ||
        c == '=' ||
        c == '%'   
    );
}

bool isPunctuation(char c){
    return (

        c == ',' ||
        c == ';' ||
        c == '(' ||
        c == ')' || 
        c == '[' ||
        c == ']' ||
        c == '{' ||
        c == '}'
    ); 
}

bool isArithmeticOperator(char c){
    return(
        c == '+' ||
        c == '-' ||
        c == '*' ||
        c == '%'   
    ); 
}

// this function check for an valid identifier
bool isValidIdentifier(char* str)
{
    return (str[0] != '0' && str[0] != '1' && str[0] != '2'
            && str[0] != '3' && str[0] != '4'
            && str[0] != '5' && str[0] != '6'
            && str[0] != '7' && str[0] != '8'
            && str[0] != '9' && !isDelimiter(str[0]));
}

bool isKeyword(char* str)
{
    const char* keywords[]
        = { "auto",     "break",    "case",     "char",
            "const",    "continue", "default",  "do",
            "double",   "else",     "enum",     "extern",
            "float",    "for",      "goto",     "if",
            "int",      "long",     "register", "return",
            "short",    "signed",   "sizeof",   "static",
            "struct",   "switch",   "typedef",  "union",
            "unsigned", "void",     "volatile", "while" };
    for (int i = 0;
         i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

char* getSubstring(char* str, int start, int end)
{
    int length = strlen(str);
    int subLength = end - start + 1;
    char* subStr
        = (char*)malloc((subLength + 1) * sizeof(char));
    strncpy(subStr, str + start, subLength);
    subStr[subLength] = '\0';
    return subStr;
}

// check for an integer value
bool isInteger(char* str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }
    int i = 0;
    while (isdigit(str[i])) {
        i++;
    }
    return str[i] == '\0';
}
