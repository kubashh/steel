#include "../lib/consts.c"
#include "./tokenizer.c"

// Example

// fn main() void {
//     var a = 3;
//     print("a: {}\n", a);
// }

// To:

// AST_PROGRAM
//  └─ functions
//      └─ AST_FUNC_DECL ("main")
//          └─ body
//              └─ AST_BLOCK
//                  ├─ AST_VAR_DECL ("a" = 3)
//                  └─ AST_CALL (print)
//                      ├─ arg1: AST_LITERAL_STR ("a: {}\n")
//                      └─ arg2: AST_IDENT ("a")


enum ASTNodeType {
    AST_PROGRAM,
    AST_DECL_FN,
    AST_DECL_VAR,
    AST_BLOCK,
    AST_CALL,
    AST_CONST
};

typedef struct ASTBlock {
} ASTBlock;

typedef struct ASTProgram {
    ASTBlock block;
} ASTProgram;

typedef struct ASTNode {
    u32 type;

    // union {
    //     // ASTBlock
    //     struct ASTProgram {
    //         ASTBlock block;
    //     };
    // };
} ASTNode;

// will do AST + Tokenization
ASTNode* AST_init(u8* path) {
    // Tokenize
    FileTokens tokens = tokenize_file(path);

    // Print tokens
    u8 buf[64 * 1024];
    i32 buf_i = 0;
    for(i32 j = 0; j < tokens.len; j++) {
        buf_i += sprintf(&buf[buf_i], "%s", tokens.tokens[j].value);
        printf("token: %10s type: %s\n", tokens.tokens[j].value, TYPES_NAMES[tokens.tokens[j].type]);
    }
    buf[buf_i] = '\0';
    puts(buf);


    // Free/ need fix sth see all malloc and free
    tokenize_deinit(tokens);
}

void AST_deinit(ASTNode* program) {
    // free
}
