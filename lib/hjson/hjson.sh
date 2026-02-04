clear # clear
mkdir -p ./dist # Setup
gcc lib/hjson/hjson_test.c -odist/hjson # Build
./dist/hjson # Run
rm -rf ./dist # Cleanup
