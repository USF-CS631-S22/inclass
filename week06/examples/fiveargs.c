#include <stdio.h>


int foo(int a0, int a1, int a2, int a3, int a4, int a5) {
    return a0 + a1 + a2 + a3 + a4 + a5;
}

int main(int argc, char *argv[]) {
    int r;

    r = foo(1, 2, 3, 4, 5, 6);

    return r;
}
