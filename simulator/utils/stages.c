// most combinational wires/connections are made here

extern SPRs SPR_FILE;

void fetch(IFID *IFID_state_register, EXMEM *EXMEM_state_register) {
    
    if (SPR_FILE.STALL) {
        SPR_FILE.STALL_COUNT -= 1;
        return;
    }

    SPR_FILE.PC = *(uint8_t*)MUX_2to1(
        &IFID_state_register->PCNext,
        &EXMEM_state_register->PCNext, 
        AND(EXMEM_state_register->sig_Branch, EXMEM_state_register->sig_ALUZero)
    );
    
    printf("FETCHING INSTRUCTION NUMBER %d\n", SPR_FILE.PC);
    IM_process(IFID_state_register, SPR_FILE.PC);
    printf("FETCHED INSTRUCTION\n");
    
    
    IFID_state_register->PCNext = ADD(SPR_FILE.PC, 1);
}

void decode(IFID *IFID_state_register, MEMWB *MEMWB_state_register, EXMEM *EXMEM_state_register, IDEX *IDEX_state_register) {

    if (SPR_FILE.STALL) {
        if (SPR_FILE.STALL_COUNT == 0) {
            SPR_FILE.STALL = false;
        } else {
            SPR_FILE.STALL_COUNT -= 1;

            *IDEX_state_register = (IDEX){
                .sig_RegDst = 0, .sig_ALUSrc = 0, .sig_MemtoReg = 0, .sig_RegWrite = 0, .sig_MemRead = 0, .sig_MemWrite = 0, .sig_Branch = 0, .sig_ALUOp = 0, .PCNext = 0, .REGReadData1 = 0, .REGReadData2 = 0, .signExtImm = 0, .funct = 0, .rt = 0, .rd = 0
            };
        }

        return;
    }

    if (IDEX_state_register->sig_RegWrite) {
        if (((EXMEM_state_register->writeRegister == IFID_state_register->instruction.rs) || (EXMEM_state_register->writeRegister == IFID_state_register->instruction.rt)) &&
            ((EXMEM_state_register->writeRegister == IFID_state_register->instruction.rs) || (EXMEM_state_register->writeRegister == IFID_state_register->instruction.rt))) { // writeRegister == 0 check not necessary
                printf("!!! EX HAZARD !!!\n");
                SPR_FILE.STALL = true;
                SPR_FILE.STALL_COUNT = 2;

                // latch this "bubble" data instead of what would otherwise be computed in the else 
                *IDEX_state_register = (IDEX){
                    .sig_RegDst = 0, .sig_ALUSrc = 0, .sig_MemtoReg = 0, .sig_RegWrite = 0, .sig_MemRead = 0, .sig_MemWrite = 0, .sig_Branch = 0, .sig_ALUOp = 0, .PCNext = 0, .REGReadData1 = 0, .REGReadData2 = 0, .signExtImm = 0, .funct = 0, .rt = 0, .rd = 0
                };
        }
    } else if (EXMEM_state_register->sig_RegWrite) {
        if (((MEMWB_state_register->writeRegister == IFID_state_register->instruction.rs) || (MEMWB_state_register->writeRegister == IFID_state_register->instruction.rt)) &&
            ((MEMWB_state_register->writeRegister == IFID_state_register->instruction.rs) || (MEMWB_state_register->writeRegister == IFID_state_register->instruction.rt))) { // writeRegister == 0 check not necessary
                printf("!!! MEM HAZARD !!!\n");
                SPR_FILE.STALL = true;
                SPR_FILE.STALL_COUNT = 2;

                // latch this "bubble" data instead of what would otherwise be computed in the else 
                *IDEX_state_register = (IDEX){
                    .sig_RegDst = 0, .sig_ALUSrc = 0, .sig_MemtoReg = 0, .sig_RegWrite = 0, .sig_MemRead = 0, .sig_MemWrite = 0, .sig_Branch = 0, .sig_ALUOp = 0, .PCNext = 0, .REGReadData1 = 0, .REGReadData2 = 0, .signExtImm = 0, .funct = 0, .rt = 0, .rd = 0
                };
        }
    } else {
        IDEX_state_register->PCNext = IFID_state_register->PCNext;
    
        IDEX_state_register->signExtImm = IFID_state_register->instruction.immediate; // TODO: Fix sign-extend
        IDEX_state_register->funct = IFID_state_register->instruction.funct;
    
        IDEX_state_register->rt = IFID_state_register->instruction.rt;
        IDEX_state_register->rd = IFID_state_register->instruction.rd;
    
    
        control_signal_decoder(IFID_state_register->instruction, IDEX_state_register);
        registers_process(IFID_state_register, MEMWB_state_register, IDEX_state_register);
    }


}

void execute(IDEX *IDEX_state_register, EXMEM *EXMEM_state_register) {

    if (SPR_FILE.STALL) {
        SPR_FILE.STALL_COUNT -= 1;
        return;
    }

    EXMEM_state_register->sig_MemtoReg = IDEX_state_register->sig_MemtoReg;
    EXMEM_state_register->sig_RegWrite = IDEX_state_register->sig_RegWrite;
    EXMEM_state_register->sig_MemRead = IDEX_state_register->sig_MemRead;
    EXMEM_state_register->sig_MemWrite = IDEX_state_register->sig_MemWrite;
    EXMEM_state_register->sig_Branch = IDEX_state_register->sig_Branch;
        
    EXMEM_state_register->ALUResult=ALU(
        IDEX_state_register->REGReadData1, 
        *(uint32_t*)MUX_2to1(
            &IDEX_state_register->REGReadData2, 
            &IDEX_state_register->signExtImm, 
            IDEX_state_register->sig_ALUSrc
        ),
        &EXMEM_state_register->sig_ALUZero, 
        ALU_control(IDEX_state_register->sig_ALUOp, IDEX_state_register->funct)
    );

    EXMEM_state_register->PCNext = (uint8_t)ADD(
        IDEX_state_register->PCNext, 
        IDEX_state_register->signExtImm
    );
    EXMEM_state_register->REGReadData2 = IDEX_state_register->REGReadData2;
    
    EXMEM_state_register->writeRegister = *(uint8_t*)MUX_2to1(
        &IDEX_state_register->rt, 
        &IDEX_state_register->rd, 
        IDEX_state_register->sig_RegDst
    );
}

void memory(EXMEM *EXMEM_state_register, MEMWB *MEMWB_state_register) {

    if (SPR_FILE.STALL) {
        SPR_FILE.STALL_COUNT -= 1;
        return;
    }

    MEMWB_state_register->sig_MemtoReg = EXMEM_state_register->sig_MemtoReg;
    MEMWB_state_register->sig_RegWrite = EXMEM_state_register->sig_RegWrite;

    MEMWB_state_register->ALUResult = EXMEM_state_register->ALUResult;
    MEMWB_state_register->writeRegister = EXMEM_state_register->writeRegister;

    DM_process(EXMEM_state_register, MEMWB_state_register);
}

void writeback() {
    // handled in register file logic
}