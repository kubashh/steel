# clear
clear

# Build
gcc src/lib/hjson_test.c -odist/hanula
gcc -E src/lib/hjson_test.c -odist/hanula.c
gcc -S src/lib/hjson_test.c -odist/hanula.s

# Run
./dist/hanula $1 $2 $3 $4
