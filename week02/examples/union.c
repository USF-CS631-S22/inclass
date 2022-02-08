#include <stdio.h>

union bar_u {
    int x;
    float y;
};

int main(int argc, char *argv[]) {
    union bar_u bar;


    bar.y = 2.3;
    bar.x = 1;

    printf("bar.x = %d\n", bar.x);
    printf("bar.y = %f\n", bar.y);

    return 0;
}
