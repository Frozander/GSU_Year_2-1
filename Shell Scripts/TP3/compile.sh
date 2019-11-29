gcc mylib.c -fpic -c -o mylib.o
gcc mylib.o -shared -o libmy.so
gcc main.c -o main -L/mnt/c/Users/batub/Documents/GSU/Shell\ Scripts/TP3/ -Wl,-rpath=/mnt/c/Users/batub/Documents/GSU/Shell\ Scripts/TP3/ -lmy