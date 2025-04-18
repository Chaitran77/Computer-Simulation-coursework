// #include <string.h>
// #include "utils/register_structs.h"

void not_printf(char* buf, size_t len) {
	for (size_t i = 0; i < len; i++) {
		switch (buf[i]) {
			case '\0': {
				printf("\\0");
				break;
			}
			case '\n': {
				printf("\\n");
				break;
			}
			case '\t': {
				printf("\\t");
				break;
			}
			case '\r': {
				printf("\\r");
				break;
			}
			default: {
				fputc(buf[i], stdout);
				break;
			}
		}
	}
}


void parse_tokens(instructionEncapuslator *instPointer, char token_list[5][11]) {

    printf("\n\n TOKEN PARSER \n\n");

    // The opcode will always be the first token
    strcpy(instPointer->opcode, token_list[0]);


    printf("\n");
    not_printf(token_list[1], 10);
    printf("\n");

    if (strcmp(instPointer->opcode, "J") == 0) {
        printf("\nJUMP LINE NUMBER: %d\n", atoi(token_list[1]));
        instPointer->immediate = strtol(token_list[1], NULL, 10);
        printf("JUMP %d\n", instPointer->immediate);
    }


    // LABEL, check if final character of token is ':'
    // printf("FINAL CHARACTER: %c\n", &token_list[0][strlen(&token_list[0])-1]);
    // if (token_list[0][strlen(*token_list[0])-1] == ':') {
    //     printf("LABEL %s", token_list[0]);
    // }

    printf("OPCODE: "); 
    not_printf(instPointer->opcode, 11);
    printf("\n");
}


instructionEncapuslator parse_line(char line[150]) {
    printf("LINE TO PARSE:\n");
    not_printf(line, 50);
    printf("\n");

    instructionEncapuslator parsed_instruction = {.opcode="NONE", .rd=15, .rs=16, .rt=17};
    
    
    int i = 0;
    int token_number = 0;
    int token_char_i = 0;
    
    char tokens[5][11] = {"\0\0\0\0\0\0\0\0\0\0\0"};
    char* token_pointers[5];


    // line ends at first null character
    while (line[i] != '\0') {
        if ((line[i] != ' ') && (line[i] != ',')) {
            if (token_char_i < 10) {
                tokens[token_number][token_char_i] = line[i];
                token_char_i++;
            }
        } else if (token_char_i > 0) {
            tokens[token_number][token_char_i] = '\0';
            token_pointers[token_number] = tokens[token_number];
            
            token_number++;
            token_char_i = 0;

            if (token_number >= 5) break;
            
        }

        i++;
    }

    if (token_char_i > 0 && token_number < 5) {
        tokens[token_number][token_char_i] = '\0';
        token_pointers[token_number] = tokens[token_number];
    }
    
    parse_tokens(&parsed_instruction, tokens);
    return parsed_instruction;
}


void santise(char * destination, char fileLine[150]) {

    for (int i=0; fileLine[i] != '\0'; i++) {
        if ((fileLine[i] == '\n') || (fileLine[i] == '#')) break;
        destination[i] = fileLine[i];
    }
    
}
