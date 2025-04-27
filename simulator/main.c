#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// #define TEST
// #define RUNTESTS

#include "utils/global_enums.h"
#include "utils/register_translator.h"
#include "utils/register_structs.h"
#include "utils/functional_units.h"
#include "utils/memory.h"
#include "utils/bootloader.h"
#include "utils/stage_comb_logic.h"

#include "utils/tests.h"



/* NOTE: 
Written in functional blocks where the output of one function is passed as the input to another. 
The structure will be analagous to the pipelined MIPS processor architecture.
If chained together correctly and each block is correctly implemented then the whole processor cycle will work as expected.
*/


// TODO: Pipeline stage registers
IFID IFID_pipeline_register = {
    .PCNext = 0,
    .instruction = (instructionEncapuslator){ 
        .opcode = "", .type = 0, .rs = 0, .rt = 0, .rd = 0, .funct = 0, .shamt = 0, .immediate = 0, .address = 0
    }
};

IFID IFID_pipeline_register_snapshot = {
    .PCNext = 0,
    .instruction = (instructionEncapuslator){ 
        .opcode = "", .type = 0, .rs = 0, .rt = 0, .rd = 0, .funct = 0, .shamt = 0, .immediate = 0, .address = 0
    }
};

IDEX IDEX_pipeline_register = {
    .sig_RegDst = 0, .sig_ALUSrc = 0, .sig_MemtoReg = 0, .sig_RegWrite = 0, .sig_MemRead = 0, .sig_MemWrite = 0, .sig_Branch = 0, .sig_ALUOp = 0, .PCNext = 0, .REGReadData1 = 0, .REGReadData2 = 0, .signExtImm = 0, .funct = 0, .rt = 0, .rd = 0
};

IDEX IDEX_pipeline_register_snapshot = {
    .sig_RegDst = 0, .sig_ALUSrc = 0, .sig_MemtoReg = 0, .sig_RegWrite = 0, .sig_MemRead = 0, .sig_MemWrite = 0, .sig_Branch = 0, .sig_ALUOp = 0, .PCNext = 0, .REGReadData1 = 0, .REGReadData2 = 0, .signExtImm = 0, .funct = 0, .rt = 0, .rd = 0
};


EXMEM EXMEM_pipeline_register = {
    .sig_MemtoReg = 0, .sig_RegWrite = 0, .sig_MemRead = 0, .sig_MemWrite = 0, .sig_Branch = 0, .sig_ALUZero = 0, .PCNext = 0, .ALUResult = 0, .REGReadData2 = 0, .writeRegister = 0
};

EXMEM EXMEM_pipeline_register_snapshot = {
    .sig_MemtoReg = 0, .sig_RegWrite = 0, .sig_MemRead = 0, .sig_MemWrite = 0, .sig_Branch = 0, .sig_ALUZero = 0, .PCNext = 0, .ALUResult = 0, .REGReadData2 = 0, .writeRegister = 0
};

MEMWB MEMWB_pipeline_register = {
    .sig_MemtoReg = 0, .sig_RegWrite = 0, .DMReadData = 0, .ALUResult = 0, .writeRegister = 0
};

MEMWB MEMWB_pipeline_register_snapshot = {
    .sig_MemtoReg = 0, .sig_RegWrite = 0, .DMReadData = 0, .ALUResult = 0, .writeRegister = 0
};


SPRs SPR_FILE = {.PC = 0};

// tracking variables - part of simulator
bool clock = 0;
int cycleNumber = 0;

int maxCycles = 6;

int main(int argc, char **argv) {
    (void)argc;
    #ifndef RUNTESTS

    bootloader(argv[1]);
    set_reg(17, 17);

    output_IM();
    output_DM();

    output_registers();


    do {
        // printf("Press enter for next half cycle\n");

        clock = !clock;
        printf("\n\nCLOCK CYCLE %u\n", cycleNumber);

        IFID_pipeline_register_snapshot = IFID_pipeline_register;
        IDEX_pipeline_register_snapshot = IDEX_pipeline_register;
        EXMEM_pipeline_register_snapshot = EXMEM_pipeline_register;
        MEMWB_pipeline_register_snapshot = MEMWB_pipeline_register;
        
        // all this happens simulataneously in real HW
        if (cycleNumber%5==0) printf("========\n");
        print_IFID(&IFID_pipeline_register_snapshot, false, cycleNumber%5==0);
        fetch(&IFID_pipeline_register, &EXMEM_pipeline_register, &SPR_FILE.PC);
        print_IFID(&IFID_pipeline_register, true, cycleNumber%5==0);
        if (cycleNumber%5==0) printf("========\n\n");
        
        if (cycleNumber%5==1) printf("========\n");
        print_IDEX(&IDEX_pipeline_register_snapshot, false, cycleNumber%5==1);
        decode(&IFID_pipeline_register_snapshot, &MEMWB_pipeline_register_snapshot, &IDEX_pipeline_register);
        print_IDEX(&IDEX_pipeline_register, true, cycleNumber%5==1);
        if (cycleNumber%5==1) printf("========\n\n");
        
        if (cycleNumber%5==2) printf("========\n");
        print_EXMEM(&EXMEM_pipeline_register_snapshot, false, cycleNumber%5==2);
        execute(&IDEX_pipeline_register_snapshot, &EXMEM_pipeline_register);
        print_EXMEM(&EXMEM_pipeline_register, true, cycleNumber%5==2);
        if (cycleNumber%5==2) printf("========\n\n");
        
        if (cycleNumber%5==3) printf("========\n");
        print_MEMWB(&MEMWB_pipeline_register_snapshot, false, cycleNumber%5==3);
        memory(&EXMEM_pipeline_register_snapshot, &MEMWB_pipeline_register);
        print_MEMWB(&MEMWB_pipeline_register, true, cycleNumber%5==3);
        if (cycleNumber%5==3) printf("========\n\n");
        
        if (cycleNumber%5==4) printf("========\n");
        writeback();
        if (cycleNumber%5==4) {printf("========\n\n"); };

        output_registers();

        if (cycleNumber>maxCycles) break;
        cycleNumber++;

        
/*        if (clock) { // first half of clock cycle


        } else { // second half of clock cycle
            
            cycleNumber++;
        }
*/
    } while (1); // (getchar() == '\n');

    output_registers();

    #else

    run_tests(argv);

    #endif

    printf("Exiting.");
    
    return 0;
}