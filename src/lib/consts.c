#ifndef CONSTS
#define CONSTS

#include "../lib/cross_util.c"


#define TMP_OUTPATH ".tmp.c"


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

// typedef struct HFile {
//     char* name;
//     char* value;
//     u32 len;
// };

typedef enum {
    Identifier = 0,
    Number = 1,
    String = 2,
    Punctuator = 3,
    Keyword = 4,
    Comment = 5
} TToken;


typedef struct {
    u32 start;
    u32 end;
    TToken type;
    char* value;
} Token;

#endif
