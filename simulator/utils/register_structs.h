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
    int16_t immediate;
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