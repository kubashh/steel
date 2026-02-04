#include "./lib/consts.c"
#include "./parser/tokenizer.c"
#include "./parser/ast.c"

void compiler(ConfEntry entry) {
    // Print info
    printf("Name: %s\n", entry.name);
    printf("  Headers: %s\n", entry.headers);
    printf("  Exe: %s\n", entry.exe);
    printf("  Lib: %s\n", entry.lib);
    printf("  Includes: ");
    for(i32 i = 0; i < entry.include_len; i++) {
        printf("%s ", entry.include[i]);
    }
    printf("\n\n");

    // GenAst
    ASTNode* programs[entry.include_len];
    for(i32 i = 0; i < entry.include_len; i++) {
        programs[i] = AST_init(entry.include[i]);
    }

    // // Compile
    // // get tokens
    // FileTokens filesTokens[entry.include_len];
    // for(i32 i = 0; i < entry.include_len; i++) {
    //     // Tokenize
    //     filesTokens[i] = tokenize_file(entry.include[i]);
    //     printf("%s\n\n", entry.include[i]);
    // }

    // // Print tokens
    // u8 buf[64 * 1024];
    // i32 buf_i = 0;
    // for(i32 i = 0; i < entry.include_len; i++) {
    //     // Tokenize
    //     for(i32 j = 0; j < filesTokens[i].len; j++) {
    //         buf_i += sprintf(&buf[buf_i], "%s", filesTokens[i].tokens[j].value);
    //         printf("token: %10s type: %s\n", filesTokens[i].tokens[j].value, TYPES_NAMES[filesTokens[i].tokens[j].type]);
    //     }
    // }
    // buf[buf_i] = '\0';
    // puts(buf);

    // u32 bundled_len = 0;
    // for(i32 i = 0; i < entry.include_len; i++) {
    //     bundled_len += filesTokens->len;
    // }

    // Token bundlendTokens[bundled_len];
    // // u32 
    // for(i32 i = 0; i < entry.include_len; i++) {
    //     for(i32 j = 0; j < filesTokens[i].len; i++) {
    //         // bundlendTokens[i] = 
    //     }
    // }

    // Free/ need fix sth see all malloc and free
    for(i32 i = 0; i < entry.include_len; i++) {
        AST_deinit(programs[i]);
    }
}
