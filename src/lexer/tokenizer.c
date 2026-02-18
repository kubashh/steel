#pragma once
#include "../lib/lib.c"


typedef struct CurrentTokenizer {
    u8* code;
    u8* path;
    u32 i;
} CurrentTokenizer;

CurrentTokenizer curTok;


u8 tok_peek() {
    return curTok.code[curTok.i];
}

u8 tok_peek_n(u8 n) {
    return curTok.code[curTok.i + n];
}

u8 tok_match(const u8* exp) {
    u8 i = 0;
    for(; exp[i] != '\0'; i++) {
        if(exp[i] != tok_peek_n(i)) return false;
    }
    return i;
}

// 6 bits punctator_i, 2 bits len
typedef struct TokHasPunctator {
    u32 len;
    u8* str;
} TokHasPunctator;
TokHasPunctator tok_has_punctator() {
    for(i32 i = 0; i < PUNCTATORS_LEN; i++) {
        u32 len;
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
    u8 c = tok_peek();
    return 'A' <= c && c <= 'Z' || 'a' <= c && c <= 'z' || c == '_';
}

bool tok_symbol_then(u8 c) {
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
        t.value = NULL;
        return t;
    }

    // Whitespace
    if(tok_peek() == ' ' || tok_peek() == '\n') {
        curTok.i++;
        return tok_next();
    }

    // Need buffer
    u8 buf[256];

    // Comments
    if(tok_match("//")) {
        buf[0] = '/';
        buf[1] = '/';
        i32 i = 2;
        u8 c;
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
        i32 i = 1;
        if(tok_peek_n(i) == 'x') {
            buf[i] = 'x';
            i++;
        }
        u8 c;
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
        i32 i = 0;
        u8 c;
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
        i32 i = 1;
        u8 c;
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
        u8 c;
        i32 i = 1;
        while(tok_symbol_then(c = tok_peek_n(i))) {
            buf[i] = c;
            i++;
        }
        buf[i] = '\0';
        curTok.i += i;
        t.type = TIdentifier;
        t.value = duplicate_string(buf);
        for(i32 j = 0; j < KEYWORDS_LEN; j++) {
            if(strcmp(KEYWORDS[j], buf) == 0) {
                t.type = TKeyword;
                break;
            }
        }
        return t;
    }

    // Error


    sprintf(buf, "%s %d:%d " ERR_RED ": Invalid token '%c'\n",
        curTok.path, t.line, t.line_i, tok_peek());

    error_push(duplicate_string(buf));

    t.type = TError;
    t.value = malloc(2);
    t.value[0] = tok_peek();
    t.value[1] = '\0';
    curTok.i++;
    return t;
}


// tokenize from file path 
FileTokens tokenize_file(u8* path) {
    // Read File
    u8* file = read_file_alloc(path);
    if(!file) {
        printf("File '%s' do not exists!\n", path); // TODO red color
        exit(1);
    }

    printf("Tokenizing %s\n", path);

    curTok = (CurrentTokenizer){
        .code = file,
        .path = path,
        .i = 0
    };

    // timer_start("Tokenize");

    u32 tslice_tok_alloc_size = 64 * 1024; // 64KB
    FileTokens tslice = { .path = path };
    tslice.tokens = malloc(tslice_tok_alloc_size * sizeof(Token));

    u32 i = 0;
    Token tok;
    while((tok = tok_next()).type != TEOF) {
        if(i >= tslice_tok_alloc_size) {
            tslice_tok_alloc_size <<= 1;
            tslice.tokens = realloc(tslice.tokens, tslice_tok_alloc_size * sizeof(Token));
        }

        // printf("%s %s %d:%d\n", tok.value, path, tok.line, tok.line_i);

        tslice.tokens[i] = tok;
        i++;
    }

    if(errors) {
        error_print_exit();
    }

    tslice.len = i + 1; // for TEOF
    tslice.tokens[tslice.len - 1] = tok; // TEOF
    tslice.tokens = realloc(tslice.tokens, tslice.len * sizeof(Token)); // fix tslilce size

    // timer_end();

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
