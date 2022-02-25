#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_LEN 32
#define STR_LEN 4096

int max3_c(int a0, int a1, int a2);
int max3_s(int a0, int a1, int a2);

int find_max_c(int *array, int len);
int find_max_s(int *array, int len);

int fib_rec_c(int n);
int fib_rec_s(int n);

void stolower_c(char *s);
void stolower_s(char *s);

void strncat_c(char *dest, char *src, int n);
void strncat_s(char *dest, char *src, int n);


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

void max3_test(int a0, int a1, int a2) {
    int r;

    r = max3_c(a0, a1, a2);
    printf("max3_c(%d, %d, %d) = %d\n", a0, a1, a2, r);

    r = max3_s(a0, a1, a2);
    printf("max3_s(%d, %d, %d) = %d\n", a0, a1, a2, r);
    
}

void find_max_test(int array[], int len) {
    int r;
    char arrstr[4096];

    gen_array_str(array, len, arrstr);

    r = find_max_c(array, len);
    printf("find_max_c(%s, %d) = %d\n", arrstr, len, r);

    r = find_max_s(array, len);
    printf("find_max_s(%s, %d) = %d\n", arrstr, len, r);
}

void fib_rec_test(int n) {
    int r;

    r = fib_rec_c(n);
    printf("fib_rec_c(%d) = %d\n", n, r);

    r = fib_rec_s(n);
    printf("fib_rec_s(%d) = %d\n", n, r);
}

void stolower_test(char *s) {
    char s2[STR_LEN];

    strncpy(s2, s, STR_LEN - 1);
    stolower_c(s2);
    printf("stolower_c(%s) = %s\n", s, s2);

    strncpy(s2, s, STR_LEN - 1);
    stolower_s(s2);
    printf("stolower_s(%s) = %s\n", s, s2);
}

void strncat_test(char *dest, char *src, int n) {
    char s2[STR_LEN];

    strncpy(s2, dest, STR_LEN - 1);
    strncat_c(s2, src, n);
    printf("strncat_c(%s, %s, %d) = %s\n", dest, src, n, s2);

    strncpy(s2, dest, STR_LEN - 1);
    strncat_s(s2, src, n);
    printf("strncat_s(%s, %s, %d) = %s\n", dest, src, n, s2);
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

    if (strncmp(argv[1], "max3", CMD_LEN) == 0) {
        max3_test(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
    } else if (strncmp(argv[1], "find_max", CMD_LEN) == 0) {
        args_get_array(argv, a, &n);
        find_max_test(a, n);
    } else if (strncmp(argv[1], "fib_rec", CMD_LEN) == 0) {
        fib_rec_test(atoi(argv[2]));
    } else if (strncmp(argv[1], "stolower", CMD_LEN) == 0) {
        stolower_test(argv[2]);
    } else if (strncmp(argv[1], "strncat", CMD_LEN) == 0) {
        strncat_test(argv[2], argv[3], atoi(argv[4]));
    }

    return 0;
}
