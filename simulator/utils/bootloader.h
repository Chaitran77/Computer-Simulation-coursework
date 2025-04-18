// #include "register_structs.h"
#include <stdio.h>
#include "asm_parser.h"

// No need to pass pointer to IM since it's setters are global
void bootloader(char *program_filename) {

	FILE *program_file = fopen(program_filename, "r"); 

    
	// for (uint8_t i = 0; i < (sizeof(IM)/sizeof(IM[0]))-1; i++)
    // {
    //     uint16_t inst_bin = 0b0;
    //     fgets(inst_bin, 16, program_file);
    //     set_data(i, inst_bin);
    // }

    char stringToParse[150];

    uint8_t IM_addr = 0;

    while (fgets(stringToParse, 150, program_file)) {
        char sanitisedLine[150] = "";
        santise(sanitisedLine, stringToParse);
        
        if (sanitisedLine[0] != '\0') {
            instructionEncapuslator currentInst = parse_line(sanitisedLine);
            set_inst(IM_addr, currentInst);
            IM_addr++;
        }
    }
}
