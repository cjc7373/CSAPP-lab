long q(long x) {
    long y = x + 1;
    long a[x];
    a[x - 1] = 1;
    return y;
}

long p(long x, long *dest) {
    long y = q(x + 1);
    *dest = y;
}
