#include "compiler.c"
#include "lib/lib.c"

void compileUtil(ConfEntry entry, char *ccomp) {
    bool isLib = true;
    if (!entry.lib) {
        entry.lib = TMP_OUTPATH;
        isLib = false;
    }
    compiler(entry);

    // C compile
    // char buf[128];
    // sprintf(buf, "%s %s -o%s\n", ccomp, entry.lib, entry.exe);
    // printf("%s", buf);
    // system(buf);
}

// --debug, --size, --fast, --ram
void handle_build(u32 args_len, char *args[]) {
    // printf("Building project...\n");

    // timer_start("Config");
    HConfig config = hconfig_init();
    // timer_end();

    // printf("Compiler: %s\n", config.compiler);

    if (args_len < 3) {
        for (i32 i = 0; i < config.entries_len; i++) {
            compileUtil(config.entries[i], config.compiler);
        }
    } else {
        for (i32 i = 2; i < args_len; i++) {
            for (i32 j = 0; j < config.entries_len; j++) {
                if (strcmp(args[i], config.entries[j].name) == 0) {
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

void handle_add(u32 args_len, char *args[]) {}

void handle_init(u32 args_len, char *args[]) {
    printf(GREEN "creating" RESET " src/main.steel\n");
    write_file("src/main.steel", "fn main() {\n"
                                 "    print(\"Hello Steel!\");\n"
                                 "}\n");
    // write_file("steel.json", "{\n"
    //                          "}\n");
}

void handle_test(u32 args_len, char *args[]) {}

void handle_fmt(u32 args_len, char *args[]) {}

i32 main(i32 args_len, char *args[]) {
    if (args_len < 2) {
        print_help_exit();
    }

    // Check the first argument (the command)
    if (strcmp(args[1], "build") == 0)
        handle_build(args_len, args);
    else if (strcmp(args[1], "add") == 0)
        handle_add(args_len, args);
    else if (strcmp(args[1], "init") == 0)
        handle_init(args_len, args);
    else if (strcmp(args[1], "test") == 0)
        handle_test(args_len, args);
    else if (strcmp(args[1], "fmt") == 0)
        handle_fmt(args_len, args);
    else if (strcmp(args[1], "targets") == 0)
        print_targets_exit();
    else if (strcmp(args[1], "version") == 0)
        print_version_exit();
    else if (strcmp(args[1], "help") == 0 || strcmp(args[1], "-h") == 0 ||
             strcmp(args[1], "--help") == 0)
        print_help_exit();
    else
        print_bad_command_exit(args[1]);

    return 0;
}
