#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void parse_ansi_code(char* ansi_input) {
    char string_of_codes[50];

    for (int i = 0; ansi_input[i] != '\0'; i++) {
        if (ansi_input[i] == '\x1b' && ansi_input[i + 1] == '[') {
            printf("\n\n");

            i += 2; 
            string_of_codes[0] = '\0';

            while (ansi_input[i] != 'm') { 
                char temp[2] = {ansi_input[i], '\0'};
                strcat(string_of_codes, temp);
                i++;
            }

            char *delimter    = strtok(string_of_codes, ";");
            char **code_array = NULL;
            int j = 0, size = 0;

            while (delimter != NULL){
                code_array = (char **)realloc(code_array, (size + 1) * sizeof(char *));
                code_array[j++] = delimter;
                size++;
                delimter = strtok(NULL, ";");
            }

            for (j = 0; j < size; ++j){ 
                printf("Code #%d: %s\n", j + 1, code_array[j]);
            }

            printf("\n");
            free(code_array);
        }

        else {
            printf("%c", ansi_input[i]); 
        }
        
    }
}

// int main() {
//     char str[] = "Hello\x1b[1;31mworld\x1b[0m!";
//
//     printf("Given '%s', this is what is parsed: \n\n", str);
//
//     parse_ansi_code(str);
//     printf("\n");
//     
//     return 0;
// }
