#include<bits/stdc++.h>
using namespace std;

// 0 based index
// 0 based index
// 0 based index
// 0 based index


// --- MODIFY HERE (1/6) ---
// Define the node struct. This holds the data for a range.
struct Node {
    long long val;
    int sz;      // stores size of the range, useful for walking

    // Default constructor (identity element for queries)
    Node() : val(0), sz(0) {} 

    // Leaf constructor
    Node(long long v) : val(v), sz(1) {}
};

// --- MODIFY HERE (2/6) ---
// Define the lazy struct. This holds the pending updates.
struct Lazy {
    long long val;
    bool id;       // Flag to check if this lazy is a no-op (identity)

    // Default constructor (identity element for updates)
    Lazy() : val(0), id(true) {} 

    // Update constructor
    Lazy(long long v) : val(v), id(false) {}
};

class LazySegmentTree {
public:
    LazySegmentTree(int n) : n(n) {
        t.resize(4 * n);
        lz.resize(4 * n);
    }

    LazySegmentTree(const vector<long long>& a) : n(a.size()) {
        t.resize(4 * n);
        lz.resize(4 * n);
        build(1, 0, n - 1, a);
    }

    void update(int l, int r, long long val) {
        update(1, 0, n - 1, l, r, Lazy(val));
    }

    Node query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    int find_first(int l, int r, long long val) {
        return find_first(1, 0, n - 1, l, r, val);
    }


private:
    int n;
    vector<Node> t; // tree
    vector<Lazy> lz; // lazy

    // --- MODIFY HERE (3/6) ---
    // Merge two nodes
    Node merge(const Node& left, const Node& right) {
        Node res;

        res.val = left.val + right.val; 
        res.sz = left.sz + right.sz;
        return res;
    }

    // --- MODIFY HERE (4/6) ---
    // apply parents lazy to childs value
    // how child segtree node should look like after applying range update to childs range
    void apply(int v, const Lazy& lazy_upd, int len) {

        t[v].val += lazy_upd.val * len;
    }

    // --- MODIFY HERE (5/6) ---
    // apply parents lazy to childs lazy
    // how child lazy node should look like after applying range update to childs range
    void combine(int v, const Lazy& parent_lazy) {
        if (lz[v].id) {
            lz[v] = parent_lazy;
        } else {
            lz[v].val += parent_lazy.val;
            lz[v].id = false;
        }
    }

    void reset(int v) {
        lz[v] = Lazy();
    }

    bool is_id(int v) {
        return lz[v].id;
    }

    // --- MODIFY HERE (6/6) ---
    int find_first(int v, int tl, int tr, int ql, int qr, long long val) {
        if (tr < ql || tl > qr) {
            return -1;
        }

        push(v, tl, tr);

        // Example for "find first >= val" with min query:
        if (t[v].val >= val) {
            return max(tl, ql);
        }

        if (tl == tr) {
            return -1; 
        }

        int tm = (tl + tr) / 2;
        
        int res_left = find_first(v * 2, tl, tm, ql, qr, val);
        if (res_left != -1) {
            return res_left;
        }

        return find_first(v * 2 + 1, tm + 1, tr, ql, qr, val);
    }

    // --- CORE LOGIC (Usually no changes needed) ---

    // Push lazy updates down to children
    void push(int v, int tl, int tr) {
        if (!is_id(v)) { 
            int tm = (tl + tr) / 2;
            int left_child = v * 2;
            int right_child = v * 2 + 1;

            apply(left_child, lz[v], tm - tl + 1);
            combine(left_child, lz[v]);

            apply(right_child, lz[v], tr - (tm + 1) + 1);
            combine(right_child, lz[v]);

            reset(v);
        }
    }

    // Build the tree from an initial array
    void build(int v, int tl, int tr, const vector<long long>& a) {
        if (tl == tr) {
            t[v] = Node(a[tl]);
        } else {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm, a);
            build(v * 2 + 1, tm + 1, tr, a);
            t[v] = merge(t[v * 2], t[v * 2 + 1]);
        }
    }

    void update(int v, int tl, int tr, int l, int r, const Lazy& val) {
        if (l > r) {
            return;
        }
        if (l == tl && r == tr) {
            apply(v, val, tr - tl + 1);
            combine(v, val);
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            update(v * 2, tl, tm, l, min(r, tm), val);
            update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, val);
            t[v] = merge(t[v * 2], t[v * 2 + 1]);
        }
    }

    Node query(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return Node(); // Return identity element
        }
        if (l == tl && r == tr) {
            return t[v];
        }
        
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        
        Node left_res = query(v * 2, tl, tm, l, min(r, tm));
        Node right_res = query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
        
        return merge(left_res, right_res);
    }

    
};


