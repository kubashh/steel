#ifndef CROSS_UTIL
#define CROSS_UTIL


//
// cross include
//

// just for IDE
#ifndef CLOCK_MONOTONIC
#define CLOCK_MONOTONIC 0
#endif

// All platforms
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "stdint.h"
#include "string.h"
#include "time.h"
#include "dirent.h"


#ifdef _WIN32 // Windows

#include "windows.h" // Sleep

#else // Posix (Linux / Mac)

#include "sys/time.h"
#include "unistd.h"    // usleep

#endif

// pub

#define pub


//
// int, uint, float
//

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t
#define u128 __uint128_t
#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t
#define i128 __int128_t

#define f32 float
#define f64 double

#ifdef __float80
#define f80 __float80
#endif

#ifdef __f128
#define f128 __f128
#endif


//
// string
//

char* duplicate_string(const char* str);

// Duplicate string and allocate
char* duplicate_string(const char* str) {
    if (str == NULL) return NULL;
    char* dup_str = malloc(strlen(str) + 1);
    if (dup_str) {
        strcpy(dup_str, str);
    }
    return dup_str;
}

// //
// // getchar
// //

// #ifdef _WIN32
//     #include "conio.h"  // _getch
// #else
//     #include "termios.h" // termios
//     #include "unistd.h" // tcgetattr, tcsetattr, read, tcsetattr
// #endif

// // Cross-platform function to get a single character
// char cross_getchar() {
// #ifdef _WIN32
//     return _getch();  // Reads a single key without waiting for Enter
// #else
//     struct termios oldt, newt;
//     char ch;

//     // Get current terminal settings
//     tcgetattr(STDIN_FILENO, &oldt);
//     newt = oldt;

//     // Disable canonical mode and echo
//     newt.c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSANOW, &newt);

//     read(STDIN_FILENO, &ch, 1);  // Read 1 character

//     // Restore original terminal settings
//     tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

//     return ch;
// #endif
// }


//
// sleep
//

void sleep_ms(u32 ms);

void sleep_ms(u32 ms) {
#ifdef _WIN32
    Sleep(ms); // ms
#else
    usleep(ms * 1000); // ms / 1000
#endif
}


// //
// // thread
// //

// #ifdef _WIN32
//     #include "windows.h" // HANDLE, DWORD, CreateThread, WaitForSingleObject, CloseHandle
//     typedef HANDLE cross_thread_t;
//     typedef DWORD thread_return_t;
// #else
//     #include "pthread.h" // pthread_t, pthread_create, pthread_join
//     typedef pthread_t cross_thread_t;
//     typedef void* thread_return_t;
// #endif

// typedef thread_return_t (*thread_func_t)(void *);

// i32 cross_thread_create_basic(cross_thread_t *t, thread_func_t func);
// cross_thread_t cross_thread_create(thread_func_t func);
// i32 cross_thread_join(cross_thread_t t);


// #ifdef _WIN32

// static DWORD WINAPI win_thread_func(LPVOID arg) {
//     thread_func_t func = ((thread_func_t*)arg)[0];
//     void *farg = ((void**)arg)[1];
//     free(arg);
//     return func(farg);
// }

// i32 cross_thread_create(cross_thread_t *t, thread_func_t func, void *arg) {
//     void **pack = malloc(2 * sizeof(void*));
//     pack[0] = func;
//     pack[1] = arg;
//     *t = CreateThread(NULL, 0, win_thread_func, pack, 0, NULL);
//     return (*t == NULL);
// }

// i32 cross_thread_join(cross_thread_t t) {
//     WaitForSingleObject(t, INFINITE);
//     CloseHandle(t);
//     return 0;
// }

// #else // POSIX

// i32 cross_thread_create_basic(cross_thread_t *t, thread_func_t func) {
//     return pthread_create(t, NULL, func, NULL);
// }

// i32 cross_thread_join(cross_thread_t t) {
//     return pthread_join(t, NULL);
// }

// #endif

// cross_thread_t cross_thread_create(thread_func_t func) {
//     cross_thread_t t;
//     cross_thread_create_basic(&t, func);
//     return t;
// }

// //
// // clear
// //

// void cross_clear();

// void cross_clear() {
// #if _WIN32
//     system("cls");
// #else
//     system("clear");
// #endif
// }


//
// now_s now_ms now_micro now_nano
//

u64 now_s();
u32 now_ms();
u64 now_micro();
u64 now_nano();

u64 now_s() {
    return time(NULL);
}


#ifdef _WIN32
    u32 now_ms() {
        FILETIME ft;
        GetSystemTimeAsFileTime(&ft);
        u64 time = ((u64)ft.dwLowDateTime | ((u64)ft.dwHighDateTime << 32));
        return (u32)(time / 10000);
    }
#else
    u32 now_ms() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv.tv_sec * 1000 + tv.tv_usec / 1000;
    }
#endif

#ifdef _WIN32
    // Get current time in microseconds
    u64 now_micro() {
        FILETIME ft;
        GetSystemTimeAsFileTime(&ft);
        u64 time = ((u64)ft.dwLowDateTime | ((u64)ft.dwHighDateTime << 32));
        return (u64)(time / 10); // Convert to microseconds
    }

    // Get current time in nanoseconds
    u64 now_nano() {
        LARGE_INTEGER frequency, counter;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&counter);
        return (counter.QuadPart * 1000000000LL) / frequency.QuadPart; // Convert to nanoseconds
    }

#else
    // Get current time in microseconds
    u64 now_micro() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return (u64)(tv.tv_sec) * 1000000LL + tv.tv_usec; // Convert to microseconds
    }

    // Get current time in nanoseconds
    u64 now_nano() {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts); // CLOCK_MONOTONIC for a steady clock
        return (u64)(ts.tv_sec) * 1000000000LL + ts.tv_nsec; // Convert to nanoseconds
    }

#endif


//
// measure_start measure_end
//

u64 measure_start() {
    return now_micro();
}

void measure_end(const char* const label, const u64 start) {
    const u64 t = now_micro() - start;
    if(t < 1000) {
        printf("%s: %3.2fμs\n", label, (f64)t);
    } else if(t < 1000000) {
        printf("%s: %3.2fms\n", label, (f64)t / 1000.0);
    } else {
        printf("%s: %3.2fs\n", label, (f64)t / 1000000.0);
    }
}

void measure_end_buf(char* buf, const u64 start) {
    const u64 t = now_micro() - start;
    if(t < 1000) {
        sprintf(buf, "%ldμs", t);
    } else if(t < 1000000) {
        sprintf(buf, "%ldms", t / 1000);
    } else {
        sprintf(buf, "%lds", t / 1000000);
    }
}


//
// randomize
//

void randomize();
u32 rand_max(const u32 max);

inline void randomize() {
    srand(time(NULL));
}

u32 rand_max(const u32 max) {
    return rand() % max;
}

//
// Files
//

char* read_file_alloc(const char* const filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return NULL;

    // Move the file pointer to the end of the file to get the size
    fseek(file, 0, SEEK_END);
    u32 fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);  // Move back to the beginning of the file

    // Allocate memory for the file content, including space for the null terminator
    char *content = (char *)malloc(fileSize + 1);
    if (content == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    // Read the file contents into the allocated memory
    u32 bytesRead = fread(content, 1, fileSize, file);
    content[bytesRead] = '\0';  // Null-terminate the string

    // Close the file
    fclose(file);

    return content;
}

u32 read_file_len(const char* const filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return 0;

    // Move the file pointer to the end of the file to get the size
    fseek(file, 0, SEEK_END);
    u32 fileSize = ftell(file) + 1;
    fclose(file);
    return fileSize;
}

bool read_file_buf(char* buf, const u32 fileSize, const char* const filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return NULL;

    // Read the file contents into the allocated memory
    u32 bytesRead = fread(buf, 1, fileSize, file);
    buf[bytesRead] = '\0';  // Null-terminate the string

    // Close the file
    fclose(file);

    return true;
}

u8 write_file(const char* const path, const char* const src) {
    FILE* file = fopen(path, "w");

    if (file == NULL) return 1;

    fputs(src, file);

    // Close the file when done
    fclose(file);
}

// //
// // scan_dir_alloc
// //

// char** scan_dir_alloc() {
//     const char *dir_name = "src";
//     DIR *dir = opendir(dir_name);  // Open the directory

//     if (dir == NULL) return NULL;

//     struct dirent *entry;
    
//     // Read entries from the directory one by one
//     while ((entry = readdir(dir)) != NULL) {
//         // Print the name of the file or directory
//         printf("%s\n", entry->d_name);
//         printf("%c\n", entry->d_type);
//     }

//     // Close the directory when done
//     closedir(dir);
// }

#endif
