#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "armemu.h"

#define STR_LEN 4096

extern bool g_verbose;

void copy_array(int *dst, int *src, int len) {
    for (int i = 0; i < len; i++) {
        dst[i] = src[i];
    }
}

void print_array(char *prefix, int *arr, int len) {
    printf("%s", prefix);
    for (int i = 0; i < len; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");
}

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
    strncat(outstr, "]",STR_LEN);
}

void quadratic_test(int start_arg, char **argv, struct arm_state *state) {
    int r;
    int x = atoi(argv[start_arg]);
    int a = atoi(argv[start_arg + 1]);
    int b = atoi(argv[start_arg + 2]);
    int c = atoi(argv[start_arg + 3]);

    r = quadratic_c(x, a, b, c);
    printf("quadratic_c(%d, %d, %d, %d) = %d\n", x, a, b, c, r);

    r = quadratic_s(x, a, b, c);
    printf("quadratic_s(%d, %d, %d, %d) = %d\n", x, a, b, c, r);

    armemu_init(state, (uint32_t *) quadratic_s, x, a, b, c);
    r = armemu(state);
    printf("quadratic_e(%d, %d, %d, %d) = %d\n", x, a, b, c, r);
}

void max3_test(int start_arg, char **argv, struct arm_state *state) {
    int r;
    int a = atoi(argv[start_arg]);
    int b = atoi(argv[start_arg + 1]);
    int c = atoi(argv[start_arg + 2]);

    r = max3_c(a, b, c);
    printf("max3_c(%d, %d, %d) = %d\n", a, b, c, r);

    r = max3_s(a, b, c);
    printf("max3_s(%d, %d, %d) = %d\n", a, b, c, r);

    armemu_init(state, (uint32_t *) max3_s, a, b, c, 0);
    r = armemu(state);
    printf("max3_e(%d, %d, %d) = %d\n", a, b, c, r);

}

void find_max_test(int start_arg, int argc, char **argv, struct arm_state *state) {
    int array[1024];
    int len = 0;
    int r;
    char arrstr[4096];

    for (int i = 0; i < argc - start_arg; i++) {
        array[i] = atoi(argv[i + start_arg]);
        len++;
    }

    gen_array_str(array, len, arrstr);

    r = find_max_c(array, len);
    printf("find_max_c(%s, %d) = %d\n", arrstr, len, r);

    r = find_max_s(array, len);
    printf("find_max_s(%s, %d) = %d\n", arrstr, len, r);

    armemu_init(state, (uint32_t *) find_max_s,
                (uint32_t) array, (uint32_t) len, 0, 0);
    r = armemu(state);
    printf("find_max_e(%s, %d) = %d\n", arrstr, len, r);
}

void fib_rec_test(int start_arg, char **argv, struct arm_state *state) {
    int r;
    int n = atoi(argv[start_arg]);

    r = fib_rec_c(n);
    printf("fib_rec_c(%d) = %d\n", n, r);

    r = fib_rec_s(n);
    printf("fib_rec_s(%d) = %d\n", n, r);

    armemu_init(state, (uint32_t*) fib_rec_s, n, 0, 0, 0);
    r = armemu(state);
    printf("fib_rec_e(%d) = %d\n", n, r);
}

void get_bitseq_test(int start_arg, char **argv, struct arm_state *state) {
    int r;
    int n = atoi(argv[start_arg]);
    int start = atoi(argv[start_arg + 1]);
    int end = atoi(argv[start_arg + 2]);

    r = get_bitseq_c(n, start, end);
    printf("get_bitseq_c(%d, %d, %d) = %d\n", n, start, end, r);

    r = get_bitseq_s(n, start, end);
    printf("get_bitseq_s(%d, %d, %d) = %d\n", n, start, end, r);
    
    armemu_init(state, (uint32_t *) get_bitseq_s, n, start, end, 0);
    r = armemu(state);
    printf("get_bitseq_e(%d, %d, %d) = %d\n", n, start, end, r);
}

void stolower_test(int start_arg, char **argv, struct arm_state *state) {
    char s_copy[STR_LEN];
    char s[STR_LEN];
    strncpy(s_copy, argv[start_arg], STR_LEN - 1);
    
    strncpy(s, s_copy, STR_LEN - 1);
    stolower_c(s);
    printf("stolower_c(%s) = %s\n", s_copy, s);

    strncpy(s, s_copy, STR_LEN - 1);
    stolower_s(s);
    printf("stolower_s(%s) = %s\n", s_copy, s);

    strncpy(s, s_copy, STR_LEN - 1);
    armemu_init(state, (uint32_t *) stolower_s, (uint32_t) s, 0, 0, 0);
    armemu(state);
    printf("stolower_e(%s) = %s\n", s_copy, s);
}

void strncat_test(int start_arg, char **argv, struct arm_state *state) {
    char dst_copy[STR_LEN];
    char dst[STR_LEN];
    char src[STR_LEN];
    int n; 

    strncpy(dst_copy, argv[start_arg], STR_LEN - 1);
    strncpy(src, argv[start_arg + 1], STR_LEN - 1);
    n = atoi(argv[start_arg + 2]);
    n = (n >= (STR_LEN - 1)) ? (STR_LEN - 1) : n;

    strncpy(dst, dst_copy, STR_LEN - 1);
    strncat_c(dst, src, n);
    printf("strncat_c(%s, %s, %d) = %s\n", dst_copy, src, n, dst);

    strncpy(dst, dst_copy, STR_LEN - 1);
    strncat_s(dst, src, n);
    printf("strncat_s(%s, %s, %d) = %s\n", dst_copy, src, n, dst);

    strncpy(dst, dst_copy, STR_LEN - 1);
    armemu_init(state, (uint32_t*) strncat_s, 
                (uint32_t) dst, (uint32_t) src, (uint32_t) n, 0);
    armemu(state);
    printf("strncat_e(%s, %s, %d) = %s\n", dst_copy, src, n, dst);
}

void matches_test(int start_arg, char **argv, struct arm_state *state) {
    char *s1 = argv[start_arg];
    char *s2 = argv[start_arg + 1];
    int r;

    r = matches_c(s1, s2);
    printf("matches_c(%s, %s) = %d\n", s1, s2, r);

    r = matches_s(s1, s2);
    printf("matches_s(%s, %s) = %d\n", s1, s2, r); 

    armemu_init(state, (uint32_t*) matches_s, (uint32_t) s1, (uint32_t) s2, 0, 0);
    r = armemu(state);
    printf("matches_e(%s, %s) = %d\n", s1, s2, r); 
}

void merge_sort_test(int start_arg, int argc, char **argv, struct arm_state *state) {
    int aux[MAX_ARRAY];
    int a_copy[MAX_ARRAY];
    int a[MAX_ARRAY] = {0,};
    int len = 0;

    for (int i = 0; i < argc - start_arg; i++) {
        a_copy[i] = atoi(argv[i + start_arg]);
        len++;
    }

    for (int i = 0; i < len; i++) {
        aux[i] = 0;
    }
    copy_array(a, a_copy, len);
    print_array("a[] =", a, len);
    print_array("aux[] =", aux, len);
    merge_sort_c(a, 0, len - 1, aux);
    printf("merge_sort_c(a, 0, %d, aux)\n", len - 1);
    print_array("a[] =", a, len);

    for (int i = 0; i < len; i++) {
        aux[i] = 0;
    }
    copy_array(a, a_copy, len);
    print_array("a[] =", a, len);
    print_array("aux[] =", aux, len);
    merge_sort_s(a, 0, len - 1, aux);
    printf("merge_sort_c(a, 0, %d, aux)\n", len - 1);
    print_array("a[] =", a, len);

    for (int i = 0; i < len; i++) {
        aux[i] = 0;
    }
    copy_array(a, a_copy, len);
    print_array("a[] =", a, len);
    print_array("aux[] =", aux, len);
    armemu_init(state, (uint32_t*) merge_sort_s, (uint32_t) a, 0, len - 1, (uint32_t) aux);
    armemu(state);
    printf("merge_sort_e(a, 0, %d, aux)\n", len - 1);
    print_array("a[] =", a, len);
}

int parse_params(int argc, char **argv, struct arm_state *asp) {
    // Parse optional command line parameters which must precede
    // the name of the emulated program and its parameters
    asp->analyze = false;
    asp->verbose = false;
    asp->cache_sim = false;
    asp->i_cache.type = CT_NONE;
    asp->d_cache.type = CT_NONE;    
    int i;
    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            // Return the index of the first non-optional parameter,
            // which is the name of the emulated program
            break;
        } else if (!strcmp(argv[i], "-a")) {
            asp->analyze = true;
        } else if (!strcmp(argv[i], "-dm1")) {
            asp->cache_sim = true;
            asp->i_cache.type = CT_DIRECT_MAPPED_1;
            asp->i_cache.size = atoi(argv[i + 1]);
            asp->d_cache.type = CT_DIRECT_MAPPED_1;
            asp->d_cache.size = atoi(argv[i + 1]);
            i++;
        } else if (!strcmp(argv[i], "-dm4")) {
            asp->cache_sim = true;
            asp->i_cache.type = CT_DIRECT_MAPPED_4;
            asp->i_cache.size = atoi(argv[i + 1]);
            asp->d_cache.type = CT_DIRECT_MAPPED_4;
            asp->d_cache.size = atoi(argv[i + 1]);
            i++;
        } else if (!strcmp(argv[i], "-sa1")) {
            asp->cache_sim = true;
            asp->i_cache.type = CT_SET_ASSOCIATIVE_1;
            asp->i_cache.size = atoi(argv[i + 1]);
            asp->d_cache.type = CT_SET_ASSOCIATIVE_1;
            asp->d_cache.size = atoi(argv[i + 1]);
            i++;
        } else if (!strcmp(argv[i], "-sa4")) {
            asp->cache_sim = true;
            asp->i_cache.type = CT_SET_ASSOCIATIVE_4;
            asp->i_cache.size = atoi(argv[i + 1]);
            asp->d_cache.type = CT_SET_ASSOCIATIVE_4;
            asp->d_cache.size = atoi(argv[i + 1]);
            i++;
        } else if (!strcmp(argv[i], "-v")) {
            g_verbose = true;
        }
    }
    return i;
}

void usage() {
    printf("usage: project04 <prog> [<arg1> ...]\n");
    exit(-1);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        usage();
    }

    struct arm_state state;
    int i = parse_params(argc, argv, &state);
    
    if (!strcmp(argv[i], "quadratic")) {
        quadratic_test(i + 1, argv, &state);
    } else if (!strcmp(argv[i], "max3")) {
        max3_test(i + 1, argv, &state);
    } else if (!strcmp(argv[i], "find_max")) {
        find_max_test(i + 1, argc, argv, &state);
    } else if (!strcmp(argv[i], "fib_rec")) {
        fib_rec_test(i + 1, argv, &state);
    } else if (!strcmp(argv[i], "stolower")) {
        stolower_test(i + 1, argv, &state);
    } else if (!strcmp(argv[i], "strncat")) {
        strncat_test(i + 1, argv, &state);
    } else if (!strcmp(argv[i], "get_bitseq")) {
        get_bitseq_test(i + 1, argv, &state);
    } else if (!strcmp(argv[i], "matches")) {
        matches_test(i + 1, argv, &state);
    } else if (!strcmp(argv[i], "merge_sort")) {
        merge_sort_test(i + 1, argc, argv, &state);
    } else {
        usage();
    }

    armemu_print(&state);

    return 0;
}
