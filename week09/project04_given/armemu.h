#include <stdint.h>
#include <stdbool.h>


#define ARMEMU_DEBUG 0
#define MAX_INSTRUCTION_COUNT 1000000
#define MAX_ARRAY 1024

#define NREGS 16
#define STACK_SIZE 4096
#define SP 13
#define LR 14
#define PC 15

#define CPSR_N 31
#define CPSR_Z 30
#define CPSR_C 29
#define CPSR_V 28

#define CT_NONE 0
#define CT_DIRECT_MAPPED_1 1
#define CT_DIRECT_MAPPED_4 2
#define CT_SET_ASSOCIATIVE_1 3
#define CT_SET_ASSOCIATIVE_4 4
#define CACHE_MAX_SLOTS 4096
#define CACHE_MAX_BLOCK_SIZE 4

// Dynamic analysis structs

struct analysis_st {
    int i_count;
    int dp_count;
    int mem_count;
    int b_count;
    int b_taken;
    int b_not_taken;
};

// Cache simulation structs

struct cache_slot_st {
    uint32_t valid;
    uint32_t tag;
    uint32_t block[CACHE_MAX_BLOCK_SIZE];
    uint32_t timestamp;

};
struct cache_st {
    struct cache_slot_st slots[CACHE_MAX_SLOTS];
    int type;
    int size;
    int ways;
    int block_size;
    uint32_t index_mask;
    uint32_t index_bits;
    int refs;
    int hits;
    int misses;
    int misses_cold;
    int misses_hot;
    int slots_used;
};

// arm_state represents the state of the emulated ARM processor
struct arm_state {
    uint32_t regs[NREGS];
    uint32_t cpsr;
    uint8_t stack[STACK_SIZE];

    bool analyze;
    bool cache_sim;;
    bool verbose;

    struct analysis_st analysis;
    struct cache_st i_cache;
    struct cache_st d_cache;    
};


// Declare the emulation target functions
int quadratic_c(int x, int a, int b, int c);
int quadratic_s(int x, int a, int b, int c);

int max3_c(int a, int b, int c);
int max3_s(int a, int b, int c);

int find_max_c(int *array, int n);
int find_max_s(int *array, int n);

int fib_rec_c(int n);
int fib_rec_s(int n);

int get_bitseq_c(int n, int start, int end);
int get_bitseq_s(int n, int start, int end);

void stolower_c(char *s);
void stolower_s(char *s);

void strncat_c(char *dst, char *src, int n);
void strncat_s(char *dst, char *src, int n);

int matches_c(char *s1, char *s2);
int matches_s(char *s1, char *s2);

void merge_sort_c(int a[], int start, int end, int aux[]);
void merge_sort_s(int a[], int start, int end, int aux[]);

// Public functions for armemu and cache
void armemu_init(struct arm_state *asp, uint32_t *fp,
                 uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3);
int armemu(struct arm_state *asp);
void armemu_print(struct arm_state *asp);
void cache_init(struct cache_st *csp);
uint32_t cache_lookup(struct cache_st *csp, uint32_t addr, bool write, uint32_t value);
void cache_print(struct cache_st *csp, char *name);

// Simple logging
void verbose(char *fmt, ...);
