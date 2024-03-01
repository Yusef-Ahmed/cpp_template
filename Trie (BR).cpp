const int len = 20;
int pw[len];

void pre() {
    pw[0] = 1;
    for (int i = 1; i < len; i++) pw[i] = 2 * pw[i - 1];
}

vector<bool> binrep(int n) {
    vector<bool> v(len);
    for (int i = 0; i < len; i++) {
        if (n & pw[i]) v[i] = 1;
        else v[i] = 0;
    }
    return v;
}

struct Node {
    int cnt;
    Node *ptr[2];
};

struct BinTrie {
    Node *root;

    BinTrie() {
        root = new Node();
    }

    void insert(int x) {
        vector<bool> v = binrep(x);
        Node *cur = root;
        for (int i = len - 1; i >= 0; i--) {
            bool rank = v[i];
            if (cur->ptr[rank] == NULL)
                cur->ptr[rank] = new Node();
            cur = cur->ptr[rank];
            cur->cnt++;
        }
    }

    void erase(int x) {
        vector<bool> v = binrep(x);
        Node *cur = root;
        for (int i = len - 1; i >= 0; i--) {
            bool rank = v[i];
            cur = cur->ptr[rank];
            cur->cnt--;
        }
    }

    int search(int x) {
        Node *cur = root;
        vector<bool> v = binrep(x);
        int ans = 0;
        for (int i = len - 1; i >= 0; i--) {
            bool rank = v[i];
            if (rank == 1) rank = 1; // Cause of the XOR.
            if (cur->ptr[rank] == NULL) {
                cur->ptr[rank] = new Node();
                cur = cur->ptr[rank];
            } else if (cur->ptr[rank]->cnt < pw[i]) {
                cur = cur->ptr[rank];
            } else if (cur->ptr[!rank] == NULL) {
                ans += pw[i];
                cur->ptr[!rank] = new Node();
                cur = cur->ptr[!rank];
            } else {
                ans += pw[i];
                cur = cur->ptr[!rank];
            }
        }
        return ans;
    }
}; /// 1-DON'T repeat, 2-pre, 3-len.

int check(ll n) {
    int cnt = 0;
    while (n) n /= 2, cnt++;
    return cnt;
}
