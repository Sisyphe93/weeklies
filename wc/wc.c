#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>

void printBytesCount(ssize_t bytes[], char *fileName){
    for(int i = 0; i < 4; i++){
        if (bytes[i] > 0)
            printf(" %ld", bytes[i]);
    }
    printf(" %s\n", fileName);
}

int isBlank(char c){
    return c == ' ' || c == '\t' || c == '\r' || c == '\n' || !c;
}

int countCharacters(const char *str) {
    setlocale(LC_CTYPE, "");
    
    int count = 0;
    mbstate_t state = {0};
    int i = 0;
    while (str[i] != '\0') {
        wchar_t wc;
        int result = mbrtowc(&wc, &str[i], MB_CUR_MAX, &state);
        if (result > 0) {
            count++;
            i += result;
        } else if (result == 0) {
            break;
        }
    }
    return count;
}

int countWords(char *str){
    int words = 0;
    int i = 0;
    int len = strlen(str);

    while (i < len){
        if (isBlank(str[i]))
            i++;
        else break;
    }
    while(i < len){
        if (str[i]){
            if (isBlank(str[i - 1]) && !isBlank(str[i])){
                words++;
            }
        }
        i++;
    }

    return words;
}

int flags(char* str, char c, ssize_t bytes[]){
    if (c == 'c' ){
        bytes[3] += strlen(str);
    }else if(c == 'l'){
        bytes[2] += 1;
    }else if (c == 'w')
        bytes[1] += countWords(str);
    else if (c == 'm')
        bytes[0] += countCharacters(str);
    else{
        bytes[3] += strlen(str);
        bytes[1] += 1;
        bytes[2] += countWords(str);
    }
}

void readFileAndFlag(char* fileName, char c){

    if (fileName == NULL){
        printf("file name not specified");
        return ;
    }

    FILE* fptr = fopen(fileName, "r");
    char *line;
    ssize_t read;
    size_t len = 0;
    ssize_t bytes[] = {0,0,0,0};
    if (fptr == NULL){
        printf("Failed to open file");
        return ;
    }

    while((read = getline(&line, &len, fptr)) != -1){
        flags(line, c, bytes);
    }
    printBytesCount(bytes, fileName);
    fclose(fptr);
    if (line)
        free(line);
}

int main(int argc, char** argv){
    // if (argc > 2)
    //     readFileAndFlag(argv[2], argv[1][1]);
    // else if (argc == 2){
    //     readFileAndFlag(argv[1], '\0');
    // }
    char str[10000];
    scanf("%s", str);
    printf("%s\n", str);
    return 0;
}