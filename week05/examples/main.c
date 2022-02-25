#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_LEN 32
#define STR_LEN 4096


int sum_array_c(int *array, int len);
int sum_array_s(int *array, int len);
int sum_array2_s(int *array, int len);

int add4f_c(int a0, int a1, int a2, int a3);
int add4f_s(int a0, int a1, int a2, int a3);

int fact_c(int n);
int fact_s(int n);

int strlen_c(char *s);
int strlen_s(char *s);


void args_get_array(char **argv, int a[], int *n) {
    int i;
    
    *n = atoi(argv[2]);
    for (i = 0; i < *n; i++) {
        a[i] = atoi(argv[3 + i]);
    }
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

void sum_array_test(int array[], int len) {
    int r;
    char arrstr[4096];

    gen_array_str(array, len, arrstr);

    r = sum_array_c(array, len);
    printf("sum_array_c(%s, %d) = %d\n", arrstr, len, r);

    r = sum_array_s(array, len);
    printf("sum_array_s(%s, %d) = %d\n", arrstr, len, r);

    r = sum_array2_s(array, len);
    printf("sum_array2_s(%s, %d) = %d\n", arrstr, len, r);


}

void add4f_test(int a0, int a1, int a2, int a3) {
    int r;

    r = add4f_c(a0, a1, a2, a3);
    printf("add4f_c(%d, %d, %d, %d) = %d\n", a0, a1, a2, a3, r);

    r = add4f_s(a0, a1, a2, a3);
    printf("add4f_s(%d, %d, %d, %d) = %d\n", a0, a1, a2, a3, r);
    
}

void fact_test(int n) {
    int r;

    r = fact_c(n);
    printf("fact_c(%d) = %d\n", n, r);

    r = fact_s(n);
    printf("fact_s(%d) = %d\n", n, r);
}

void strlen_test(char *s) {
    int r;

    r = strlen_c(s);
    printf("strlen_c(%s) = %d\n", s, r);

    r = strlen_s(s);
    printf("strlen_s(%s) = %d\n", s, r);
}

int main(int argc, char **argv) {
    int n;
    int a[4096];

    if (argc == 1) {
        printf("usage: main <prog> [<arg1> ...]\n");
        exit(-1);
    }

    if (strncmp(argv[1], "sum_array", CMD_LEN) == 0) {
        args_get_array(argv, a, &n);
        sum_array_test(a, n);
    } else if (strncmp(argv[1], "add4f", CMD_LEN) == 0) {
        add4f_test(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    } else if (strncmp(argv[1], "fact", CMD_LEN) == 0) {
        fact_test(atoi(argv[2]));
    } else if (strncmp(argv[1], "strlen", CMD_LEN) == 0) {
        strlen_test(argv[2]);
    }

    return 0;
}
