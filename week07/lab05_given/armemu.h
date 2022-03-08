#define ARMEMU_DEBUG 0
#define MAX_INSTRUCTION_COUNT 1000000

#define NREGS 16
#define STACK_SIZE 4096
#define SP 13
#define LR 14
#define PC 15

/* The complete machine state */
struct arm_state {
    uint32_t regs[NREGS];
    uint32_t cpsr;
    uint8_t stack[STACK_SIZE];
};

/* Initialize an arm_state struct with a function pointer and arguments */
void armemu_init(struct arm_state *asp, uint32_t *fp,
                    uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3);
int armemu(struct arm_state *asp);
