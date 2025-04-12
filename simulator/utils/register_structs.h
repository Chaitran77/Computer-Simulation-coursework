typedef struct {
    // short = 2 bytes = 16 bits
    unsigned short r0; // cannot initialise this to 0 
    unsigned short r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31;
} GPRs;

typedef struct {
    uint8_t PC; // stores the current address in instruction memory
    uint16_t IR; // stores the current instruction
} SPRs;

// control unit signals
typedef struct {
    bool RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch, ALUOp1, ALUOp2;
} control_unit;