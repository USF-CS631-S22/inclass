#include <stdio.h>

int mul_c(int a0, int a1, int a2);
int mul_s(int a0, int a1, int a2);

int main(int argc, char *argv[]) {
    int r;

    r = mul_c(2, 3, 4);
    printf("mul_c(2, 3, 4) = %d\n", r);
    r = mul_s(2, 3, 4);
    printf("mul_s(2, 3, 4) = %d\n", r);

    return 0;
}
