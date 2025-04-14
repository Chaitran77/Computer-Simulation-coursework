// #include "register_structs.h"
#include <stdio.h>

// No need to pass pointer to IM since it's setters are global
void bootloader(char **argv) {

	FILE *program_file = fopen(argv[1], "r"); 

    // change the instruction memory to characters and store the characters
	
	for (uint8_t i = 0; i < (sizeof(IM)/sizeof(IM[0]))-1; i++)
    {
        uint16_t inst_bin = 0b0;
        fgets(inst_bin, 16, program_file);
        set_data(i, inst_bin);
    }
}
