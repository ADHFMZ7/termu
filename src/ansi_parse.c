#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void parseAnsiCode(char* ansiInput) {
    int len = strlen(ansiInput);
    char stringOfCodes[50];

    for (int i = 0; i < len; i++) {
        if (ansiInput[i] == '\x1b' && ansiInput[i + 1] == '[') {
            printf("\n\n");

            i += 2; 
            stringOfCodes[0] = '\0';

            while (ansiInput[i] != 'm') { 
                char temp[2] = {ansiInput[i], '\0'};
                strcat(stringOfCodes, temp);
                i++;
            }

            char *delimter = strtok(stringOfCodes, ";");
            char **codeArray = NULL;
            int j = 0, size = 0;

            while (delimter != NULL){
                codeArray = (char **)realloc(codeArray, (size + 1) * sizeof(char *));
                codeArray[j++] = delimter;
                size++;
                delimter = strtok(NULL, ";");
            }

            for (j = 0; j < size; ++j){ 
                printf("Code #%d: %s\n", j + 1, codeArray[j]);
            }

            printf("\n");
            free(codeArray);
        }

        else {
            printf("%c", ansiInput[i]); 
        }
        
    }
}

int main() {
    char str[] = "Hello\x1b[1;31mworld\x1b[0m!";

    printf("Given '%s', this is what is parsed: \n\n", str);

    parseAnsiCode(str);
    printf("\n");
    
    return 0;
}
