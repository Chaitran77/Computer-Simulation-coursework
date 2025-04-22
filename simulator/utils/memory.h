#include <stdint.h>
#include <stdio.h>
#include <limits.h>

// only called by IM_process() and bootloader()
instructionEncapuslator *get_inst(uint8_t addr);
void set_inst(uint8_t addr, instructionEncapuslator inst);

// only called by DM_process() and bootloader()
uint32_t get_data(uint8_t addr);
void set_data(uint8_t addr, uint32_t data);


uint32_t get_register(uint8_t number);
void set_register(uint8_t number, uint32_t value);



void IM_process(IFID *IFID_state_register, uint8_t PC_address) {
    IFID_state_register->instruction = *get_inst(PC_address);
}

void DM_process(EXMEM *EXMEM_state_register, MEMWB *MEMWB_state_register) {
    if (EXMEM_state_register->sig_MemRead) {
        MEMWB_state_register->DMReadData = get_data(EXMEM_state_register->ALUResult);
    } 
    
    if (EXMEM_state_register->sig_MemWrite) {
        set_data(EXMEM_state_register->ALUResult, EXMEM_state_register->REGReadData2);
    }
}

void registers_process(IFID *IFID_state_register, MEMWB *MEMWB_state_register, IDEX *IDEX_state_register) {
    if (MEMWB_state_register->sig_RegWrite) {
        // could have used a ternery conditional as set_register() argument, but names are a bit long
        if (MEMWB_state_register->sig_MemtoReg)
            set_register(MEMWB_state_register->writeRegister, MEMWB_state_register->DMReadData);
        else {
            set_register(MEMWB_state_register->writeRegister, MEMWB_state_register->ALUResult);
        }
    }

    IDEX_state_register->REGReadData1 = get_register(IFID_state_register->instruction.rs);
    IDEX_state_register->REGReadData2 = get_register(IFID_state_register->instruction.rt);

}



// 2 sets of addressable memory

// static uint32_t IM[256] = {0}; // prog. len. ~64 lines => capacity is 256, 32-bit wide instructions (8-bit addr)
static instructionEncapuslator IM[256]; // prog. len. ~64 lines => capacity is 256, 32-bit wide instructions (8-bit addr)
static uint32_t DM[256] = {0}; // max data addresses = 256, 32-bit wide data => 8-bit addr

static uint32_t REG[32] = {0};

uint32_t get_reg(uint8_t reg_number) {
    if (!(reg_number > 32 || reg_number < 1)) return REG[reg_number-1];
    printf("INVALID REGISTER %d", reg_number); exit(-1); 
}

void set_reg(uint8_t reg_number, uint32_t value) {
    if (!(reg_number > 32 || reg_number < 1)) {
        REG[reg_number-1] = value;
    } else {
        printf("INVALID REGISTER %d (set)", reg_number); exit(-1); 
    };
}


instructionEncapuslator *get_inst(uint8_t addr) {
    if (addr <= (sizeof(IM)/sizeof(IM[0]))-1) return &IM[addr];
    printf("OUTSIDE of INSTRUCTION memory: Address %d", addr); exit(0);
}

void set_inst(uint8_t addr, instructionEncapuslator inst) {
    if (addr < (sizeof(IM)/sizeof(IM[0]))) {
        IM[addr] = inst;
    } else {
        printf("OUTSIDE of INSTRUCTION memory: Setting Address %d", addr); exit(-1);
    }
}


uint32_t get_data(uint8_t addr) {
    if (addr <= (sizeof(DM)/sizeof(DM[0]))-1) return DM [addr];
    printf("OUTSIDE of DATA memory: Address %d", addr); exit(-1);
    
}

void set_data(uint8_t addr, uint32_t data) {
    if (addr < (sizeof(DM)/sizeof(DM[0]))) {
        DM[addr] = data;
    } else {
        printf("OUTSIDE of DATA memory: Setting Address %d", addr); exit(-1);
    };
}

// for debugging

void print_instruction(int address) {
    instructionEncapuslator *inst = get_inst(address);
    
    printf(
        "OP: %5s | rs: %2s%d | rt: %2s%d | rd: %2s%d | funct: %1d | shamt: %2d | imm: %5d | addr: %5d|\n", 
        inst->opcode,
        "r", 
        inst->rs,
        "r", 
        inst->rt,
        "r", 
        inst->rd,
        inst->funct,
        inst->shamt,
        inst->immediate,
        inst->address
    );
}

void output_IM() {
    printf("INST MEM\nAddress		Instruction\n");
    for (uint16_t i = 0; i < (sizeof(IM)/sizeof(IM[0])); i++)
    {        
        printf("%7d		", i);
        print_instruction(i);
    }
    
}

void output_DM() {
    // for testing
    DM[200] = 3;
    DM[201] = 31;
    DM[202] = 314;
    DM[203] = 3141;
    DM[204] = 31415;
    DM[205] = 314159;
    
    printf("DATA MEM\n");

    for (uint16_t i = 0; i < (sizeof(DM)/sizeof(DM[0])); i++) // (sizeof(DM)/sizeof(DM[0]))
    {
        printf("%3d %6d %c", i, get_data(i), ((i%4)==3)?'\n':' ');
    }
    
}