long pcount(unsigned long x) {
    long result = 0;
    while (x) {
        result += x & 1;
        x >>= 1;
    }
    return result;
}