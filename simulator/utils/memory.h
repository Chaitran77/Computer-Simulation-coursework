#include <stdint.h>
#include <stdio.h>
#include <limits.h>

// https://stackoverflow.com/a/35926790
void print_bin(unsigned int integer)
{
    int i = CHAR_BIT * sizeof integer; /* however many bits are in an integer */
    while(i--) {
        putchar('0' + ((integer >> i) & 1)); 
    }
}

// 2 sets of addressable memory

// static uint32_t IM[256] = {0}; // prog. len. ~64 lines => capacity is 256, 32-bit wide instructions (8-bit addr)
static instructionEncapuslator IM[256]; // prog. len. ~64 lines => capacity is 256, 32-bit wide instructions (8-bit addr)
static uint32_t DM[256] = {0}; // max data addresses = 256, 32-bit wide data => 8-bit addr

instructionEncapuslator *get_inst(uint8_t addr) {
    if (addr > (sizeof(IM)/sizeof(IM[0]))-1) printf("OUTSIDE of INSTRUCTION memory");
    return &IM[addr];
}

uint32_t get_data(uint8_t addr) {
    if (addr > (sizeof(DM)/sizeof(DM[0]))-1) printf("OUTSIDE of DATA memory");
    return DM [addr];
}

void set_inst(uint8_t addr, instructionEncapuslator inst) {
    if (addr < (sizeof(IM)/sizeof(IM[0]))) {
        IM[addr] = inst;
    } else {
        printf("OUTSIDE of INSTRUCTION memory");
    }
}

void set_data(uint8_t addr, uint32_t data) {
    if (addr < (sizeof(DM)/sizeof(DM[0]))) {
        DM[addr] = data;
    } else {
        printf("OUTSIDE of INSTRUCTION memory");
    };
}

// for debugging
void output_IM() {
    printf("INST MEM\nAddress		Instruction\n");
    for (uint16_t i = 0; i < (sizeof(IM)/sizeof(IM[0])); i++)
    {
        // When instructions were binary
        // print_bin(get_inst(i));
        
        printf("%7d		", i);
        printf("%s", get_inst(i)->opcode);
        printf("\n");

        
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