#include <stdint.h>
#include <stdio.h>
#include <limits.h>

// only called by IM_process() and bootloader()
instructionEncapuslator *get_inst(uint8_t addr);
void set_inst(uint8_t addr, instructionEncapuslator inst);

// only called by DM_process() and bootloader()
uint32_t get_data(uint8_t addr);
void set_data(uint8_t addr, uint32_t data);


uint32_t get_reg(uint8_t number);
void set_reg(uint8_t number, uint32_t value);



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
    printf("REGISTERS PROCESS\n");
    
    // reads data for instruction actually in the decode stage
    IDEX_state_register->REGReadData1 = get_reg(IFID_state_register->instruction.rs);
    IDEX_state_register->REGReadData2 = get_reg(IFID_state_register->instruction.rt);

    // writes data for the instruction that is at the end of the pipeline
    if (MEMWB_state_register->sig_RegWrite) {
        // could have used a ternery conditional as set_reg() data/value argument, but the pointer path are a bit long
        if (MEMWB_state_register->sig_MemtoReg) {
            set_reg(MEMWB_state_register->writeRegister, MEMWB_state_register->DMReadData);
            printf("SETTING REG FROM DM\n");
        } else {
            set_reg(MEMWB_state_register->writeRegister, MEMWB_state_register->ALUResult);
            printf("SETTING REG ALUResult\n");
        }
    }

}



// 2 sets of addressable memory

// static uint32_t IM[256] = {0}; // prog. len. ~64 lines => capacity is 256, 32-bit wide instructions (8-bit addr)
static instructionEncapuslator IM[256]; // prog. len. ~64 lines => capacity is 256, 32-bit wide instructions (8-bit addr)
static uint32_t DM[256] = {0}; // max data addresses = 256, 32-bit wide data => 8-bit addr

static uint32_t REG[32] = {0};

uint32_t get_reg(uint8_t reg_number) {
    if (reg_number < 32) return REG[reg_number-1];
    printf("INVALID REGISTER %d", reg_number); exit(-1); 
}

void set_reg(uint8_t reg_number, uint32_t value) {
    // TODO
    // if (!(reg_number > 32 || reg_number < 1)) {
        REG[reg_number-1] = value;
    // } else {
    //     printf("INVALID REGISTER %d (set)", reg_number); exit(-1); 
    // };
}


instructionEncapuslator *get_inst(uint8_t addr) {
    // The following check was implemented but is not necessary due to the rollover when incrementing at 255. This ensures that addr will always be in range of IM.
    // if (addr <= (sizeof(IM)/sizeof(IM[0]))-1) return &IM[addr];
    // printf("OUTSIDE of INSTRUCTION memory: Address %d", addr); exit(0);

    return &IM[addr];
}

void set_inst(uint8_t addr, instructionEncapuslator inst) {
    // The following check was implemented but is not necessary due to the rollover when incrementing at 255. This ensures that addr will always be in range of IM.
    // if (addr < (sizeof(IM)/sizeof(IM[0]))) {
    //     IM[addr] = inst;
    // } else {
    //     printf("OUTSIDE of INSTRUCTION memory: Setting Address %d", addr); exit(-1);
    // }

    IM[addr] = inst;
}


uint32_t get_data(uint8_t addr) {
    // The following check was implemented but is not necessary due to the rollover when incrementing at 255. This ensures that addr will always be in range of DM.
    // if (addr <= (sizeof(DM)/sizeof(DM[0]))-1) return DM [addr];
    // printf("OUTSIDE of DATA memory: Address %d", addr); exit(-1);
    
    return DM [addr];
}

void set_data(uint8_t addr, uint32_t data) {
    // The following check was implemented but is not necessary due to the rollover when incrementing at 255. This ensures that addr will always be in range of DM.
    // if (addr < (sizeof(DM)/sizeof(DM[0]))) {
    //     DM[addr] = data;
    // } else {
    //     printf("OUTSIDE of DATA memory: Setting Address %d", addr); exit(-1);
    // };

    DM[addr] = data;
}

// for debugging

void output_registers() {

    // want this to be horizontally output

    printf("REGISTERS\n");

    for (uint8_t i = 0; i < 32; i++)
    {
        printf("(R%02d: %3d)%c %c", i, get_reg(i), (i==31)?'\0':',', (i==15)?'\n':'\0'); // values can have upto 6 digits but I won't print numbers greater than 3
    }

    printf("\n");
    
}

void output_IM() {
    printf("INST MEM\nAddress		Instruction\n");
    for (uint16_t i = 0; i < (sizeof(IM)/sizeof(IM[0])); i++)
    {        
        if (i==20) break;
        printf("%7d		", i);
        print_instruction(get_inst(i));
    }
    
}

void output_DM() {
    // for testing
    #ifdef TEST
    DM[200] = 3;
    DM[201] = 31;
    DM[202] = 314;
    DM[203] = 3141;
    DM[204] = 31415;
    DM[205] = 314159;
    #endif

    printf("DATA MEM\n |");

    for (uint16_t i = 0; i < (sizeof(DM)/sizeof(DM[0])); i++) // (sizeof(DM)/sizeof(DM[0]))
    {
        printf("%3d: %6d %c | ", i, get_data(i), ((i%8)==7)?'\n':' ');
    }
    
}