ll ncr(int n,int r) {
    if (r == 0 || n == 0) return 1;
    return ncr(n - 1, r - 1) * n / r;
}
