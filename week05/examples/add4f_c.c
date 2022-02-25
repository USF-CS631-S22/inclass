int add2_c(int a0, int a1) {
    return a0 + a1;
}

int add4f_c(int a0, int a1, int a2, int a3) {
    int r1, r2;

    r1 = add2_c(a0, a1);
    r2 = add2_c(a2, a3);

    return r1 + r2;
}
