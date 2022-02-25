#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv) {
    uint32_t x = 0xFFAA1122;
    uint32_t *xp;
    uint8_t byte;

    xp = &x;

    byte = *((uint8_t *) xp);

    printf("Byte value at address %p = %X\n", xp, byte);
    // if byte == 0x22, then we are little endian

    return 0;
}
