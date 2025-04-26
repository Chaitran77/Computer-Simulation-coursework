// most combinational wires/connections are made here

void fetch(IFID *IFID_state_register, EXMEM *EXMEM_state_register, uint8_t *PC_address) {
    
    IFID_state_register->PCNext = ADD(*PC_address, 1);
    
    PC_address = (uint8_t*)MUX_2to1(
        &IFID_state_register->PCNext,
        &EXMEM_state_register->PCNext, 
        AND(EXMEM_state_register->sig_Branch, EXMEM_state_register->sig_ALUZero)
    );
    
    
    printf("FETCHING INSTRUCTION NUMBER %d", *PC_address);

    IM_process(IFID_state_register, *PC_address);

    printf("FETCHED INSTRUCTION ")
}

void decode(IFID *IFID_state_register, MEMWB *MEMWB_state_register, IDEX *IDEX_state_register) {

    IDEX_state_register->PCNext = IFID_state_register->PCNext;

    IDEX_state_register->signExtImm = IFID_state_register->instruction.immediate; // TODO: Fix sign-extend
    IDEX_state_register->funct = IFID_state_register->instruction.funct;

    IDEX_state_register->rt = IFID_state_register->instruction.rt;
    IDEX_state_register->rd = IFID_state_register->instruction.rd;


    control_signal_decoder(IFID_state_register->instruction, IDEX_state_register);
    registers_process(IFID_state_register, MEMWB_state_register, IDEX_state_register);    

}

void execute(IDEX *IDEX_state_register, EXMEM *EXMEM_state_register) {

    EXMEM_state_register->sig_MemtoReg = IDEX_state_register->sig_MemtoReg;
    EXMEM_state_register->sig_RegWrite = IDEX_state_register->sig_RegWrite;
    EXMEM_state_register->sig_MemRead = IDEX_state_register->sig_MemRead;
    EXMEM_state_register->sig_MemWrite = IDEX_state_register->sig_MemWrite;
    EXMEM_state_register->sig_Branch = IDEX_state_register->sig_Branch;
        
    EXMEM_state_register->ALUResult=ALU(
        IDEX_state_register->REGReadData1, 
        (uint32_t)MUX_2to1(
            &IDEX_state_register->REGReadData2, 
            &IDEX_state_register->signExtImm, 
            IDEX_state_register->sig_ALUSrc
        ),
        &EXMEM_state_register->sig_ALUZero, 
        ALU_control(IDEX_state_register->sig_ALUOp, IDEX_state_register->funct)
    );

    EXMEM_state_register->PCNext = (uint8_t)ADD(
        (uint32_t)IDEX_state_register->PCNext, 
        IDEX_state_register->signExtImm
    );
    EXMEM_state_register->REGReadData2 = IDEX_state_register->REGReadData2;
    
    EXMEM_state_register->writeRegister = (uint8_t)MUX_2to1(
        &IDEX_state_register->rt, 
        &IDEX_state_register->rd, 
        IDEX_state_register->sig_RegDst
    );
}

void memory(EXMEM *EXMEM_state_register, MEMWB *MEMWB_state_register) {

    MEMWB_state_register->sig_MemtoReg = EXMEM_state_register->sig_MemtoReg;
    MEMWB_state_register->sig_RegWrite = EXMEM_state_register->sig_RegWrite;

    DM_process(EXMEM_state_register, MEMWB_state_register);
}

void writeback() {
    // handled in register file logic
}