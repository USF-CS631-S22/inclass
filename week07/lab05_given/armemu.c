#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "armemu.h"

void armemu_init(struct arm_state *asp, uint32_t *fp,
                 uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3) {
    int i;
    
    /* Zero out registers */
    for (i = 0; i < NREGS; i += 1) {
        asp->regs[i] = 0;
    }

    /* Zero out the cpsr */
    asp->cpsr = 0;

    /* Zero out the stack */
    for (i = 0; i < STACK_SIZE; i += 1) {
        asp->stack[i] = 0;
    }

    /* Initialize the PC */
    asp->regs[PC] = (uint32_t) fp;

    /* Initialize LR */
    asp->regs[LR] = 0;

    /* Initialize SP */
    asp->regs[SP] = (uint32_t) &asp->stack[STACK_SIZE];

    /* Initialize the first 4 arguments */
    asp->regs[0] = a0;
    asp->regs[1] = a1;
    asp->regs[2] = a2;
    asp->regs[3] = a3;
}


bool armemu_is_bx(uint32_t iw) {
    uint32_t bxcode;

    bxcode = (iw >> 4) & 0xFFFFFF;

    /* 0x12fff1 = 0b000100101111111111110001 */
    return bxcode == 0x12fff1;   
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

    return (dp_bits == 0b00) & (opcode == 0b0100);
}

void armemu_add(struct arm_state *asp, uint32_t iw) {
    uint32_t i_bit;
    uint32_t rn;
    uint32_t rd;
    uint32_t rm;
    uint32_t imm;
    uint32_t oper2;
    
    i_bit = (iw >> 25) & 0b1;
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

    /* Order matters: more constrained to least constrained */
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
        armemu_one(asp);
    }
    
    return (int) asp->regs[0];
}
