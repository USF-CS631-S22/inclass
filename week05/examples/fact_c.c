int fact_c(int n) {
    int r;

    if (n == 0) {
        r = 1;
    } else {
        r = fact_c(n - 1) * n;
    }

    return r;    
}
