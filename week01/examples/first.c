// C comments, // to end of line or /* text, supports multple lines */

// Include files allow us to access library functions and related type
// declarations. Technically, #include is supported by the C preprocessor
// and just does a file insertion, recursively. You can see the result
// of the C preprocessor phase doing this:
//
// gcc -E file.c > file.cp
//
// Then look at file.cp to see the result of the C preprocessor.

#include <stdio.h>

// In C we have to main entities: data and functions

// Data can live in one of three places: global, stack, heap

// x is global
int x;


// All code in C must reside in functions. Functions consist of statements and expression.

int plus_one(int x) {
    // Add 1 to the argument x and return this value.
    return x + 1;
}

// The main function is special, it is where execution begins when you start the program.

int main(int argc, char *argv[]) {
    // Update global x
    x = 2;

    x = plus_one(x);

    printf("x = %d\n", x);

    return 0;
}
