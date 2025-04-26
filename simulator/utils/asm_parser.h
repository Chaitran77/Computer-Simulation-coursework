// #include <string.h>
// #include "utils/register_structs.h"


void parse_tokens(instructionEncapuslator *instPointer, char token_list[5][11]) {

    
    // The opcode will always be the first token
    strcpy(instPointer->opcode, token_list[0]);
    
    
    #ifdef TEST
        printf("\n\nTOKEN PARSER <== \n");
        not_printf(token_list[1], 10);
        printf("\n");
    #endif

    if (strcmp(instPointer->opcode, "J") == 0) {
        instPointer->type = J;
        instPointer->address = strtol(token_list[1], NULL, 10);
    }
    
    if ((strcmp(instPointer->opcode, "ADD") == 0) || (strcmp(instPointer->opcode, "SLT") == 0)) {
        instPointer->type = R;
        instPointer->rs = register_translator(token_list[2]);
        instPointer->rt = register_translator(token_list[3]);
        instPointer->rd = register_translator(token_list[1]);

        if (strcmp(instPointer->opcode, "ADD") == 0) {
            instPointer->funct = 0;
        } else if (strcmp(instPointer->opcode, "SLT") == 0) {
            instPointer->funct = 1;
        }
        // instPointer->shamt will always be 0 since there are no instructions that require it
        
    }

    if ((strcmp(instPointer->opcode, "LW") == 0) || (strcmp(instPointer->opcode, "SW") == 0)|| (strcmp(instPointer->opcode, "ADDI") == 0)|| (strcmp(instPointer->opcode, "BEQ") == 0)) {
        instPointer->type = I;
        instPointer->rs = register_translator(token_list[2]);
        instPointer->rt = register_translator(token_list[1]);
        instPointer->immediate = strtol(token_list[3], NULL, 10);

        // absolute addressing is used for LW and SW and the immediate is not read (given rs register contains address)
    }



    // LABEL, check if final character of token is ':'
    // printf("FINAL CHARACTER: %c\n", &token_list[0][strlen(&token_list[0])-1]);
    // if (token_list[0][strlen(*token_list[0])-1] == ':') {
    //     printf("LABEL %s", token_list[0]);
    // }

    #ifdef TEST
        printf("OPCODE: "); 
        not_printf(instPointer->opcode, 11);
        printf("\n");
    #endif
}


instructionEncapuslator parse_line(char line[150]) {
    #ifdef TEST
        printf("LINE TO PARSE: <==\n");
        not_printf(line, 50);
        printf("\n");
    #endif

    instructionEncapuslator parsed_instruction = {.opcode="NONE", .type=-1, .rs=0, .rt=0, .rd=0, .shamt=0, .immediate=0, .address=0};
    
    
    int i = 0;
    int token_number = 0;
    int token_char_i = 0;
    
    char tokens[5][11] = {{'\0'}};
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


void santise(char * destination, char *fileLine) {

    for (int i=0; fileLine[i] != '\0'; i++) {
        if ((fileLine[i] == '\n') || (fileLine[i] == '#')) break;
        destination[i] = fileLine[i];
    }
    
}
