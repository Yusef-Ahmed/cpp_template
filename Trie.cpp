struct Node {
    int cnt;
    Node *ptr[26];
};

struct Trie {
    Node *root;

    Trie() {
        root = new Node();
    }

    void insert(string &s) {
        Node *cur = root;
        for (auto &i: s) {
            int rank = i - 'a';
            if (cur->ptr[rank] == NULL)
                cur->ptr[rank] = new Node();
            cur = cur->ptr[rank];
            cur->cnt++;
        }
    }

    void erase(string &s) {
        Node *cur = root, *del;
        bool f = 0;
        for (auto &i: s) {
            if (f) {
                del = NULL;
                f = 0;
            }
            int rank = i - 'a';
            cur = cur->ptr[rank];
            cur->cnt--;
            if (cur->cnt == 0) del = cur, f = 1;
        }
        if (f) del = NULL;
    }

    int search(string &s) {
        Node *cur = root;
        for (auto &i: s) {
            int rank = i - 'a';
            if (cur->ptr[rank] == NULL)
                return 0;
            cur = cur->ptr[rank];
        }
        return cur->cnt;
    }
};
