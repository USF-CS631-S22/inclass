int fib_rec_c(int n)
{
    int r;
    
    if (n == 0) {
        r = 0;
    } else if (n == 1) {
        r = 1;
    } else {
        r = fib_rec_c(n - 1) + fib_rec_c(n - 2);
    }

    return r;
}

