
void removeCommentsAndExcessWhiteSpaces(char* input){
    int l = 0;
    int r = 0;

    int index =0;
    char output[4096];

    while (r < strlen(input)){

        if (input[r] == ' '){ // remove excess whitespaces
            output[index] = ' ';
            index++;
            r++;
            while (input[r] == ' ' && r <= strlen(input)){
                r++;
            }
        }
        else if (input[r] == '/'){
            if (r+1 < strlen(input) && input[r+1] == '/'){
                // this is a single line comment
                while (input[r] != '\n' && r<= strlen(input)){
                    r++;
                }
            }
            else if (r+1 < strlen(input) && input[r+1] == '*'){
                // this is a multiline comment
                r += 2;
                while (r < strlen(input)){
                    if (input[r] == '*' && r+1 < strlen(input) && input[r+1] == '/'){
                        r+=2;
                        break;
                    }
                    r++;
                }
            }
            else{
                output[index] = input[r];
                index++;
                r++;
            }
        }
        else{
            output[index] = input[r];
            index++;
            r++;
        }
    }
    output[index++] = '\0';

    strcpy(input, output);
}

void removeDirectives(char* input){
    int index = 0;
    int r = 0;
    char output[4096];
    while (r < strlen(input)){

        if (input[r] == '#'){
            r++;
            while (input[r] != '\n'){
                r++;
            }
            r++;
        }else{
            output[index] = input[r];
            r++;
            index++;
        }
    }
    output[index++] = '\0';


    strcpy(input, output);
}

void replaceNewLines(char* input){
    int index = 0;
    int r = 0;
    char output[4096];

    while (r < strlen(input)){

        if (input[r] == '\n'){
            output[index] = ' ';
        }else{
            output[index] = input[r];
        }
        r++;
        index++;
    }
    output[index++] = '\0';


    strcpy(input, output);
}

void runPreprocessor(char* input){
    removeCommentsAndExcessWhiteSpaces(input);
    removeDirectives(input);
    replaceNewLines(input);
}