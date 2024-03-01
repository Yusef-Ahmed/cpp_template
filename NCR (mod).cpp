const int N = 1000+5;
int fac[N];

int fp(int b, int p) {
    if (p == 0) return 1;
    int ans = fp(1LL * b * b % mod, p / 2);
    if (p % 2) return 1LL * ans * b % mod;
    return ans;
}

int ncr(int n,int r) { // stars & bars
    return 1LL * fac[n] * fp(1LL * fac[r] * fac[n - r] % mod, mod - 2) % mod;
}

void pre() {
    fac[0] = 1;
    for (int i = 1; i < (int) N; i++) {
        fac[i] = 1LL * fac[i - 1] * i % mod;
    }
}
