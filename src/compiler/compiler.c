#include "../lib/consts.c"

void compiler(ConfEntry entry) {
    printf("Name: %s\n", entry.name);
    printf("  Headers: %s\n", entry.headers);
    printf("  Exe: %s\n", entry.exe);
    printf("  Lib: %s\n", entry.lib);
    printf("  Includes: ");
    for (u8 i = 0; i < entry.include_len; i++) {
        printf("%s ", entry.include[i]);
    }
    printf("\n\n");
}

Token* tokenize() {
    
}
