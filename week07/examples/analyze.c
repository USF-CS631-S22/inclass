#include <stdio.h>
#include <stdint.h>

int add2_s(int a0, int a1);

void analyze(uint32_t *pc) {
    uint32_t iw;

    iw = *pc;

    printf("pc = %X\n", (uint32_t) pc);
    printf("iw = %X\n", iw);

    uint32_t cond;
    uint32_t dp_bits;
    uint32_t i_bit;
    uint32_t opcode;
    uint32_t rn;
    uint32_t rd;
    uint32_t rm;
    uint32_t imm;

    cond = (iw >> 28) & 0b1111;
    dp_bits = (iw >> 26) & 0b11;
    i_bit = (iw >> 25) & 0b1;
    opcode = (iw >> 21) & 0b1111;
    rn = (iw >> 16) & 0b1111;
    rd = (iw >> 12) & 0b1111;
    rm = iw & 0b1111;
    imm = iw & 0b11111111;

    printf("cond = %X\n", cond);
    printf("dp_bits = %X\n", dp_bits);
    printf("i_bit = %X\n", i_bit);
    printf("opcode = %X\n", opcode);
    printf("rn = %d\n", rn);
    printf("rd = %d\n", rd);
    printf("rm = %d\n", rm);
    printf("imm = %d\n", imm);

    printf("\n");
}


int main(int argc, char *argv[]) {
    int r;

    r = add2_s(1, 2);
    printf("add2_s(1, 2) = %d\n", r);

    uint32_t *pc;
    pc = (uint32_t *) add2_s;

    analyze(pc);

    pc = pc + 1;

    analyze(pc);

    pc = pc + 1;

    analyze(pc);
    
    return 0;
}
