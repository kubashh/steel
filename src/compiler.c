#include "lib/lib.c"
#include "lexer/tokenizer.c"
#include "parser/ast.c"

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
        const FileTokens tokens = tokenize_file(entry.include[i]);
        programs[i] = AST_init(tokens);
        tokenize_deinit(tokens);
    }

    // // Compile
    // // get tokens
    // FileTokens files_tokens[entry.include_len];
    // for(i32 i = 0; i < entry.include_len; i++) {
    //     // Tokenize
    //     files_tokens[i] = tokenize_file(entry.include[i]);
    //     printf("%s\n\n", entry.include[i]);
    // }

    // // Print tokens
    // u8 buf[64 * 1024];
    // i32 buf_i = 0;
    // for(i32 i = 0; i < entry.include_len; i++) {
    //     // Tokenize
    //     for(i32 j = 0; j < files_tokens[i].len; j++) {
    //         buf_i += sprintf(&buf[buf_i], "%s", files_tokens[i].tokens[j].value);
    //         printf("token: %10s type: %s\n", files_tokens[i].tokens[j].value, TYPES_NAMES[files_tokens[i].tokens[j].type]);
    //     }
    // }
    // buf[buf_i] = '\0';
    // puts(buf);

    // u32 bundled_len = 0;
    // for(i32 i = 0; i < entry.include_len; i++) {
    //     bundled_len += files_tokens->len;
    // }

    // Token bundlend_tokens[bundled_len];
    // // u32 
    // for(i32 i = 0; i < entry.include_len; i++) {
    //     for(i32 j = 0; j < files_tokens[i].len; i++) {
    //         // bundlend_tokens[i] = 
    //     }
    // }

    // Free/ need fix sth see all malloc and free
    for(i32 i = 0; i < entry.include_len; i++) {
        AST_deinit(programs[i]);
    }
}
