# Compile the source files into object files
gcc -c heap_usage.c -o heap_usage.o
gcc -c stack_ll.c -o stack_ll.o
gcc -c linked_list.c -o linked_list.o
gcc -c cgStackDriver.c -o cgStackDriver.o

# Link the object files to create the executable
gcc heap_usage.o stack_ll.o linked_list.o cgStackDriver.o -o cgStackExecutable
./cgStackExecutable small.csv
