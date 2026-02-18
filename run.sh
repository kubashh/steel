# clear
clear

# Setup
mkdir -p ./dist

# Build
gcc src/steel.c -odist/steel

# Run
./dist/steel $1 $2 $3 $4

# Cleanup
rm -rf ./dist
