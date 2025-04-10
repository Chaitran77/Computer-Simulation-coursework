#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "utils/register_translator.h"

#include "utils/tests.h"

typedef enum {R, I, J} instructionType;

#define ADD 0b00101001

void set_control_unit_signals(struct control_unit *control_unit, uint8_t opcode) {
    // UNIT: Control Unit block
    switch (opcode) {
        case 0b00000000: // R-type instruction
            // control_unit = {.RegDst=true, false, false, true, false, false, false, true, false};
            control_unit->RegDst=true;
            control_unit->ALUSrc=false;
            control_unit->MemtoReg=false;
            control_unit->RegWrite=true; 
            control_unit->MemRead=false; 
            control_unit->MemWrite=false; 
            control_unit->Branch=false; 
            control_unit->ALUOp1=true; 
            control_unit->ALUOp2=false;
            break;

        case I:

            break;

        case J:

            break;
    }
}

/* NOTE: 
Written in functional blocks where the output of one function is passed as the input to another. 
The structure will be analagous to the pipelined MIPS processor architecture.
If chained together correctly and each block is correctly implemented then the whole processor cycle will work as expected.
*/

// #define strTest

// pipeline stage registers


// register file

struct GPRs {
    // short = 2 bytes = 16 bits
    unsigned short r0; // cannot initialise this to 0 
    unsigned short r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31;
};

struct SPRs {
    uint8_t PC; // stores the current address in instruction memory
    uint16_t IR; // stores the current instruction
};

// control unit signals
struct control_unit {
    bool RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch, ALUOp1, ALUOp2;
};

struct GPRs REGISTER_FILE = {.r0 = 0};
struct control_unit CONTROL_UNIT;

bool clock = 0;
int cycleNumber = 0;

// A new state machine struct is created every time a new instruction starts

enum STATE {IF, ID, EX, MEM, WB};

struct instructionState {
    enum state;
};

void ASM(state) {
    switch (state)
    {
    case IF:
        /* code */
        break;
    
    default:
        break;
    }
}

int main(int argc, char **argv) {

    // FILE *program_file = fopen(argv[1], "r"); 
    
    do {
        printf("Press enter for next half cycle\n");

        clock = !clock;
        printf("Clock cycle number: %d\n", cycleNumber);

        if (clock) { // first half of clock cycle
            cycleNumber++;

        } else { // second half of clock cycle

        }

    } while (getchar() == '\n');


    printf("Exiting.");
    
    return 0;
}