#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h>


void parse_ansi_code(char* ansi_input) {
    char string_of_codes[50];
    int code_counter = 0;

    for (int i = 0; ansi_input[i] != '\0'; i++) {
        if (ansi_input[i] == '\x1b' && ansi_input[i + 1] == '[') {
            printf("\n\n");

            i += 1; 
            
            string_of_codes[0] = '\0';

            while (ansi_input[i + 1] != '\0' && isalpha(ansi_input[i]) == 0 && ansi_input[i] != '\a') { 
                char temp[2] = {ansi_input[i], '\0'};
                strcat(string_of_codes, temp);
                
                if( isalpha(ansi_input[i + 1]) != 0){
                    char temp_terminate[2] = {ansi_input[i + 1], '\0'};
                    strcat(string_of_codes, temp_terminate);
                }

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
                printf("Code #%d: %s\n", code_counter, code_array[j]);
                code_counter++;
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
//     char str[] = "`@�"
//     "[1m[7m%[27m[1m[0m"                                                                              
//     "�Ҩ��"
//     "]7;file://Anthonys-Air-5/Users/anthonyjarjour/Desktop/termu"                                    
//     "�Ҩ��"
//     "[0m[27m[24m[J(base) anthonyjarjour@Anthonys-Air-5 termu % [K[?2004h";                      
//     // "�Ҩ��";
//
//     printf("Given '%s', this is what is parsed: \n\n", str);
//
//     parse_ansi_code(str);
//     printf("\n");
//     
//     return 0;
// }
