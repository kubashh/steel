#include "../lib/consts.c"


typedef struct {
    char* code;
    u32 i;
} CurrentTokenizer;

CurrentTokenizer curTok;


char tok_peek() {
    return curTok.code[curTok.i];
}

char tok_peek_n(i8 n) {
    return curTok.code[curTok.i + n];
}

u8 tok_match(const char * exp) {
    u8 i = 0;
    for(; exp[i] != '\0'; i++) {
        if(exp[i] != tok_peek_n(i)) return false;
    }
    return i;
}

// 6 bits punctator_i, 2 bits len
typedef struct {
    u8 len;
    char* str;
} TokHasPunctator;
TokHasPunctator tok_has_punctator() {
    for(u8 i = 0; i < PUNCTATORS_LEN; i++) {
        u8 len;
        if(len = tok_match(punctators[i])) {
            TokHasPunctator thp = {len, punctators[i]};
            // printf("len: %d\n", len);
            return thp;
        }
    }

    // printf("len: %d\n", 0);
    TokHasPunctator thp = {0};
    return thp;
}

bool tok_symbol_start() {
    char c = tok_peek();
    return 'A' <= c && c <= 'Z' || 'a' <= c && c <= 'z' || c == '_';
}

bool tok_symbol_then(char c) {
    return 'A' <= c && c <= 'Z' || 'a' <= c && c <= 'z' || '0' <= c && c <= '9' || c == '_';
}


Token tok_next() {
    Token t;

    u32 line = 1;
    u32 line_i = 1;
    for(u32 i = 0; i < curTok.i; i++) {
        if(curTok.code[i] == '\n') {
            line++;
            line_i = 1;
        }
        else line_i++;
    }

    t.line = line;
    t.line_i = line_i;

    // EOF
    if(tok_peek() == '\0') {
        t.type = TEOF;
        return t;
    }

    // Whitespace
    if(tok_peek() == ' ' || tok_peek() == '\n') {
        curTok.i++;
        return tok_next();
    }

    // Need buffer
    char buf[256];

    // Comments
    if(tok_match("//")) {
        buf[0] = '/';
        buf[1] = '/';
        u8 i = 2;
        char c;
        while((c = tok_peek_n(i)) != '\n' && c != '\0') {
            buf[i] = c;
            i++;
        }
        curTok.i += i;
        buf[i] = '\0';
        t.type = TComment;
        t.value = duplicate_string(buf);
        return t;
    }

    // Punctuators
    TokHasPunctator thp = tok_has_punctator();
    if(thp.len) {
        curTok.i += thp.len;
        t.type = TPunctuator;
        t.value = duplicate_string(thp.str);
        return t;
    }

    // Numbers
    if(strchr(NUMBERS, tok_peek())) {
        buf[0] = tok_peek();
        u8 i = 1;
        if(tok_peek_n(i) == 'x') {
            buf[i] = 'x';
            i++;
        }
        char c;
        while(strchr(NUMBERS, c = tok_peek_n(i))) {
            buf[i] = c;
            i++;
        }
        curTok.i += i;
        buf[i] = '\0';
        t.type = TNumber;
        t.value = duplicate_string(buf);
        return t;
    }
    // Char as number
    if(tok_peek() == '\'') {
        u8 i = 0;
        char c;
        while(c = tok_peek_n(i) != '\'') {
            buf[i] = c;
            i++;
        }
        buf[i] = tok_peek_n(i);
        i++;
        buf[i] = '\0';
        curTok.i += i;
        t.type = TNumber;
        t.value = duplicate_string(buf);
        return t;
    }

    // Strings
    if(tok_peek() == '"') {
        buf[0] = '"';
        u8 i = 1;
        char c;
        while((c = tok_peek_n(i)) != '"' || tok_peek_n(i - 1) == '\\') {
            buf[i] = c;
            i++;
        }
        buf[i] = '"';
        i++;
        buf[i] = '\0';
        curTok.i += i;
        t.type = TString;
        t.value = duplicate_string(buf);
        return t;
    }

    // Identifiers/Keywords
    if(tok_symbol_start()) {
        buf[0] = tok_peek();
        char c;
        u8 i = 1;
        while(tok_symbol_then(c = tok_peek_n(i))) {
            buf[i] = c;
            i++;
        }
        buf[i] = '\0';
        curTok.i += i;
        t.type = TIdentifier;
        t.value = duplicate_string(buf);
        for(u8 j = 0; j < C_KEYWORDS_LEN; j++) {
            if(strcmp(cKeywords[j], buf) == 0) {
                t.type = TKeyword;
                break;
            }
        }
        return t;
    }

    // Error
    strcpy(buf, "Unhandled char c\n");

    buf[15] = tok_peek();

    // Error (Token) - unhandled expression

    t.value = duplicate_string(buf);
    t.type = TError;
    return t;
}


bool tok_len_next() {
    // EOF
    if(tok_peek() == '\0') {
        return false;
    }

    // Whitespace
    if(tok_peek() == ' ' || tok_peek() == '\n') {
        curTok.i++;
        return tok_len_next();
    }

    // Comments
    if(tok_match("//")) {
        curTok.i += 2;
        char c;
        while((c = tok_peek()) != '\n' && c != '\0') {
            curTok.i++;
        }
        return true;
    }

    // Punctuators
    TokHasPunctator thp = tok_has_punctator();
    if(thp.len) {
        curTok.i += thp.len;
        return true;
    }

    // Numbers
    if(strchr(NUMBERS, tok_peek())) {
        curTok.i++;
        if(tok_peek() == 'x') {
            curTok.i++;
        }
        while(strchr(NUMBERS, tok_peek())) {
            curTok.i++;
        }
        return true;
    }
    // Char as number
    if(tok_peek() == '\'') {
        curTok.i++;
        while(tok_peek() != '\'') {
            curTok.i++;
        }
        curTok.i++;
        return true;
    }

    // Strings
    if(tok_peek() == '"') {
        curTok.i++;
        while(tok_peek() != '"' || tok_peek(-1) == '\\') {
            curTok.i++;
        }
        curTok.i++;
        return true;
    }

    // Identifiers/Keywords
    if(tok_symbol_start()) {
        curTok.i++;
        while(tok_symbol_then(tok_peek())) {
            curTok.i++;
        }
        return true;
    }

    return false;
}


u32 tok_len() {
    u32 len = 0;
    curTok.i = 0;

    while(tok_len_next()) {
        len++;
    }
    return len;
}


// tokenize from file path 
FileTokens tokenize_init(char* path) {
    // Read File
    char* file = read_file_alloc(path);

    printf("Tokenizing %s\n", path);

    curTok.code = file;

    // u64 start = measure_start();

    FileTokens tslice = {.len = tok_len() + 1, .path = path};
    tslice.tokens = malloc(tslice.len * sizeof(Token));

    curTok.i = 0;
    Token tok;
    u32 i = 0;
    for(; (tok = tok_next()).type != TEOF; i++) {
        if(tok.type == TError) {
            printf("Error: Invalid token at %s %d:%d\n", path, tok.line, tok.line_i);
            printf("%s\n", tok.value);
            exit(0);
        }

        // printf("%s %s %d:%d\n", tok.value, path, tok.line, tok.line_i);

        tslice.tokens[i] = tok;
    }

    tslice.tokens[tslice.len - 1] = tok; // TEOF

    // measure_end("Tokenize", start);

    // Free
    free(file);

    return tslice;
}

void tokenize_deinit(FileTokens tslice) {
    for(u32 i = 0; i < tslice.len - 1; i++) {
        free(tslice.tokens[i].value);
        // free(tslice.tokens);
    }
}
