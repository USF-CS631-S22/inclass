#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    uint32_t uv1;
    uint32_t uv2;
    int32_t v1;
    int32_t v2;

    uint32_t result;

    v1 = 2;
    v2 = 3;

    result = v1 - v2;

    printf("result (d) = %d\n", result);
    printf("result (u) = %u\n", result);

    v1 = -1;
    v2 = 2;
    uv1 = v1;
    uv2 = v2;

    printf("uv1 = %u\n", uv1);
    printf("uv2 = %u\n", uv2);    

    if (v1 > v2) {
        printf("[1] %d > %d\n", v1, v2);
    }

    if (uv1 > uv2) {
        printf("[2] %u > %u\n", uv1, uv2);
    } 


    v1 >> 2;
    uv1 >> 3;

    return 0;
}
