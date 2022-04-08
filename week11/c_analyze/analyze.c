#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/* Test programs to analyze */


int quadratic_s(int x, int a, int b, int c);
int sum_array_s(int *array, int len);
int find_max_s(int *array, int len);
int fact_s(int n);
int fib_rec_s(int n);
int stolower_s(char *s1, char *s2);


/* Analyze struct */

struct analyze_st {
	int inst_count;
	int dp_count;
	int mem_count;
	int b_count;
    int bcc_count;
    int bl_count;
	int mul_count;
	int bx_count;
};

void analyze_init(struct analyze_st *ap) {
	ap->inst_count = 0;
	ap->dp_count = 0;
	ap->mem_count = 0;
	ap->b_count = 0;
	ap->bcc_count = 0;
	ap->bl_count = 0;
	ap->mul_count = 0;
	ap->bx_count = 0;
}

void analyze_print(struct analyze_st *ap, char *name) {
	printf("[Instruction Analysis: %s]\n", name);
	printf("Data Processing    : %d\n", ap->dp_count);
	printf("Multiply           : %d\n", ap->mul_count);
	printf("Memory             : %d\n", ap->mem_count);
	printf("B                  : %d\n", ap->b_count);
	printf("BCC                : %d\n", ap->bcc_count);
	printf("BL                 : %d\n", ap->bl_count);
	printf("BX                 : %d\n", ap->bx_count);
	printf("--------------------\n");
	printf("Total              : %d\n", ap->inst_count);	
}

void analyze_code(struct analyze_st *ap, uint32_t *code) {
	uint32_t *ip = code;
	uint32_t iw;
	uint32_t bits31_28;
	uint32_t bits27_26;
	uint32_t bits27_25;
	uint32_t bit24;
	uint32_t bits27_22;
	uint32_t bits7_4;
	uint32_t bits27_4;

	while (true) {
		iw = *ip;

		if (iw == 0xE2800000) {
		    /* Check for end marker: add r0, r0, #0 */
			break;
		}

        bits31_28 = (iw >> 28) & 0b1111;
		bits27_26 = (iw >> 26) & 0b11;
		bits27_25 = (iw >> 25) & 0b111;
		bits27_22 = (iw >> 22) & 0b111111;
		bit24     = (iw >> 24) & 0b1;
		bits7_4   = (iw >> 4) & 0b1111;
		bits27_4  = (iw >> 4) & 0xFFFFFF;
		
		if (bits27_4 == 0x12FFF1) {
			ap->bx_count += 1;
		} else if (bits27_22 == 0b000000 && bits7_4 == 0b1001) {
			ap->mul_count += 1;
		} else if (bits27_25 == 0b101 && bit24 == 0 
		           && bits31_28 == 0b1110) {
			ap->b_count += 1;
		} else if (bits27_25 == 0b101 && bit24 == 0
		           && bits31_28 != 0b1110) {
			ap->bcc_count += 1;
		} else if (bits27_25 == 0b101 && bit24 == 1
		           && bits31_28 == 0b1110) {
			ap->bl_count += 1;
		} else if (bits27_26 == 0b01) {
			ap->mem_count += 1;
		} else if (bits27_26 == 0b00) {
			ap->dp_count += 1;
		} else {
			printf("analyze: unrecogized instruction - ignoring\n");
			continue;
		}

		ap->inst_count += 1;
		ip += 1;
	}
}

int main(int argc, char **argv) {
	struct analyze_st analyze;

	analyze_init(&analyze);
	analyze_code(&analyze, (uint32_t *) quadratic_s);
	analyze_print(&analyze, "quadratic_s");
	printf("\n");

	analyze_init(&analyze);
	analyze_code(&analyze, (uint32_t *) sum_array_s);
	analyze_print(&analyze, "sum_array_s");
	printf("\n");

	analyze_init(&analyze);
	analyze_code(&analyze, (uint32_t *) find_max_s);
	analyze_print(&analyze, "find_max_s");
	printf("\n");

	analyze_init(&analyze);
	analyze_code(&analyze, (uint32_t *) fact_s);
	analyze_print(&analyze, "fact_s");
	printf("\n");

	analyze_init(&analyze);
	analyze_code(&analyze, (uint32_t *) fib_rec_s);
	analyze_print(&analyze, "fib_rec_s");
	printf("\n");

	analyze_init(&analyze);
	analyze_code(&analyze, (uint32_t *) stolower_s);
	analyze_print(&analyze, "stolower_s");
	printf("\n");

	return 0;
}
