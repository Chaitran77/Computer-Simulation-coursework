#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// #define TEST

#include "utils/global_enums.h"
#include "utils/register_translator.h"
#include "utils/register_structs.h"
#include "utils/functional_units.h"
#include "utils/tests.h"
#include "utils/memory.h"
#include "utils/bootloader.h"

#include "utils/stage_comb_logic.h"

#define ADD 0b00101001


/* NOTE: 
Written in functional blocks where the output of one function is passed as the input to another. 
The structure will be analagous to the pipelined MIPS processor architecture.
If chained together correctly and each block is correctly implemented then the whole processor cycle will work as expected.
*/


// TODO: Pipeline stage registers
IFID IFID_pipeline_register, IFID_pipeline_register_snapshot = {0};
IDEX IDEX_pipeline_register, IDEX_pipeline_register_snapshot = {0};
EXMEM EXMEM_pipeline_register, EXMEM_pipeline_register_snapshot = {0};
MEMWB MEMWB_pipeline_register, MEMWB_pipeline_register_snapshot = {0};


SPRs SPR_FILE = {.PC = 0b0};
// control_unit CONTROL_UNIT;

// tracking variables - part of simulator
bool clock = 0;
int cycleNumber = 0;

// A new state machine struct is created every time a new instruction starts

// typedef struct {
//     STATE state;
// } instructionState;

// void ASM(instructionState *instructionState) {
//     switch (instructionState -> state)
//     {
//     case IF:
//         /* code */
        
//         break;
//     case ID:
//         break;
//     case EX:
//         break;
//     case MEM:
//         break;
//     case WB:
//         break;
//     default:
//         break;
//     }
// }

int main(int argc, char **argv) {

    bootloader(argv[1]);

    output_IM();
    output_DM();

    do {
        printf("Press enter for next half cycle\n");

        clock = !clock;
        printf("Clock cycle number: %d\n", cycleNumber);

        
        if (clock) { // first half of clock cycle

            IFID_pipeline_register_snapshot = IFID_pipeline_register;
            IDEX_pipeline_register_snapshot = IDEX_pipeline_register;
            EXMEM_pipeline_register_snapshot = EXMEM_pipeline_register;
            MEMWB_pipeline_register_snapshot = MEMWB_pipeline_register;
            
            // all this happens simulataneously in real HW
            fetch(&IFID_pipeline_register, &EXMEM_pipeline_register, &SPR_FILE.PC);
            decode(&IFID_pipeline_register_snapshot, &MEMWB_pipeline_register_snapshot, &IDEX_pipeline_register);
            execute(&IDEX_pipeline_register_snapshot, &EXMEM_pipeline_register);
            memory(&EXMEM_pipeline_register_snapshot, &MEMWB_pipeline_register);
            writeback();

            output_IM();
            output_DM();

        } else { // second half of clock cycle
            
            cycleNumber++;
        }

    } while (getchar() == '\n');


    printf("Exiting.");
    
    return 0;
}