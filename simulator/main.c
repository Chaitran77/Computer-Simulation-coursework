#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// #define strTest

// pipeline stage registers


// register file

struct registers {
    // short = 2 bytes = 16 bits
    unsigned short r0; // cannot initialise this to 0 
    unsigned short r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31;
};


// register translator ($t4 => 12), was going to map enums to numbers with a LUT but that's tedious 
int register_translator(char register_name[5]) {
    int register_number = -1;

    if (strncmp(register_name+1, "zero", 4) == 0) return 0;
    if (strncmp(register_name+1, "at", 2) == 0) return 1;
    if (strncmp(register_name+1, "gp", 2) == 0) return 28;
    if (strncmp(register_name+1, "sp", 2) == 0) return 29;
    if (strncmp(register_name+1, "fp", 2) == 0) return 30;
    if (strncmp(register_name+1, "ra", 2) == 0) return 31;
    
    {
        int register_name_num = register_name[2] - '0';

        // if (register_name_num < 0 || register_name_num > 31) {
        //     printf("ERROR: Invalid register address (OOB)");
        //     exit(-1);
        // }


        switch (register_name[1]) {
            
            case 'v':
                // values for expression results and expression evaluation

                if (register_name_num == 0 || register_name_num == 1) {
                    register_number = register_name_num + 2;
                }
                    
                break;
            case 'a':
                // values for expression results and expression evaluation

                if (register_name_num >= 0 && register_name_num <= 3) {
                    register_number = register_name_num + 4;
                }
                    
                break;
            case 't':
                // the temporaries
    
                if (register_name_num <= 7) {
                    register_number = register_name_num + 8;
                } else if ((register_name_num == 8) || (register_name_num == 9)) {
                    register_number = register_name_num + 16;
                }
                
                break;

            case 's':
                // the saved temporaries

                if (register_name_num >= 0 && register_name_num <= 7) {
                    register_number = register_name_num + 16;
                }
                    
                break;

            case 'k':
                // reserved

                if (register_name_num == 0 || register_name_num == 1) {
                    register_number = register_name_num + 26;
                }
                    
                break;
            
            // no default case because a valid case could be triggered with an OOB register_name_num which req. the same result
        }

        if (register_number>=0) return register_number;
        printf("ERROR: Invalid register address");
        exit(-1);
        
    }
    

    

}


struct registers REGISTER_FILE = {.r0 = 0};

int main(int argc, char **argv) {

    // FILE *program_file = fopen(argv[1], "r"); 

    #ifndef strTest

    char reg_name[5] = "$t4";
    int reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$zero");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$at");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$v0");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$v1");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$a0");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$a2");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$a3");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$t0");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$t7");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$t9");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$s7");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$k1");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$gp");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$sp");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$fp");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$ra");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    #else

    char reg_name[5] = "$zero";
    strcpy(reg_name, "$at");

    printf("%s", reg_name);
    printf("%d", register_translator(reg_name));
    
    // if (strncmp(reg_name+1, "at", 2) == 0) {
    //     printf("yesy");
    // }

    #endif

    return 0;
}