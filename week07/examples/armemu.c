#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int add2_s(int a0, int a1);

#define NREGS 16
#define STACK_SIZE 1024
#define SP 13
#define LR 14
#define PC 15


struct arm_state {
    uint32_t regs[NREGS];
    uint32_t cpsr;
    uint8_t stack[STACK_SIZE];
};


void armemu_init(struct arm_state *asp, uint32_t *funcp,
                 uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3) {

    /* Zero out registers */
    for (int i = 0; i < NREGS; i++) {
        asp->regs[i] = 0;
    }

    /* Zero out cpsr */
    asp->cpsr = 0;

    /* Zero out the stack */
    for (int i = 0; i < STACK_SIZE; i++) {
        asp->stack[i] = 0;
    }

    /* Initialize PC */
    asp->regs[PC] = (uint32_t) funcp;

    /* Initialize LR */
    asp->regs[LR] = 0;

    /* Initialize SP */
    asp->regs[SP] = (uint32_t) &asp->stack[STACK_SIZE];

    /* Initialize the first 4 args */
    asp->regs[0] = a0;
    asp->regs[1] = a1;
    asp->regs[2] = a2;
    asp->regs[3] = a3;
}

void armemu_print_state(struct arm_state *asp) {
    uint32_t iw;

    iw = *((uint32_t *) asp->regs[PC]);
    printf("iw = %x\n", iw);
    for (int i = 0; i < NREGS; i++) {
        printf("regs[%d] = %d (%x)\n", i, asp->regs[i], asp->regs[i]);
    }
    printf("cpsr = %x\n", asp->cpsr);
    printf("\n");
}

bool armemu_is_bx(uint32_t iw) {
    return ((iw >> 4) & 0xFFFFFF) == 0x12FFF1;
}

void armemu_bx(struct arm_state *asp, uint32_t iw) {
    uint32_t rn;

    rn = iw & 0b1111;

    asp->regs[PC] = asp->regs[rn];
}

bool armemu_is_add(uint32_t iw) {
    uint32_t dp_bits;
    uint32_t opcode;

    dp_bits = (iw >> 26) & 0b11;
    opcode = (iw >> 21) & 0b1111;

    return (dp_bits == 0) && (opcode == 0b0100);
}

void armemu_add(struct arm_state *asp, uint32_t iw) {
    uint32_t dp_bits;
    uint32_t i_bit;
    uint32_t opcode;
    uint32_t rn;
    uint32_t rd;
    uint32_t rm;
    uint32_t imm;
    uint32_t oper2;


    dp_bits = (iw >> 26) & 0b11;
    i_bit = (iw >> 25) & 0b1;
    opcode = (iw >> 21) & 0b1111;
    rn = (iw >> 16) & 0b1111;
    rd = (iw >> 12) & 0b1111;
    rm = iw & 0b1111;
    imm = iw & 0b11111111;

    if (!i_bit) {
        oper2 = asp->regs[rm];
    } else {
        oper2 = imm;
    }

    asp->regs[rd] = asp->regs[rn] + oper2;

    if (rd != PC) {
        asp->regs[PC] = asp->regs[PC] + 4;
    }
}


void armemu_one(struct arm_state *asp) {
    uint32_t iw;

    iw = *((uint32_t *) asp->regs[PC]);

    if (armemu_is_bx(iw)) {
        armemu_bx(asp, iw);
    } else if (armemu_is_add(iw)) {
        armemu_add(asp, iw);
    } else {
        printf("armemu_one() invalid instruction\n");
        exit(-1);
    }    
}

int armemu(struct arm_state *asp) {

    while (asp->regs[PC] != 0) {
        armemu_print_state(asp);
        armemu_one(asp);
    }
    
    return asp->regs[0];
}


int main(int argc, char *argv[]) {
    struct arm_state state;
    int r;
    
    armemu_init(&state, (uint32_t *) add2_s, 1, 2, 0, 0);
    r = armemu(&state);
    printf("add2_e(1, 2) = %d\n", r);

    return 0;
}
