#include <stdio.h>


int main(int argc, char **argv) {
    int x;
    char c;

    int *xp = &x;
    char *cp = &c;

    xp = xp + 1;
    cp = cp + 1;



    int x1 = 1;
    int y1 = 2;
    unsigned a = 3;
    unsigned b = 4;

    if (x1 > y1) {
        x1 = x1 + 1;
    }

    if (a > b) {
        a = a + 1;
    }



    x = x >> 2;
    a = a >> 2;

    return 0;
}
