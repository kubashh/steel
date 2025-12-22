#include "../lib/consts.c"

void check(FileTokens ftokens) {
    Token tok;
    Token prev;
    u32 i = 0;
    for(; (tok = ftokens.tokens[i]).type != TEOF; i++) {
        printf("%s", tok.value);
        prev = tok;
    }
}
