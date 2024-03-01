int n;
int arr[N];

struct sparse {
    int table[N][20], logTwo[N];

    int merge(int u, int v) {
        return max(u, v);
    }

    void build() {
        logTwo[1] = 0;
        for (int i = 2; i <= n; i++)
            logTwo[i] = logTwo[i >> 1] + 1;

        for (int i = 0; i <= n; i++)
            table[i][0] = arr[i];

        for (int j = 1; j < 20; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                table[i][j] = merge(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
    }

    int query(int l, int r) {
        int len = r - l + 1;
        int power = logTwo[len];
        return merge(table[l][power], table[r - (1 << power) + 1][power]);
    }
};
