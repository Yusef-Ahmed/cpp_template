bool flag[N];
map<int, bool> mp;
void getprime() {
    for (ll i = 2; i < N; i++) {
        if (flag[i] == 1) continue;
        mp[i] = 1;
        for (ll j = i * i; j < N; j += i) flag[j] = 1;
    }
}
