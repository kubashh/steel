#include "lib/lib.c"
#include "compiler.c"


void compileUtil(ConfEntry entry, u8* ccomp) {
    bool isLib = true;
    if(!entry.lib) {
        entry.lib = TMP_OUTPATH;
        isLib = false;
    }
    compiler(entry);

    // C compile
    // u8 buf[128];
    // sprintf(buf, "%s %s -o%s\n", ccomp, entry.lib, entry.exe);
    // printf("%s", buf);
    // system(buf);
}

// --debug, --size, --fast, --ram
void handle_build(u8 args_len, u8 *args[]) {
    // printf("Building project...\n");

    // timer_start("Config");
    HConfig config = hconfig_init();
    // timer_end();

    // printf("Compiler: %s\n", config.compiler);

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
                // print_bad_command_exit(args[i]); ????
            }
        }
    }

    // Free the allocated memory
    hconfig_deinit(config);
    printf("Done.\n");
}

void handle_add() {
}

void handle_init() { // easy
}

void handle_test() {
}

void handle_fmt() {
}

//            "    targets     List available compilation targets\n"
//            "    version\n"
//            "    help        Print help. (-h, --help, for C fans)\n"

u8 main(u8 args_len, u8 *args[]) {
    if(args_len < 2) {
        print_help_exit();
    }

    // Check the first argument (the command)
    if(strcmp(args[1], "build") == 0) handle_build(args_len, args);
    else if(strcmp(args[1], "add") == 0) handle_add(args_len, args);
    else if(strcmp(args[1], "init") == 0) handle_init(args_len, args);
    else if(strcmp(args[1], "test") == 0) handle_test(args_len, args);
    else if(strcmp(args[1], "fmt") == 0) handle_fmt(args_len, args);
    else if(strcmp(args[1], "targets") == 0) print_targets_exit();
    else if(strcmp(args[1], "version") == 0) print_version_exit();
    else if(strcmp(args[1], "help") == 0 || strcmp(args[1], "-h") == 0 || strcmp(args[1], "--help") == 0) print_help_exit();
    else print_bad_command_exit(args[1]);

    return 0;
}
