#pragma once

#include "../../lib/libsteel.c"


#define STEEL_VERSION "0.0.1"

#define TMP_OUTPATH "./tmp.c"


// Colors
#define RESET               "\x1b[0m"
#define RED                 "\x1b[31m"
#define GREEN               "\x1b[32m"
#define YELLOW              "\x1b[33m"
#define BLUE                "\x1b[34m"
#define BOLD_BLUE           "\x1b[1;34m"
#define BACKGROUND_WHITE    "\x1b[31;47m"



#define NUMBERS "0123456789"
#define SYMBOL_START "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_"
#define SYMBOL_THEN "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM_0123456789"


// Compiler types

#define TIdentifier 0
#define TNumber 1
#define TString 2
#define TPunctuator 3
#define TKeyword 4
#define TComment 5
#define TEOF 6
#define TError 7

const u8* TYPES_NAMES[] = {
    "Identifier",
    "Number",
    "String",
    "Punctuator",
    "Keyword",
    "Comment",
    "EOF",
    "Error 7"
};


#define PUNCTATORS_LEN sizeof(punctators) / 8
u8 *punctators[] = { // Sorted by len
    "<<=",  // Left Shift Assignment
    ">>=",  // Right Shift Assignment
    "==",   // Equality Comparison
    "!=",   // Inequality Comparison
    "<=",   // Less Than or Equal
    ">=",   // Greater Than or Equal
    "&&",   // Logical AND
    "||",   // Logical OR
    "<<",   // Left Shift (Bitwise)
    ">>",   // Right Shift (Bitwise)
    "++",   // Increment
    "--",   // Decrement
    "+=",   // Addition Assignment
    "-=",   // Subtraction Assignment
    "*=",   // Multiplication Assignment
    "/=",   // Division Assignment
    "%=",   // Modulus Assignment
    "&=",   // Bitwise AND Assignment
    "|=",   // Bitwise OR Assignment
    "^=",   // Bitwise XOR Assignment
    // "->",   // Pointer to Member Access
    "<",    // Less Than
    ">",    // Greater Than
    ";",    // Semicolon
    ",",    // Comma
    ".",    // Period (member access)
    "(",    // Left Parenthesis
    ")",    // Right Parenthesis
    "{",    // Left Brace
    "}",    // Right Brace
    "[",    // Left Square Bracket
    "]",    // Right Square Bracket
    "!",    // Logical NOT
    "~",    // Bitwise NOT
    "+",    // Addition or Unary Plus
    "-",    // Subtraction or Unary Minus
    "*",    // Multiplication or Pointer Dereference
    "/",    // Division
    "%",    // Modulus (Remainder)
    "&",    // Bitwise AND or Address-of
    "|",    // Bitwise OR
    "^",    // Bitwise XOR
    "=",    // Assignment
    ":",    // Ternary Operator Separator
    "?",    // Ternary Operator (Condition ? True : False)
    // "\"", // Double Quotes (string literal)
    // "'",  // Single Quote (character literal)
    // "//", // C++-style Comment Start (for some compilers)
    // "/*", // Multi-line Comment Start
    // "*/", // Multi-line Comment End
};

#define KEYWORDS_LEN sizeof(KEYWORDS) / 8
u8 *KEYWORDS[] = {
    // Declaration
    "fn",
    "var",
    "const",
    "pub",
    "export"
    // "volatile", // ?? like rust as function
    // "extern", // ?? steel.json
    // "restrict", // ?? good compiler analysis
    // "type", // ??

    // Types
    "i8",
    "i16",
    "i32",
    "i64",
    "i128",
    "u8",
    "u16",
    "u32",
    "u64",
    "u128",
    "f32",
    "f64",
    "enum", // ?? inline
    "struct", // ?? inline with .{} like zig
    "union", // ?? inline with |
    "void",
    // "error", // ??

    // Statements
    "if",
    "while",
    "for", // ?? like zig
    "break", // labeled
    "continue", // labeled
    // "case", // like zig
    "else", // if/switch
    "switch",
    // "default // else like zig
    "do", // ??
    // "goto", // to break/continue labeled
    "return",

    // Other
    "sizeof",
    "test" // like zig
};


// Config
typedef struct ConfEntry {
    u8* name;
    u8* headers;
    u8* exe;
    u8* lib;
    u8** include;
    u8 include_len;
} ConfEntry;

typedef struct HConfig {
    u8* compiler;
    ConfEntry* entries;
    u8 entries_len;
} HConfig;


// typedef struct Slice {
//     void* ptr;
//     u32 len;
// } Slice;


typedef struct Token {
    u8 type;
    u8* value;
    u32 line;
    u32 line_i;
} Token;


typedef struct FileTokens {
    Token* tokens;
    u32 len;
    u8* path;
} FileTokens;
