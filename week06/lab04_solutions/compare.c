#include <stdio.h>


int main(int argc, char *argv[]) {
    unsigned x, y;

    x = 1;
    y = 2;

    if (x <= y) {
        x = x + 100;
    }

    return x;
}
