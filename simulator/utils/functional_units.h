
void* MUX_2to1(void* in0, void* in1, bool select) {
    /* returns a pointer of undefined type to one of the inputs; 
        all calls should be cast back to the input type */
    return select?in1:in0;
}

uint32_t ADD(uint32_t in1, uint32_t in2) {
     return in1+in2;
}

uint32_t AND(bool in1, bool in2) {
    return in1&&in2; // TODO: Check operator
}

uint8_t ALU_control(uint8_t ALUOp, bool funct) {
    switch (ALUOp)
    { // there are 3 operations that the ALU will need to perform
    case 0: // LW, SW
        return 0; // ADD
    case 1: // BEQ
        return 1; // SUB
    case 2: // funct field decides
        switch (funct)
        { // there are 2 operations that R-type instructions use
        case 0:
            return 0; // ADD
        case 1:
            return 2; // SLT
        }
    default:
        printf("INVALID ALUOp %d, funct %d", ALUOp, funct); exit(-1);
    }
}

uint32_t ALU(uint32_t in1, uint32_t in2, bool *sig_zero, uint8_t sig_ALUCtrl) {
    uint32_t result = 0;

    switch (sig_ALUCtrl)
    {
    case 0: // ADD
        result = in1 + in2;
        break;

    case 1: // SUB
        result = in1 - in2;
        break;
    
    case 2: // SLT
        result = in1 < in2;
        break;
    
    default:
        printf("INVALID ALUCtrl %d", sig_ALUCtrl); exit(-1);
    }

    if (result==0) {
        *sig_zero=1;
    } else {
        *sig_zero=0;
    }

    return result;
}


void control_signal_decoder(instructionEncapuslator instruction, IDEX *IDEX_state_register) {
    
    // instruction.type is derived from the opcode, so all the information is coming from the opcode 

    switch (instruction.type) {
        case R: // R-type instruction
            // control_unit = {.RegDst=true, false, false, true, false, false, false, true, false};
            IDEX_state_register->sig_RegDst=true;
            IDEX_state_register->sig_ALUSrc=false;
            IDEX_state_register->sig_MemtoReg=false;
            IDEX_state_register->sig_RegWrite=true; 
            IDEX_state_register->sig_MemRead=false; 
            IDEX_state_register->sig_MemWrite=false; 
            IDEX_state_register->sig_Branch=false; 
            IDEX_state_register->sig_ALUOp=2; // use funct field
            break;

        case I:
            IDEX_state_register->sig_ALUOp=0;
            IDEX_state_register->sig_ALUSrc=true;
            
            IDEX_state_register->sig_RegDst=false;
            IDEX_state_register->sig_RegWrite=true; 
            
            IDEX_state_register->sig_MemtoReg=false;
            
            IDEX_state_register->sig_MemRead=false;
            IDEX_state_register->sig_MemWrite=false;

            IDEX_state_register->sig_Branch=false;

            if (strcmp(instruction.opcode, "LW") == 0) {
                IDEX_state_register->sig_RegDst=true;
                IDEX_state_register->sig_MemtoReg=true;
                IDEX_state_register->sig_MemRead=false; 
                IDEX_state_register->sig_MemWrite=false; 

            } else if (strcmp(instruction.opcode, "SW") == 0) {
                IDEX_state_register->sig_MemRead=true; 
                IDEX_state_register->sig_MemWrite=false;

            } else if (strcmp(instruction.opcode, "BEQ") == 0) {
                IDEX_state_register->sig_ALUOp=1;
                IDEX_state_register->sig_Branch=true;
            }
            break;

        case J:
            IDEX_state_register->sig_RegDst=false;
            IDEX_state_register->sig_ALUSrc=false;
            IDEX_state_register->sig_MemtoReg=false;
            IDEX_state_register->sig_RegWrite=false; 
            IDEX_state_register->sig_MemRead=false; 
            IDEX_state_register->sig_MemWrite=false; 
            IDEX_state_register->sig_Branch=false; 
            IDEX_state_register->sig_ALUOp=0;
            break;
    }
}