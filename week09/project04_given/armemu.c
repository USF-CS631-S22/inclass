#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "armemu.h"

// Analysis functions

// Project04: Analysis struct init
void analysis_init(struct analysis_st *ap) {
    ap->i_count = 0;
    ap->dp_count = 0;
    ap->mem_count = 0;
    ap->b_count = 0;
    ap->b_taken = 0;
    ap->b_not_taken = 0;
}

// Project04: Print results of dynamic analysis
void analysis_print(struct analysis_st *ap) {
    printf("=== Analysis\n");
    printf("I_count       = %d\n", ap->i_count);
    printf("DP_count      = %d (%.2f%%)\n", ap->dp_count,
           ((double) ap->dp_count / (double) ap->i_count) * 100.0);
    printf("SDT_count     = %d (%.2f%%)\n", ap->mem_count,
           ((double) ap->mem_count / (double) ap->i_count) * 100.0);    
    printf("B_count       = %d (%.2f%%)\n", ap->b_count,
           ((double) ap->b_count / (double) ap->i_count) * 100.0);
    printf("B_taken       = %d (%.2f%%)\n", ap->b_taken,
               ((double) ap->b_taken / (double) ap->b_count) * 100.0);
    printf("B_not_taken   = %d (%.2f%%)\n", ap->b_not_taken,
               ((double) ap->b_not_taken / (double) ap->b_count) * 100.0);
}

// Project04: Print results of dynamic analysis and cache sim
void armemu_print(struct arm_state *asp) {
    if (asp->analyze) {
        analysis_print(&(asp->analysis));
    }

    if (asp->cache_sim) {
        cache_print((&asp->i_cache), "(I)");
        cache_print((&asp->d_cache), "(D)");
    }
}

void armemu_init(struct arm_state *asp, uint32_t *func,
                 uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3) {
    int i;

    // Zero out registers
    for (i = 0; i < NREGS; i += 1) {
        asp->regs[i] = 0;
    }

    // Zero out the CPSR
    asp->cpsr = 0;

    // Zero out the stack
    for (i = 0; i < STACK_SIZE; i += 1) {
        asp->stack[i] = 0;
    }

    // Initialize the Program Counter
    asp->regs[PC] = (uint32_t) func;

    // Initialize the Link Register to a sentinel value
    asp->regs[LR] = 0;

    // Initialize Stack Pointer to the logical bottom of the stack
    asp->regs[SP] = (uint32_t) &asp->stack[STACK_SIZE];

    // Initialize the first 4 arguments in emulated r0-r3
    asp->regs[0] = a0;
    asp->regs[1] = a1;
    asp->regs[2] = a2;
    asp->regs[3] = a3;

    // Project04: Initialize dynamic analysis
    analysis_init(&asp->analysis);
    
    // Project04: Initialize cache simulator
    cache_init(&asp->i_cache);
    cache_init(&asp->d_cache);
}


bool armemu_is_bx(uint32_t iw) {
    uint32_t bxcode;

    bxcode = (iw >> 4) & 0xFFFFFF;

    // 0x12fff1 == 0b000100101111111111110001
    return bxcode == 0x12fff1;   
}

void armemu_bx(struct arm_state *asp, uint32_t iw) {
    uint32_t rn = iw & 0b1111;

    // Project04: increment dynamic analysis
    asp->analysis.b_count += 1;
    asp->analysis.b_taken += 1;    

    asp->regs[PC] = asp->regs[rn];
}

bool armemu_is_add(uint32_t iw) {
    uint32_t dp_bits = (iw >> 26) & 0b11;
    uint32_t opcode = (iw >> 21) & 0b1111;

    return (dp_bits == 0b00) & (opcode == 0b0100);
}

void armemu_add(struct arm_state *asp, uint32_t iw) {
    uint32_t i_bit = (iw >> 25) & 0b1;
    uint32_t rn = (iw >> 16) & 0b1111;
    uint32_t rd = (iw >> 12) & 0b1111;
    uint32_t rm = iw & 0b1111;
    uint32_t imm = iw & 0b11111111;
    uint32_t oper2;

    // Project04: Increment analysis count
    asp->analysis.dp_count += 1;
    
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

    asp->analysis.i_count += 1;

    /* Project04: get instruction word from instruction cache
       instead of the PC pointer directly
       uint32_t iw = *((uint32_t *) asp->regs[PC]);
    */
    uint32_t iw = cache_lookup(&asp->i_cache, asp->regs[PC], false, 0);

    // Order matters: more constrained to least constrained
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
