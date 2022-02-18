#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    uint32_t v1;
    uint32_t v2;
    uint32_t result;

    v1 = 2;
    v2 = 3;

    result = v1 - v2;

    printf("result (d) = %d\n", result);
    printf("result (u) = %u\n", result);

    return 0;
}
