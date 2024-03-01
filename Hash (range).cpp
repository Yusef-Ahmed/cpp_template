int pw1[N], pw2[N], inv1[N], inv2[N];

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
    pw1[0] = inv1[0] = pw2[0] = inv2[0] = 1;
    int mulInv1 = fastPower(P1, mod - 2);
    int mulInv2 = fastPower(P2, mod - 2);
    for (int i = 1; i < N; i++) {
        pw1[i] = mul(pw1[i - 1], P1);
        pw2[i] = mul(pw2[i - 1], P2);
        inv1[i] = mul(inv1[i - 1], mulInv1);
        inv2[i] = mul(inv2[i - 1], mulInv2);
    }
}

struct RangeHash {
    vector<pii > prefixHash;

    RangeHash(string &s) {
        prefixHash = vector<pii >(s.size(), {0, 0});
        for (int i = 0; i < s.size(); i++) {
            prefixHash[i].F = mul(s[i] - 'a' + 1, pw1[i]);
            prefixHash[i].S = mul(s[i] - 'a' + 1, pw2[i]);
            if (i) {
                prefixHash[i] = {
                        add(prefixHash[i].F, prefixHash[i - 1].F),
                        add(prefixHash[i].S, prefixHash[i - 1].S)
                };
            }
        }
    }

    pii getHashVal() {
        return prefixHash.back();
    }

    pii getRangeHashVal(int l, int r) {
        return {
                mul(add(prefixHash[r].F, -(l ? prefixHash[l - 1].F : 0)), inv1[l]),
                mul(add(prefixHash[r].S, -(l ? prefixHash[l - 1].S : 0)), inv2[l])
        };
    }
};
