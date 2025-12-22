#include "../lib/consts.c"
#include "tokenizer.c"

void compiler(ConfEntry entry) {
    // Print info
    printf("Name: %s\n", entry.name);
    printf("  Headers: %s\n", entry.headers);
    printf("  Exe: %s\n", entry.exe);
    printf("  Lib: %s\n", entry.lib);
    printf("  Includes: ");
    for(u8 i = 0; i < entry.include_len; i++) {
        printf("%s ", entry.include[i]);
    }
    printf("\n\n");

    // Compile
    // get tokens
    FileTokens filesTokens[entry.include_len];
    for(u8 i = 0; i < entry.include_len; i++) {
        // Tokenize
        filesTokens[i] = tokenize_init(entry.include[i]);
    }

    u32 bundled_len = 0;
    for(u8 i = 0; i < entry.include_len; i++) {
        bundled_len += filesTokens->len;
    }

    Token bundlendTokens[bundled_len];
    // u32 
    for(u8 i = 0; i < entry.include_len; i++) {
        for(u32 j = 0; j < filesTokens[i].len; i++) {
            // bundlendTokens[i] = 
        }
    }

    // Free/ need fix sth see all malloc and free
    for(u8 i = 0; i < entry.include_len; i++) {
        tokenize_deinit(filesTokens[i]);
    }
}
