#include "cross_util.c"


// atoi (str => int) or atof (str => double)


// json types
#define HJson_Invalid (0)
#define HJson_False   (1 << 0)
#define HJson_True    (1 << 1)
#define HJson_Null    (1 << 2)
#define HJson_Number  (1 << 3)
#define HJson_String  (1 << 4)
#define HJson_Array   (1 << 5)
#define HJson_Object  (1 << 6)


#define HJson_NewAlloc() (HJson*)calloc(1, sizeof(HJson))


// HJson structure
typedef struct HJson {
    // next for walking on array/object linked list
    struct HJson *next;
    // An array or object item will have a child pointer pointing to a chain of the items in the array/object.
    struct HJson *child;

    // TO Consider: evry thing as void* value? (number, string, child)

    u8 type;

    // The item's name string, if this item is the child of, or is in the list of subitems of an object.
    char* name;

    // f64
    f64 number;
    // string
    char* string;
} HJson;

typedef struct {
    void* allocated;
} SaveAllocation;

typedef char* ParseBuffer;


// Lib headers
HJson* HJson_parse(char* src);
void HJson_free(HJson* json);
char* HJson_stringify(HJson* json);

// Utils
// HJson* HJson_CreateNumber(f64 num);
// HJson* HJson_CreateString(char* str);
HJson* HJson_NewElement(u8 type);

HJson* parse_value(ParseBuffer* input_buffer);


// Helpers
void skipWhitespace(ParseBuffer* str) {
    while(**str != '\0' && (**str == ' ' || **str == '\n')) {
        (*str)++;
    }
}


// HJson


// Init allocate in memory
HJson* HJson_parse(char* src) {
    return parse_value(&src);
}


HJson* HJson_NewElement(u8 type) {
    HJson* node = HJson_NewAlloc();
    if (node) {
        memset(node, '\0', sizeof(HJson));
    }
    node->type = type;

    return node;
}


// Need validated string
HJson* parse_string(ParseBuffer* input_buf) {
    (*input_buf)++;
    u32 len = 0;
    u32 src_len = 0;
    char c;
    while(c = (*input_buf)[src_len] != '"' || (*input_buf)[src_len - 1] == '\\') {
        if((*input_buf)[src_len] != '\\') len++;
        src_len++;
    }

    char* out = malloc(len + 1);

    u32 i = 0;
    u32 src_i = 0;
    while(src_i < src_len && i < len) {
        if((*input_buf)[src_i] != '\\') {
            out[i] = (*input_buf)[src_i];
            src_i++;
            i++;
        } else { // escape sequence
            switch ((*input_buf)[src_i + 1]) {
                case 'n':
                    out[i] = '\n';
                    break;
                case 't':
                    out[i] = '\t';
                    break;
                case '"':
                    out[i] = '"';
                    break;
                case '\\':
                    out[i] = '\\';
                    break;

                default:
                    printf("Error at parse_string (HJson): illegal escape character %c\n", (*input_buf)[src_i + 1]);
            }
            src_i += 2;
            i++;
        }
    }

    (*input_buf) += src_len + 1;
    out[len] = '\0';

    HJson* node = HJson_NewAlloc();
    node->type = HJson_String;
    node->string = out;
    return node;
}


HJson* parse_number(ParseBuffer* input_buf) {
    u8 len = 1;
    char c;
    while(c = (*input_buf)[len]) {
        switch(c) {
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
            case '+':
            case '-':
            case '.':
            case 'e':
                len++;
                break;
            default:
                goto loop_end;
        }
    }

loop_end:

    char buf[len + 1];

    memcpy(buf, *input_buf, len);
    buf[len] = '\0';

    *input_buf += len;

    HJson* node = HJson_NewAlloc();
    node->type = HJson_Number;
    node->number = atof(buf);
    return node;
}


HJson* parse_array(ParseBuffer* input_buf) {
    (*input_buf)++; // skip [
    HJson* array = HJson_NewElement(HJson_Array);
    skipWhitespace(input_buf);
    HJson* prev = NULL;
    HJson* cur_item = NULL;

    while(**input_buf != ']' && **input_buf != '\0') {
        cur_item = parse_value(input_buf);
        if(prev == NULL) {
            array->child = cur_item;
        } else {
            prev->next = cur_item;
        }

        skipWhitespace(input_buf);
        if(**input_buf == ',') (*input_buf)++;
        skipWhitespace(input_buf);
        prev = cur_item;
    }

    (*input_buf)++; // skip ]

    return array;
}


HJson* parse_object(ParseBuffer* input_buf) {
    // (*input_buf)++; // skip }
    // HJson* object = HJson_NewElement(HJson_Object);
    // skipWhitespace(input_buf);
    // HJson* prev = NULL;
    // HJson* cur_item = NULL;

    // while(**input_buf != ']' && **input_buf != '\0') {
    //     cur_item = parse_value(input_buf);
    //     // allocate string name
    //     if(prev == NULL) {
    //         object->child = cur_item;
    //     } else {
    //         prev->next = cur_item;
    //     }

    //     skipWhitespace(input_buf);
    //     if(**input_buf == ',') (*input_buf)++;
    //     skipWhitespace(input_buf);
    //     prev = cur_item;
    // }

    // (*input_buf)++; // skip {

    // return object;
}


HJson* parse_value(ParseBuffer* input_buf) {
    skipWhitespace(input_buf);

    // string
    if(**input_buf == '"') {
        return parse_string(input_buf);
    }

    // number
    if('0' < **input_buf && **input_buf <= '9') {
        return parse_number(input_buf);
    }

    // array
    if(**input_buf == '[') {
        return parse_array(input_buf);
    }

    // object
    if(**input_buf == '{') {
        // TODO
        return parse_object(input_buf);
    }

    // true
    if(strncmp((const char*)(*input_buf), "true", 4) == 0) {
        (*input_buf) += 4;
        return HJson_NewElement(HJson_True);
    }

    // false
    if(strncmp((const char*)(*input_buf), "false", 5) == 0) {
        (*input_buf) += 5;
        return HJson_NewElement(HJson_False);
    }

    // null
    if(strncmp((const char*)(*input_buf), "null", 4) == 0) {
        (*input_buf) += 4;
        
        return HJson_NewElement(HJson_Null);
    }
}


// Stringify allocate json string
char* HJson_stringify(HJson* json) {

}


// Free memory
void HJson_free(HJson* json) {
    if(json->child) HJson_free(json->child);
    if(json->name) free(json->name);
    if(json->string) free(json->string);
    if(json->next) {
        HJson_free(json->next);
        free(json->next);
    }
}
