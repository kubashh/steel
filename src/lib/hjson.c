#include "cross_util.c"


// json types
#define HJson_Invalid (0)
#define HJson_False  (1 << 0)
#define HJson_True   (1 << 1)
#define HJson_Null   (1 << 2)
#define HJson_Number (1 << 3)
#define HJson_String (1 << 4)
#define HJson_Array  (1 << 5)
#define HJson_Object (1 << 6)
#define HJson_Raw    (1 << 7)
#define HJson_IsReference (1 << 8)


// HJson structure
typedef struct {
    // next/prev allow you to walk array/object chains. Alternatively, use GetArraySize/GetArrayItem/GetObjectItem
    struct cJSON *next;
    struct cJSON *prev;
    // An array or object item will have a child pointer pointing to a chain of the items in the array/object.
    struct cJSON *child;

    // The type of the item, as above.
    u8 type;

    // string
    char* string;
    // f64
    f64 number;

    // The item's name string, if this item is the child of, or is in the list of subitems of an object.
    char* name;
} HJson;

typedef struct {
    void* allocated;
} SaveAllocation;


// Headers
HJson* HJson_init(char* src);
void HJson_deinit(HJson* json);


// Helpers
void removeWhiteSpaceBuf(const char* str, char* buf) {
    u32 len = 0;
    for(u32 i = 0; str[i] != '\0'; i++) {
        if(str[i] != '\n' && str[i] != '\t' && str[i] != ' ') {
            buf[len++] = str[i];
        }
    }
    buf[len] = '\0';
}


// HJson


HJson* HJson_init(char* src) {
    char buf[strlen(src) + 1];
    removeWhiteSpaceBuf(src, buf);
    printf("%s\n", src);
    printf("%s\n", buf);
}

void HJson_deinit(HJson* json) {

}
