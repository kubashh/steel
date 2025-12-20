// Foreground colors (text color):

// 30 → Black
// 31 → Red
// 32 → Green
// 33 → Yellow
// 34 → Blue
// 35 → Magenta
// 36 → Cyan
// 37 → White
// 39 → Default color

// Background colors:

// 40 → Black
// 41 → Red
// 42 → Green
// 43 → Yellow
// 44 → Blue
// 45 → Magenta
// 46 → Cyan
// 47 → White
// 49 → Default background

// Styles:

// 1 → Bold
// 4 → Underline
// 0 → Reset (to default style)


// Define color codes
#define RESET               "\033[0m"
#define RED                 "\033[31m"
#define GREEN               "\033[32m"
#define YELLOW              "\033[33m"
#define BLUE                "\033[34m"
#define BOLD_BLUE           "\033[1;34m"
#define BACKGROUND_WHITE    "\033[31;47m"


// Print help and exit
void print_help() {
    printf("Hanula (lang) commands:\n"
           "    build       # Build the project\n"
           "        <path>  # Specify path for build\n"
           "    -h          # Print help\n");
    exit(0);
}