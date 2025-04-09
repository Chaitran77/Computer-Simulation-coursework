int main() {
    char reg_name[] = "$t4";
    // int reg_number = register_translator(reg_name);
    // printf("%d", reg_number);

    // reg_name[0] = "$zero";
    // reg_number = register_translator(reg_name);
    // printf("%d", reg_number);

    if (strcmp(reg_name+1, "t4") == 0) {
        printf("yesy");
    }
}