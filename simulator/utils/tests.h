// #include "register_structs.h"


void register_translator_tests() {
    char reg_name[6] = "$t4";
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
    
}

void run_instruction() {
    
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

    
    SPRs SPR_FILE = {.PC = 0b0};
    
    IFID_pipeline_register_snapshot = IFID_pipeline_register;
    IDEX_pipeline_register_snapshot = IDEX_pipeline_register;
    EXMEM_pipeline_register_snapshot = EXMEM_pipeline_register;
    MEMWB_pipeline_register_snapshot = MEMWB_pipeline_register;

    fetch(&IFID_pipeline_register, &EXMEM_pipeline_register, &SPR_FILE.PC);
    decode(&IFID_pipeline_register_snapshot, &MEMWB_pipeline_register_snapshot, &IDEX_pipeline_register);
    execute(&IDEX_pipeline_register_snapshot, &EXMEM_pipeline_register);
    memory(&EXMEM_pipeline_register_snapshot, &MEMWB_pipeline_register);
    
    instructionEncapuslator test_instruction = {
        .opcode = "ADD",
        .rd = 16, .rs = 0, .rt = 0,
        .funct = 0,
        
        .shamt = 0
    };

    control_signal_decoder(test_instruction, &IDEX_pipeline_register);

    
}
    void run_tests() {
        run_instruction();
    }