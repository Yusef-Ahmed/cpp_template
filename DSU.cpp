struct DSU {
    int parent[N];
    int groupsize[N];

    DSU() {
        for (int i = 0; i < N; i++) {
            parent[i] = i;
            groupsize[i] = 1;
        }
    }

    int find_leader(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find_leader(parent[i]);
    }

    bool same_group(int x, int y) {
        int leader1 = find_leader(x);
        int leader2 = find_leader(y);
        return leader1 == leader2;
    }

    void unite(int x, int y) {
        int leader1 = find_leader(x);
        int leader2 = find_leader(y);
        if (leader1 == leader2) return;
        if (groupsize[leader2] > groupsize[leader1]) {
            swap(leader1, leader2);
        }
        groupsize[leader1] += groupsize[leader2];
        parent[leader2] = leader1;
    }

    int get_size(int x) {
        int leader = find_leader(x);
        return groupsize[leader];
    }
};

struct Edge {
    int u, v;
    double weight;

    bool operator<(Edge const &other) {
        return weight < other.weight;
    }
};
