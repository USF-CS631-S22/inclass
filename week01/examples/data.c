#include <stdio.h>
// stdlib.h is needed for malloc() and free()
// use the man command to learn more about C library functions
//
// $ man malloc
//
// Force a man section like this:
//
// $ man 3 printf

#include <stdlib.h>

// Recall data can live in three places: global, stack, heap

// x is global
int x;

int main(int argc, char *argv[]) {
    // y is a local variable and only lives for the execution of main
    int y;

    // zp is also a local variable, one word in size. It's type is a pointer to an int.
    int *zp;

    // Allocate space on the heap for one int (4 bytes on a 32-bit machine).
    zp = (int *) malloc(sizeof(int));

    x = 1;
    y = 2;
    // Derefrence the pointer so that we can assign 3 to the location in memory.
    *zp = 3;

    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("*zp = %d\n", *zp);

    return 0;
}
