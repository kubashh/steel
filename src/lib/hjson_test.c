#include "hjson.c"
// #include "cJSON.c"

u8 main() {
    // Read file
    u64 start = measure_start();
    char* file = read_file_alloc("test.json");
    measure_end("Read file", start);

    // HJson parse/free
    start = measure_start();
    HJson* json = HJson_parse(file);

    // printf("%s %ld\n", file, sizeof(HJson));
    // printf("%s\n", json->child->string);
    // printf("%f\n", json->child->next->child->number);
    // printf("%.0f\n", json->child->next->child->number);
    // printf("%s\n", json->child->next->child->next->string);
    // printf("%.0f\n", json->child->next->next->number);
    // printf("%.0f\n", json->number);
    // printf("%s\n", json->string);

    // printf("%d", json->child);
    // parse_value(json, (char*)" false");

    HJson_free(json);
    measure_end("HJson", start);
    
    // printf("%s", file);

    // cJSON parse/free
    // start = measure_start();
    // cJSON* json2 = HJson_parse(file);

    // printf("%s %ld\n", file, sizeof(HJson));
    // printf("%s\n", json2->child->string);
    // printf("%f\n", json2->child->next->child->valuedouble);
    // // printf("%.0f\n", json->child->next->child->number);
    // // printf("%s\n", json->child->next->child->next->string);
    // // printf("%.0f\n", json->child->next->next->number);
    // // printf("%.0f\n", json->number);
    // // printf("%s\n", json->string);

    // // printf("%d", json->child);
    // // parse_value(json, (char*)" false");

    // HJson_free(json2);
    // measure_end("cJSON", start);

    free(file);

    return 0;
}
