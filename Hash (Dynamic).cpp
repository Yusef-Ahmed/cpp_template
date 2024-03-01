const int mod = 1e9+7, oo = 0x3f3f3f3f, N = 1e5+9,
LOG = 18, P1 = 31, P2 = 37;

int pw1[N], pw2[N];

int mul(int a, int b) {
    a = ((a % mod) + mod) % mod;
    b = ((b % mod) + mod) % mod;
    return (a * 1LL * b) % mod;
}

int add(int a, int b) {
    a = ((a % mod) + mod) % mod;
    b = ((b % mod) + mod) % mod;
    return (a + b) % mod;
}

int fastPower(int base, int power) {
    if (!power) return 1;
    int ret = fastPower(base, power >> 1);
    ret = mul(ret, ret);
    if (power % 2) ret = mul(ret, base);
    return ret;
}

void pre() {
    pw1[0] = pw2[0] = 1;
    int mulInv1 = fastPower(P1, mod - 2);
    int mulInv2 = fastPower(P2, mod - 2);
    for (int i = 1; i < N; i++) {
        pw1[i] = mul(pw1[i - 1], P1);
        pw2[i] = mul(pw2[i - 1], P2);
    }
}

struct DynamicHash {
    pii value, pre;
    int size = 0;
//    int inv1 = fastPower(P1, mod - 2), inv2 = fastPower(P2, mod - 2);
    int inv1 = 129032259, inv2 = 621621626;

    int cast(char c) { return c - 'a' + 1; }

    void HashItAll(string &s) {
        size = s.size();
        for (int i = 0; i < size; i++) {
            value.F = mul(cast(s[i]), pw1[i]);
            value.S = mul(cast(s[i]), pw2[i]);
            if (i) value = {add(value.F, pre.F), add(value.S, pre.S)};
            pre = value;
        }
    }

    void add_back(char x) {
        value.F = (value.F + 1LL * pw1[size] * cast(x)) % mod;
        value.S = (value.S + 1LL * pw2[size] * cast(x)) % mod;
        size++;
    }

    void remove_back(char x) {
        size--;
        value.F = (((value.F - 1LL * pw1[size] * cast(x)) % mod) + mod) % mod;
        value.S = (((value.S - 1LL * pw2[size] * cast(x)) % mod) + mod) % mod;
    }

    void add_front(char x) {
        value.F = (1LL * value.F * P1 + cast(x)) % mod;
        value.S = (1LL * value.S * P2 + cast(x)) % mod;
        size++;
    }

    void remove_front(char x) {
        size--;
        value.F = (1LL * (value.F - cast(x) + mod) * inv1) % mod;
        value.S = (1LL * (value.S - cast(x) + mod) * inv2) % mod;
    }
};
