void register_translator_tests() {
    char reg_name[5] = "$t4";
    int reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$zero");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$at");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$v0");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$v1");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$a0");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$a2");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$a3");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$t0");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$t7");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$t9");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$s7");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$k1");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$gp");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$sp");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$fp");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

    strcpy(reg_name, "$ra");
    reg_number = register_translator(reg_name);
    printf("%s %d \n", reg_name, reg_number);

}