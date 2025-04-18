#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#include "utils/register_translator.h"
#include "utils/register_structs.h"
#include "utils/tests.h"
#include "utils/memory.h"
#include "utils/bootloader.h"


typedef enum {R, I, J} instructionType;
typedef enum {IF, ID, EX, MEM, WB} STATE;


#define ADD 0b00101001

void set_control_unit_signals(control_unit *control_unit, uint8_t opcode) {
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

// TODO: Pipeline stage registers



GPRs REGISTER_FILE = {.r0 = 0b0};
SPRs SPR_FILE = {.PC = 0b0};
control_unit CONTROL_UNIT;

// tracking variables - part of simulator
bool clock = 0;
int cycleNumber = 0;

// A new state machine struct is created every time a new instruction starts

typedef struct {
    STATE state;
} instructionState;

void ASM(instructionState *instructionState) {
    switch (instructionState -> state)
    {
    case IF:
        /* code */
        
        break;
    case ID:
        break;
    case EX:
        break;
    case MEM:
        break;
    case WB:
        break;
    default:
        break;
    }
}

int main(int argc, char **argv) {

    bootloader(argv[1]);
    
    do {
        printf("Press enter for next half cycle\n");

        clock = !clock;
        printf("Clock cycle number: %d\n", cycleNumber);

        output_IM();
        output_DM();

        if (clock) { // first half of clock cycle
            cycleNumber++;

        } else { // second half of clock cycle

        }

    } while (getchar() == '\n');


    printf("Exiting.");
    
    return 0;
}