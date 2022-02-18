#include <stdbool.h>
#include <stdio.h>
 
bool is_bin_char(char c) {
    return (c == '0' || c == '1');
}

bool is_dec_char(char c) {
    return (c >= '0') && (c <= '9');
}

bool is_lit(bool (*is_valid_char)(char), char c) {
    return is_valid_char(c);
}

int main(int argc, char *argv[]) {
    bool b;

    b = is_lit(is_bin_char, '1');

    printf("b = %d\n", b);    

    b = is_lit(is_dec_char, '3');

    printf("b = %d\n", b);    

    return 0;
}
