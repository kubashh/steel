#ifndef CONSTS
#define CONSTS

#include "../lib/cross_util.c"


#define TMP_OUTPATH ".tmp.c"

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


#define PUNCTATORS_LEN 52
char *punctators[] = { // Sort by len
    "#include", // Preprocessor Directive
    "#define",  // Macro Definition
    "#ifdef",   // Preprocessor Conditional Compilation
    "#endif",   // End of Preprocessor Conditional
    "#else",    // Preprocessor Else
    "#elif",    // Preprocessor Else If
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
    "->",   // Pointer to Member Access
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
    "#",    // Preprocessor directive (e.g., #include)
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

#define C_KEYWORDS_LEN 34
char *cKeywords[] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "inline",
    "int",
    "long",
    "register",
    "restrict",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while"
};


// Config
typedef struct {
    char* name;
    char* headers;
    char* exe;
    char* lib;
    char** include;
    u8 include_len;
} ConfEntry;

typedef struct {
    char* compiler;
    ConfEntry* entries;
    u8 entries_len;
} HConfig;


// typedef struct {
//     void* ptr;
//     u32 len;
// } Slice;


typedef struct {
    u8 type;
    char* value;
    u32 line;
    u32 line_i;
} Token;


typedef struct {
    Token* tokens;
    u32 len;
    char* path;
} FileTokens;


#endif
