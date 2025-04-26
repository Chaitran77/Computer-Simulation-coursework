typedef struct {
    uint32_t r0; // cannot initialise this to 0 here
    uint32_t r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31;
} GPRs;

typedef struct {
    uint8_t PC; // stores the current access address in instruction memory
    uint32_t IR; // stores the current instruction
} SPRs;



typedef struct {
    char opcode[10];
    instructionType type;
    uint8_t rs, rt, rd; 
    bool funct; // only 1 function
    int8_t shamt;
    uint16_t immediate;
    uint32_t address; // following 26-bit address convention, but IM really only requires 8 bits
} instructionEncapuslator;


// all control signal names
// RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch, ALUOp1, ALUOp2

typedef struct {
    uint8_t PCNext;
    instructionEncapuslator instruction;
} IFID;

typedef struct {
    bool sig_RegDst, sig_ALUSrc, sig_MemtoReg, sig_RegWrite, sig_MemRead, sig_MemWrite, sig_Branch;
    uint8_t sig_ALUOp;
    
    uint8_t PCNext;
    uint16_t REGReadData1;
    uint16_t REGReadData2;
    uint32_t signExtImm;
    bool funct;
    uint8_t rt;
    uint8_t rd;
} IDEX;

typedef struct {
    bool sig_MemtoReg, sig_RegWrite, sig_MemRead, sig_MemWrite, sig_Branch;    
    bool sig_ALUZero;
    
    uint8_t PCNext;
    uint32_t ALUResult;
    uint32_t REGReadData2;
    uint8_t writeRegister;
} EXMEM;

typedef struct {
    bool sig_MemtoReg, sig_RegWrite;    

    uint32_t DMReadData;
    uint32_t ALUResult;
    uint8_t writeRegister;
} MEMWB;


void print_instruction(const instructionEncapuslator* instr) {
    
    printf(
        "[INST] | op: %5s | rs: %2d | rt: %2d | rd: %2d | funct: %1d | shamt: %2d | imm: %5d | addr: %5d|\n", 
        instr->opcode,
        instr->rs,
        instr->rt,
        instr->rd,
        instr->funct,
        instr->shamt,
        instr->immediate,
        instr->address
    );
}

void print_IFID(const IFID* ifid, bool new) {
    printf("[%s IFID] | PCNext: %u | ", new ? "New" : "Old", ifid->PCNext);
    print_instruction(&ifid->instruction);
}

void print_IDEX(const IDEX* idex, bool new) {
    printf("[%s IDEX] | sig_RegDst: %s | sig_ALUSrc: %s | sig_MemtoReg: %s | sig_RegWrite: %s | sig_MemRead: %s | sig_MemWrite: %s | sig_Branch: %s | sig_ALUOp: %u | PCNext: %u | REGReadData1: %u | REGReadData2: %u | signExtImm: %u | funct: %s | rt: %u | rd: %u\n",
            new ? "New" : "Old",
            idex->sig_RegDst ? "true" : "false",
            idex->sig_ALUSrc ? "true" : "false",
            idex->sig_MemtoReg ? "true" : "false",
            idex->sig_RegWrite ? "true" : "false",
            idex->sig_MemRead ? "true" : "false",
            idex->sig_MemWrite ? "true" : "false",
            idex->sig_Branch ? "true" : "false",
            idex->sig_ALUOp,
            idex->PCNext,
            idex->REGReadData1,
            idex->REGReadData2,
            idex->signExtImm,
            idex->funct ? "true" : "false",
            idex->rt,
            idex->rd);
}

void print_EXMEM(const EXMEM* exmem, bool new) {
    printf("[%s EXMEM] | sig_MemtoReg: %s | sig_RegWrite: %s | sig_MemRead: %s | sig_MemWrite: %s | sig_Branch: %s | sig_ALUZero: %s | PCNext: %u | ALUResult: %u | REGReadData2: %u | writeRegister: %u\n",
            new ? "New" : "Old",
            exmem->sig_MemtoReg ? "true" : "false",
            exmem->sig_RegWrite ? "true" : "false",
            exmem->sig_MemRead ? "true" : "false",
            exmem->sig_MemWrite ? "true" : "false",
            exmem->sig_Branch ? "true" : "false",
            exmem->sig_ALUZero ? "true" : "false",
            exmem->PCNext,
            exmem->ALUResult,
            exmem->REGReadData2,
            exmem->writeRegister);
}

void print_MEMWB(const MEMWB* memwb, bool new) {
    printf("[%s MEMWB] | sig_MemtoReg: %s | sig_RegWrite: %s | DMReadData: %u | ALUResult: %u | writeRegister: %u\n",
            new ? "New" : "Old",
            memwb->sig_MemtoReg ? "true" : "false",
            memwb->sig_RegWrite ? "true" : "false",
            memwb->DMReadData,
            memwb->ALUResult,
            memwb->writeRegister);
}

