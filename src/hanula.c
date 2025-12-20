#include "lib/cross_util.c"
#include "cli/cli.c"
#include "compiler/compiler.c"
#include "lib/config_alloc.c"
#include "lib/hjson.c"

void compileUtil(ConfEntry entry, char* ccomp) {
    bool isLib = true;
    if(!entry.lib) {
        entry.lib = TMP_OUTPATH;
        isLib = false;
    }
    compiler(entry);

    // C compile
    char buf[64];
    sprintf(buf, "%s %s -o%s\n", ccomp, entry.lib, entry.exe);
    printf("%s", buf);
    system(buf);
}

void build(u8 args_len, char *args[]) {
    printf("Building project...\n");

    // Config
    char* configText = readFileAlloc("hanula.json");
    if(!configText) {
        printf("No config file (hanula.json)!");
        exit(0);
    }

    HJson_init(configText);
    exit(0);

    // Create an instance of HConfig
    HConfig config;

    // Parse the JSON string into HConfig
    if (parse_json_to_hconfig(configText, &config) != 0) {
        printf("Failed to parse JSON.\n"); // Failed to parsed JSON into HConfig
        exit(0);
    }

    printf("Compiler: %s\n", config.compiler);

    if(args_len < 3) {
        for(u8 i = 0; i < config.entries_len; i++) {
            compileUtil(config.entries[i], config.compiler);
        }
    } else {
        for(u8 i = 2; i < args_len; i++) {
            for(u8 j = 0; j < config.entries_len; j++) {
                if(strcmp(args[i], config.entries[j].name) == 0) {
                    compileUtil(config.entries[j], config.compiler);
                    break;
                }
                printf("Unknown name '%s'\n", args[i]);
            }
        }
    }

    // Free the allocated memory
    free_hconfig(&config);
    free(configText);
    printf("Done.\n");
}

u8 main(u8 args_len, char *args[]) {
    if(args_len < 2) {
        print_help();
        exit(0);
    }

    // Check the first argument (the command)
    if(strcmp(args[1], "build") == 0) build(args_len, args);
    else if(strcmp(args[1], "-h") == 0) print_help();
    else {
        printf("Unknown command '%s'!\n\n", args[1]);
        print_help();
    }

    return 0;
}