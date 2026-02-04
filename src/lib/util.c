#include "consts.c"


//
// CLI
//


// Print help and exit
void print_help_exit() {
    printf("Steel commands (steel [command] [options]):\n"
           "\n"
           "    build       Build project from config\n"
           "        --debug, --size, --fast, --ram\n"
           "    add         Install lib from link\n"
           "    init        Initialize a Steel package in the current directory\n"
           "\n"
           "    test        Unit testing\n"
           "    fmt         Format Steel code into canonical form\n"
           "    targets     List available compilation targets\n"
           "    version\n"
           "    help        Print help (-h, --help, for C fans)\n"
           "\n");
    exit(0);
}

void print_bad_command_exit(u8* command) {
    printf("Unknown command '%s'!\n"
           "Use '-h' for help\n", command);
    exit(1);
}

void print_version_exit() {
    printf(STEEL_VERSION "\n");
    exit(0);
}

void print_targets_exit() {
    printf("targets TODO!\n");
    exit(0);
}


//
// HConfig
//

// Function to parse JSON and populate HConfig
HConfig hconfig_init() {
    HConfig config;
    // Parse the JSON string using HJson
    HJson* json = HJson_parse_file("steel.json");
    if(json == NULL) {
        return (HConfig){};
        // printf("No config file (steel.json)!");
        // exit(0);
    }

    // Extract the "compiler" field
    HJson* compiler_item = HJson_ObjectGet(json, "compiler");
    if (HJson_IsString(compiler_item) && compiler_item->string != NULL) {
        config.compiler = duplicate_string(compiler_item->string);
    }

    // Extract the "entries" array
    HJson* entries_item = HJson_ObjectGet(json, "entries");
    if (HJson_IsArray(entries_item)) {
        config.entries_len = HJson_ArrayLen(entries_item);
        config.entries = malloc(sizeof(ConfEntry) * config.entries_len);

        for (u8 i = 0; i < config.entries_len; i++) {
            HJson* entry_item = HJson_ArrayAt(entries_item, i);
            HJson* temp_item;

            u8* tt = config.entries[i].name;

            // Extract "name"
            temp_item = HJson_ObjectGet(entry_item, "name");
            if (HJson_IsString(temp_item) && temp_item->string != NULL) {
                config.entries[i].name = duplicate_string(temp_item->string);
            }

            // Extract "headers"
            temp_item = HJson_ObjectGet(entry_item, "headers");
            if (HJson_IsString(temp_item) && temp_item->string != NULL) {
                config.entries[i].headers = duplicate_string(temp_item->string);
            }

            // Extract "exe"
            temp_item = HJson_ObjectGet(entry_item, "exe");
            if (HJson_IsString(temp_item) && temp_item->string != NULL) {
                config.entries[i].exe = duplicate_string(temp_item->string);
            }

            // Extract "lib"
            temp_item = HJson_ObjectGet(entry_item, "lib");
            if (HJson_IsString(temp_item) && temp_item->string != NULL) {
                config.entries[i].lib = duplicate_string(temp_item->string);
            }

            // Extract "include" array
            temp_item = HJson_ObjectGet(entry_item, "include");
            if (HJson_IsArray(temp_item)) {
                u8 include_len = HJson_ArrayLen(temp_item);
                config.entries[i].include = malloc(sizeof(u8*) * include_len);

                for (u8 j = 0; j < include_len; j++) {
                    HJson* include_str_item = HJson_ArrayAt(temp_item, j);
                    if (HJson_IsString(include_str_item) && include_str_item->string != NULL) {
                        config.entries[i].include[j] = duplicate_string(include_str_item->string);
                    }
                }

                config.entries[i].include_len = include_len;
            }
        }
    }

    // Clean up the HJson object
    HJson_free(json);

    return config;
}

// Function to free memory allocated for HConfig
void hconfig_deinit(HConfig config) {
    free(config.compiler);

    for (u8 i = 0; i < config.entries_len; i++) {
        free(config.entries[i].headers);
        free(config.entries[i].name);
        for (u8 j = 0; j < config.entries_len; j++) {
            free(config.entries[i].include[j]);
        }
        free(config.entries[i].include);
    }
    free(config.entries);
}
