#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_LEN 32

int add_c(int a0, int a1);
int add_s(int a0, int a1);

int add4_c(int a0, int a1, int a2, int a3);
int add4_s(int a0, int a1, int a2, int a3);

int quadratic_c(int x, int a, int b, int c);
int quadratic_s(int x, int a, int b, int c);

int min_c(int a, int b);
int min_s(int a, int b);

void add_test(int a0, int a1) {
    int r;

    r = add_c(a0, a1);
    printf("add_c(%d, %d) = %d\n", a0, a1, r);

    r = add_s(a0, a1);
    printf("add_s(%d, %d) = %d\n", a0, a1, r);
}

void add4_test(int a0, int a1, int a2, int a3) {
    int r;

    r = add4_c(a0, a1, a2, a3);
    printf("add4_c(%d, %d, %d, %d) = %d\n", a0, a1, a2, a3, r);

    r = add4_s(a0, a1, a2, a3);
    printf("add4_s(%d, %d, %d, %d) = %d\n", a0, a1, a2, a3, r);

}

void quadratic_test(int x, int a, int b, int c) {
    int r;

    r = quadratic_c(x, a, b, c);
    printf("quadratic_c(%d, %d, %d, %d) = %d\n", x, a, b, c, r);

    r = quadratic_s(x, a, b, c);
    printf("quadratic_s(%d, %d, %d, %d) = %d\n", x, a, b, c, r);
}


void min_test(int a0, int a1) {
    int r;

    r = min_c(a0, a1);
    printf("min_c(%d, %d) = %d\n", a0, a1, r);

    r = min_s(a0, a1);
    printf("min_s(%d, %d) = %d\n", a0, a1, r);
}

int main(int argc, char **argv) {

    if (strncmp(argv[1], "add", CMD_LEN) == 0) {
        add_test(atoi(argv[2]), atoi(argv[3]));
    } else if (strncmp(argv[1], "add4", CMD_LEN) == 0) {
        add4_test(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    } else if (strncmp(argv[1], "quadratic", CMD_LEN) == 0) {
        quadratic_test(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    } else if (strncmp(argv[1], "min", CMD_LEN) == 0) {
        min_test(atoi(argv[2]), atoi(argv[3]));
    } else {
        printf("Invalid function.\n");
    }
    
    return 0;
}
