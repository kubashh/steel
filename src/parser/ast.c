#include "../lib/lib.c"

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

typedef struct ASTNode ASTNode;


enum ASTNodeType {
    AST_PROGRAM,
    AST_FILE,
    AST_BINARY,
    AST_DECL_FN,
    AST_DECL_VAR,
    AST_BLOCK,
    AST_CALL,
    AST_CONST
};

typedef struct ASTBlock {
    ASTNode** block;
    u32 len;
} ASTBlock;

typedef struct ASTProgram {
    ASTBlock block;
} ASTProgram;

typedef struct ASTNode {
    u32 type;

    union {
        // ASTBlock
        struct {
            ASTNode** block;
            u32 block_len;
        };
    };
} ASTNode;

// to opt
void AST_add(ASTNode* el, ASTNode* new) {
    if(el->block == NULL) {
        el->block = malloc(sizeof(ASTNode));
        el->block_len = 1;
    } else {
        el->block_len++;
        el->block = realloc(el->block, el->block_len);
    }
    el->block[el->block_len - 1] = new;
}

void AST_print(ASTNode* program) {
    // TODO printf();
}

// will do AST + Tokenization
ASTNode* AST_init(FileTokens tokens) {
    printf("Parsing %s\n", tokens.path);
    // // Print tokens
    // // u8 buf[64 * 1024];
    // // i32 buf_i = 0;
    // for(i32 j = 0; j < tokens.len - 1; j++) {
    //     // buf_i += sprintf(&buf[buf_i], "%s ", tokens.tokens[j].value);
    //     printf("%10s:   %s\n", TYPES_NAMES[tokens.tokens[j].type], tokens.tokens[j].value);
    // }
    // // buf[buf_i] = '\0';
    // // puts(buf);

    ASTNode* program = malloc(sizeof(ASTNode));
    program->type = AST_FILE;
    // program->block = malloc()


    // Free/ need fix sth see all malloc and free
}

void AST_deinit(ASTNode* program) {
    // free
}
