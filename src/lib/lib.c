#pragma once
#include "util.c"


// globall errors
u8** errors = NULL;

// there is few errors at time, so there is no need for making allocation efficient
void error_push(u8* msg) {
    if(errors == NULL) {
        errors = malloc(sizeof(u8**) * 2);
        errors[0] = msg;
        errors[1] = NULL;
    } else {
        u32 len = 0;
        if(errors != NULL) {
            while(errors[len] != NULL) {
                len++;
            }
        }
        len++;
        errors = realloc(errors, sizeof(u8**) * (len + 1));
        errors[len -1] = msg;
        errors[len] = NULL;
    }
}

void error_print_exit() {
    for(i32 i = 0; errors[i] != NULL; i++) {
        puts(errors[i]);
    }
    exit(1);
}
