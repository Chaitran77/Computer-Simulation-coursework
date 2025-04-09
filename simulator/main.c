#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    if (strcmp(register_name+1, "zero")) { register_number = 0; } else
    if (strcmp(register_name+1, "at")) { register_number = 1; } else
    if (strcmp(register_name+1, "gp")) { register_number = 28; } else
    if (strcmp(register_name+1, "sp")) { register_number = 29; } else
    if (strcmp(register_name+1, "fp")) { register_number = 30; } else
    if (strcmp(register_name+1, "ra")) { register_number = 31; } else
    
    {
        int register_name_num = register_name[2] - '0';
        printf("%d", register_name_num);


        switch (register_name[1]) {

            case 't':
                { // the temporaries
    
                    if (register_name_num <= 7) {
                        register_number = register_name_num + 8;
                    } else if ((register_name_num == 8) || (register_name_num == 9)) {
                        register_number = register_name_num + 16;
                    }
    
                    if (register_number>=0) return register_number;
                    printf("ERROR: Invalid register address");
                    exit(-1);
                }
                break;

            case 's':
                { // the saved temporaries
    
                    
                    register_number = register_name_num + 16;
                    
    
                    if (register_number>=0) return register_number;
                    printf("ERROR: Invalid register address");
                    exit(-1);
                }
                break;
    
            default:
                break;
        }
    }
    

    

}


struct registers REGISTER_FILE = {.r0 = 0};

int main(int argc, char **argv) {

    // FILE *program_file = fopen(argv[1], "r"); 


    char reg_name[] = "$t4";
    // int reg_number = register_translator(reg_name);
    // printf("%d", reg_number);

    // reg_name[0] = "$zero";
    // reg_number = register_translator(reg_name);
    // printf("%d", reg_number);

    if (strcmp(reg_name+1, "t4") == 0) {
        printf("yesy");
    }

    return 0;
}