#pragma once

#include "hjson.c"

// Lib headers Api
HJson* HJson_parse_fast(u8* src);


// Utils
static HJson* parse_value_fast(ParseBuffer* const input_buf);


// Helpers
static inline void skipWhitespace_fast(ParseBuffer* const input_buf) {
    while(**input_buf != '\0' && (**input_buf == ' ' || **input_buf == '\n')) {
        (*input_buf)++;
    }
}


// HJson

static const u8 is_num_char[256] = {
    ['0'] = 1, ['1'] = 1, ['2'] = 1, ['3'] = 1, ['4'] = 1,
    ['5'] = 1, ['6'] = 1, ['7'] = 1, ['8'] = 1, ['9'] = 1,
    ['+'] = 1, ['-'] = 1, ['.'] = 1, ['e'] = 1
};

static inline HJson* parse_number_fast(ParseBuffer* const input_buf) {
    u8 len = 1;
    while(is_num_char[(*input_buf)[len]]) {
        len++;
    }

    u8 buf[len + 1];

    memcpy(buf, *input_buf, len);
    buf[len] = '\0';

    *input_buf += len;

    HJson* node = HJson_NewAlloc();
    node->type = HJson_Number;
    node->number = atof(buf);
    return node;
}


// Need validated string
static inline u8* parse_string_fast(ParseBuffer* const input_buf) {
    (*input_buf)++; // skip "
    // allocate bigger? and realocate?
    u32 skipped_bytes = 0;
    u32 src_len = 0;
    while((*input_buf)[src_len] != '"') {
        if((*input_buf)[src_len] == '\\') {
            skipped_bytes++;
            src_len++;
        }
        src_len++;
    }

    u8* out = malloc(src_len - skipped_bytes + 1);

    u8* out_ptr = out;
    u8* src_end = (*input_buf) + src_len;
    while(*input_buf < src_end) {
        if(**input_buf != '\\') {
            *(out_ptr++) = *(*input_buf)++;
        } else { // escape sequence
            switch ((*input_buf)[1]) {
                case 'n':
                    *(out_ptr++) = '\n';
                    break;
                case 't':
                    *(out_ptr++) = '\t';
                    break;
                case '"':
                    *(out_ptr++) = '"';
                    break;
                case '\\':
                    *(out_ptr++) = '\\';
                    break;
            }
            (*input_buf) += 2;
        }
    }

    (*input_buf)++;
    (*out_ptr) = '\0';

    return out;
}


static inline HJson* parse_array_fast(ParseBuffer* const input_buf) {
    (*input_buf)++; // skip '['
    HJson* array = HJson_NewAlloc();
    array->type = HJson_Array;
    skipWhitespace_fast(input_buf);
    HJson* prev = NULL;
    HJson* cur_item = NULL;

    while(**input_buf != ']' && **input_buf != '\0') {
        cur_item = parse_value_fast(input_buf);
        if(prev == NULL) {
            array->child = cur_item;
        } else {
            prev->next = cur_item;
        }

        skipWhitespace_fast(input_buf);
        if(**input_buf == ',') (*input_buf)++;
        skipWhitespace_fast(input_buf);
        prev = cur_item;
    }

    (*input_buf)++; // skip ']'

    return array;
}


static inline HJson* parse_object_fast(ParseBuffer* const input_buf) {
    (*input_buf)++; // skip '{'
    HJson* object = HJson_NewAlloc();
    object->type = HJson_Object;
    skipWhitespace_fast(input_buf);
    HJson* prev = NULL;
    HJson* cur_item = NULL;

    while(**input_buf != '}' && **input_buf != '\0') {
        u8* name = parse_string_fast(input_buf);
        (*input_buf)++;
        skipWhitespace_fast(input_buf);
        cur_item = parse_value_fast(input_buf);
        cur_item->name = name;
        // allocate string name
        if(prev == NULL) {
            object->child = cur_item;
        } else {
            prev->next = cur_item;
        }

        skipWhitespace_fast(input_buf);
        if(**input_buf == ',') (*input_buf)++;
        skipWhitespace_fast(input_buf);
        prev = cur_item;
    }

    (*input_buf)++; // skip '}'

    return object;
}


static HJson* parse_value_fast(ParseBuffer* const input_buf) {
    skipWhitespace_fast(input_buf);

    switch(**input_buf) {
        // string
        case '"': {
            HJson* node = HJson_NewAlloc();
            node->type = HJson_String;
            node->string = parse_string_fast(input_buf);
            return node;
        }

        // object
        case '{': {
            return parse_object_fast(input_buf);
        }

        // array
        case '[': {
            return parse_array_fast(input_buf);
        }

        // number
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-': {
            return parse_number_fast(input_buf);
        }

        // true
        case 't': {
            (*input_buf) += 4;
            HJson* node = HJson_NewAlloc();
            node->type = HJson_True;
            return node;
        }

        // false
        case 'f': {
            (*input_buf) += 5;
            HJson* node = HJson_NewAlloc();
            node->type = HJson_False;
            return node;
        }

        // null is null needed?
        case 'n': {
            (*input_buf) += 4;
            HJson* node = HJson_NewAlloc();
            node->type = HJson_False;
            return node;
        }
    }
}


// Init allocate in memory
HJson* HJson_parse_fast(u8* src) {
    return parse_value_fast(&src);
}
