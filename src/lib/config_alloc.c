#include "cross_util.c"
#include "cJSON.c"
#include "consts.c"

// Function to parse JSON and populate HConfig
i8 parse_json_to_hconfig(const char* json_str, HConfig* config) {
    // Parse the JSON string using cJSON
    cJSON* json = cJSON_Parse(json_str);
    if (json == NULL) {
        printf("Error parsing JSON config hanula.json\n");
        return -1;
    }

    // Extract the "compiler" field
    cJSON* compiler_item = cJSON_GetObjectItemCaseSensitive(json, "compiler");
    if (cJSON_IsString(compiler_item) && compiler_item->valuestring != NULL) {
        config->compiler = duplicate_string(compiler_item->valuestring);
    }

    // Extract the "entries" array
    cJSON* entries_item = cJSON_GetObjectItemCaseSensitive(json, "entries");
    if (cJSON_IsArray(entries_item)) {
        config->entries_len = cJSON_GetArraySize(entries_item);
        config->entries = malloc(sizeof(ConfEntry) * config->entries_len);

        for (u8 i = 0; i < config->entries_len; i++) {
            cJSON* entry_item = cJSON_GetArrayItem(entries_item, i);
            cJSON* temp_item;

            char* tt = config->entries[i].name;

            // Extract "name"
            temp_item = cJSON_GetObjectItemCaseSensitive(entry_item, "name");
            if (cJSON_IsString(temp_item) && temp_item->valuestring != NULL) {
                config->entries[i].name = duplicate_string(temp_item->valuestring);
            }

            // Extract "headers"
            temp_item = cJSON_GetObjectItemCaseSensitive(entry_item, "headers");
            if (cJSON_IsString(temp_item) && temp_item->valuestring != NULL) {
                config->entries[i].headers = duplicate_string(temp_item->valuestring);
            }

            // Extract "exe"
            temp_item = cJSON_GetObjectItemCaseSensitive(entry_item, "exe");
            if (cJSON_IsString(temp_item) && temp_item->valuestring != NULL) {
                config->entries[i].exe = duplicate_string(temp_item->valuestring);
            }

            // Extract "lib"
            temp_item = cJSON_GetObjectItemCaseSensitive(entry_item, "lib");
            if (cJSON_IsString(temp_item) && temp_item->valuestring != NULL) {
                config->entries[i].lib = duplicate_string(temp_item->valuestring);
            }

            // Extract "include" array
            temp_item = cJSON_GetObjectItemCaseSensitive(entry_item, "include");
            if (cJSON_IsArray(temp_item)) {
                u8 include_len = cJSON_GetArraySize(temp_item);
                config->entries[i].include = malloc(sizeof(char*) * include_len);

                for (u8 j = 0; j < include_len; j++) {
                    cJSON* include_str_item = cJSON_GetArrayItem(temp_item, j);
                    if (cJSON_IsString(include_str_item) && include_str_item->valuestring != NULL) {
                        config->entries[i].include[j] = duplicate_string(include_str_item->valuestring);
                    }
                }

                config->entries[i].include_len = include_len;
            }
        }
    }

    // Clean up the cJSON object
    cJSON_Delete(json);

    return 0;
}

HConfig hconfig_init() {
    // Read file
    char* configText = read_file_alloc("hanula.json");
    if(!configText) {
        printf("No config file (hanula.json)!");
        exit(0);
    }

    // Create an instance of HConfig
    HConfig config;

    // Parse the JSON string into HConfig
    if (parse_json_to_hconfig(configText, &config) != 0) {
        printf("Failed to parse JSON.\n"); // Failed to parsed JSON into HConfig
        exit(0);
    }

    free(configText);

    return config;
}

// Function to free memory allocated for HConfig
void free_hconfig(HConfig* config) {
    free(config->compiler);

    for (u8 i = 0; i < config->entries_len; i++) {
        free(config->entries[i].headers);
        free(config->entries[i].name);
        for (u8 j = 0; j < config->entries_len; j++) {
            free(config->entries[i].include[j]);
        }
        free(config->entries[i].include);
    }
    free(config->entries);
}
