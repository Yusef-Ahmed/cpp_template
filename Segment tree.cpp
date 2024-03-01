ll n;
vector<ll> arr;

struct segmentTree {
    ll neutral = 0;
    vector<ll> tree, lazy;

    ll merge(ll x, ll y) {
        return (x | y);
    }

    void pre() {
        tree.resize(4 * n);
        lazy.resize(4 * n);
    }

    void build(ll node, ll start, ll end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        ll mid = start + (end - start) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(ll node, ll start, ll end, ll idx, ll val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        ll mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            update(node * 2, start, mid, idx, val);
        } else {
            update(node * 2 + 1, mid + 1, end, idx, val);
        }
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void updateRangeUtil(ll node, ll start, ll end, ll l, ll r, ll val) {
        if (lazy[node]) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (start > r || end < l || start > end) {
            return;
        }
        if (start >= l && end <= r) {
            tree[node] += val;
            if (start != end) {
                lazy[node * 2] += val;
                lazy[node * 2 + 1] += val;
            }
            return;
        }
        ll mid = (start + end) / 2;
        updateRangeUtil(node * 2, start, mid, l, r, val);
        updateRangeUtil(node * 2 + 1, mid + 1, end, l, r, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }
    
    ll query(ll node, ll start, ll end, ll l, ll r) {
        if (start > r || end < l) {
            return neutral;
        }
        if (start >= l && end <= r) {
            return tree[node];
        }
        ll mid = (start + end) / 2;
        int firstchild = query(node * 2, start, mid, l, r);
        int secondchild = query(node * 2 + 1, mid + 1, end, l, r);

        return merge(firstchild, secondchild);
    }

    ll queryRangeUtil(ll node, ll start, ll end, ll l, ll r) {
        if (start > end || start > r || end < l) {
            return neutral;
        }
        if (lazy[node]) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[node * 2] += lazy[node];
                lazy[node * 2 + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (start >= l && end <= r) {
            return tree[node];
        }
        ll mid = (start + end) / 2;
        ll firstChild = queryRangeUtil(node * 2, start, mid, l, r);
        ll secondChild = queryRangeUtil(node * 2 + 1, mid + 1, end, l, r);
        return merge(firstChild, secondChild);

    }

    void set(ll idx, ll val) {
        update(1, 0, n - 1, idx, val);
    }

    void setRange(ll l, ll r, ll val) {
        updateRangeUtil(1, 0, n - 1, l, r, val);
    }

    ll get(ll l, ll r) {
        return queryRangeUtil(1, 0, n - 1, l, r);
    }

    void buildTree() {
        pre();
        build(1, 0, n - 1);
    }

    void clear() {
        tree.clear();
    }
};
