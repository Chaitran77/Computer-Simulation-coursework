// register translator ($t4 => 12), was going to map enums to numbers with a LUT but that's tedious 
int register_translator(char register_name[5]) {
    int register_number = -1;

    if (strncmp(register_name+1, "zero", 4) == 0) return 0;
    if (strncmp(register_name+1, "at", 2) == 0) return 1;
    if (strncmp(register_name+1, "gp", 2) == 0) return 28;
    if (strncmp(register_name+1, "sp", 2) == 0) return 29;
    if (strncmp(register_name+1, "fp", 2) == 0) return 30;
    if (strncmp(register_name+1, "ra", 2) == 0) return 31;
    
    {
        int register_name_num = register_name[2] - '0';

        // if (register_name_num < 0 || register_name_num > 31) {
        //     printf("ERROR: Invalid register address (OOB)");
        //     exit(-1);
        // }


        switch (register_name[1]) {
            
            case 'v':
                // values for expression results and expression evaluation

                if (register_name_num == 0 || register_name_num == 1) {
                    register_number = register_name_num + 2;
                }
                    
                break;
            case 'a':
                // values for expression results and expression evaluation

                if (register_name_num >= 0 && register_name_num <= 3) {
                    register_number = register_name_num + 4;
                }
                    
                break;
            case 't':
                // the temporaries
    
                if (register_name_num <= 7) {
                    register_number = register_name_num + 8;
                } else if ((register_name_num == 8) || (register_name_num == 9)) {
                    register_number = register_name_num + 16;
                }
                
                break;

            case 's':
                // the saved temporaries

                if (register_name_num >= 0 && register_name_num <= 7) {
                    register_number = register_name_num + 16;
                }
                    
                break;

            case 'k':
                // reserved

                if (register_name_num == 0 || register_name_num == 1) {
                    register_number = register_name_num + 26;
                }
                    
                break;
            
            // no default case because a valid case could be triggered with an OOB register_name_num which req. the same result
        }

        if (register_number>=0) return register_number;
        printf("ERROR: Invalid register address");
        exit(-1);
        
    }

}