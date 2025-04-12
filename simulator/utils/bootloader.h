#include <stdint.h>
#include <stdio.h>

// just need to create 2 sets of addressable memory

static uint16_t IM[256] = {0}; // prog. len. ~64 lines => 256, 16-bit wide instructions => 8-bit addr
static uint32_t DM[256] = {0}; // max data addresses = 256, 32-bit wide data => 8-bit addr

uint16_t get_inst(uint8_t addr) {
    if (addr > (sizeof(IM)/sizeof(IM[0]))-1) printf("OUTSIDE of INSTRUCTION memory");
    return IM[addr];
}

uint32_t get_data(uint8_t addr) {
    if (addr > (sizeof(DM)/sizeof(DM[0]))-1) printf("OUTSIDE of DATA memory");
    return DM [addr];
}

void set_inst(uint8_t addr, uint16_t inst) {
    IM[addr] = inst;
}

void set_data(uint8_t addr, uint32_t data) {
    DM[addr] = data;
}

// for debugging
void output_IM() {
    for (uint8_t i = 0; i < (sizeof(IM)/sizeof(IM[0]))-1; i++)
    {
        printf("%B", IM[i]);
    }
    
}

void output_DM() {

    DM[200] = 3;
    DM[201] = 31;
    DM[202] = 314;
    DM[203] = 3141;
    DM[204] = 31415;
    DM[205] = 314159;


    for (uint8_t i = 0; i < (1<<8)-1; i++) // (sizeof(DM)/sizeof(DM[0]))
    {
        printf("%6d %c", get_data(i), !(i%8)?'\n':' ');
    }
    
}