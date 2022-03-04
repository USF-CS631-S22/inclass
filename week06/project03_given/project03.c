#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define CMD_LEN 32
#define STR_LEN 4096

char *substr_c(char *s1, char *s2);
char *substr_s(char *s1, char *s2);

int matches_c(char *s1, char *s2);
int matches_s(char *s1, char *s2);

void merge_c(int a[], int i, int j, int aux[]);
void merge_s(int a[], int i, int j, int aux[]);

void merge_sort_c(int a[], int i, int j, int aux[]);
void merge_sort_s(int a[], int i, int j, int aux[]);

uint32_t get_bitseq_c(uint32_t num, int start, int end);
uint32_t get_bitseq_s(uint32_t num, int start, int end);

uint32_t get_bitseq_signed_c(uint32_t num, int start, int end);
uint32_t get_bitseq_signed_s(uint32_t num, int start, int end);

void gen_array_str(int array[], int len, char *outstr) {
    int i;
    char numstr[STR_LEN];

    *outstr = '\0';
    strncat(outstr, "[", STR_LEN);

    for (i = 0; i < len; i += 1) {
        snprintf(numstr, STR_LEN, "%d", array[i]);
        strncat(outstr, numstr, STR_LEN);
        if ((i + 1) != len) {
            strncat(outstr, ",", STR_LEN);
        }
    }
    strncat(outstr, "]", STR_LEN);
}

char *substr_test(char *s1, char *s2) {
    char *p;
    int found, index;

    found = 0;
    index = 0;
    p = substr_c(s1, s2);
    if (p !=  0) {
        found = 1;
        index = (int) (p - s1);
    }
    printf("substr_c(%s, %s) = %d %d\n", s1, s2, found, index);

    found = 0;
    index = 0;
    p = substr_s(s1, s2);
    if (p != 0) {
        found = 1;
        index = (int) (p - s1);
    }
    printf("substr_s(%s, %s) = %d %d\n", s1, s2, found, index);
}

void matches_test(char *s1, char *s2) {
    int r;

    r = matches_c(s1, s2);
    printf("matches_c(%s, %s) = %d\n", s1, s2, r);

    r = matches_s(s1, s2);
    printf("matches_s(%s, %s) = %d\n", s1, s2, r);
}

void merge_test(int array[], int len) {
    int i;
    char arrstr1[4096];
    char arrstr2[4096];
    int acopy[4096];
    int aux[4096];

    for (i = 0; i < len; i++) {
        acopy[i] = array[i];
    }   
    gen_array_str(acopy, len, arrstr1);
    merge_c(acopy, 0, len - 1, aux);
    gen_array_str(acopy, len, arrstr2);
    printf("merge_c(%s, 0, %d, aux[]) = %s\n", arrstr1, len, arrstr2);

    for (i = 0; i < len; i++) {
        acopy[i] = array[i];
    }
    gen_array_str(acopy, len, arrstr1);
    merge_s(acopy, 0, len - 1, aux);
    gen_array_str(acopy, len, arrstr2);
    printf("merge_s(%s, 0, %d, aux[]) = %s\n", arrstr1, len, arrstr2);
}

void merge_sort_test(int array[], int len) {
    int i;
    char arrstr1[4096];
    char arrstr2[4096];
    int acopy[4096];
    int aux[4096];
    for (i = 0; i < len; i++) {
        acopy[i] = array[i];
    }   
    gen_array_str(acopy, len, arrstr1);
    merge_sort_c(acopy, 0, len - 1, aux);
    gen_array_str(acopy, len, arrstr2);
    printf("merge_sort_c(%s, 0, %d, aux[]) = %s\n", arrstr1, len, arrstr2);

    for (i = 0; i < len; i++) {
        acopy[i] = array[i];
    }
    gen_array_str(acopy, len, arrstr1);
    merge_sort_s(acopy, 0, len - 1, aux);
    gen_array_str(acopy, len, arrstr2);
    printf("merge_sort_s(%s, 0, %d, aux[]) = %s\n", arrstr1, len, arrstr2);
}


void get_bitseq_test(uint32_t num, int start, int end) {
    uint32_t r;

    r = get_bitseq_c(num, start, end);
    printf("get_bitseq_c(%u, %d, %d) = %u\n", num, start, end, r);

    r = get_bitseq_s(num, start, end);
    printf("get_bitseq_s(%u, %d, %d) = %u\n", num, start, end, r);    
}

void get_bitseq_signed_test(uint32_t num, int start, int end) {
    int32_t r;

    r = get_bitseq_signed_c(num, start, end);
    printf("get_bitseq_signed_c(%u, %d, %d) = %d\n", num, start, end, r);

    r = get_bitseq_signed_s(num, start, end);
    printf("get_bitseq_signed_s(%u, %d, %d) = %d\n", num, start, end, r);    
}


void args_get_array(char **argv, int a[], int *n) {
    int i;
    
    *n = atoi(argv[2]);
    for (i = 0; i < *n; i++) {
        a[i] = atoi(argv[3 + i]);
    }
}

int main(int argc, char **argv) {
    int n;
    int a[4096];

    if (argc == 1) {
        printf("usage: lab04 <prog> [<arg1> ...]\n");
        exit(-1);
    }

    if (strncmp(argv[1], "substr", CMD_LEN) == 0) {
        substr_test(argv[2], argv[3]);
    } else if (strncmp(argv[1], "matches", CMD_LEN) == 0) {
        matches_test(argv[2], argv[3]);
    } else if (strncmp(argv[1], "merge", CMD_LEN) == 0) {
        args_get_array(argv, a, &n);
        merge_test(a, n);
    } else if (strncmp(argv[1], "merge_sort", CMD_LEN) == 0) {
        args_get_array(argv, a, &n);
        merge_sort_test(a, n);
    } else if (strncmp(argv[1], "get_bitseq", CMD_LEN) == 0) {
        get_bitseq_test(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    } else if (strncmp(argv[1], "get_bitseq_signed", CMD_LEN) == 0) {
        get_bitseq_signed_test(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    }

    return 0;
}
