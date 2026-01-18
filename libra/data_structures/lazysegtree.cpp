#include <bits/stdc++.h>
using namespace std;

// MODIFY THIS SECTION, UPDATE SECTION and PUSH FUNCTION
struct Node {
    long long sum;
    long long max_val;
    long long sz; 

    // Identity Element
    static Node neutral() {
        return {0, (long long)-4e18, 0}; 
    }
    
    // Leaf Initialization: How to create a node from a single array value
    static Node from_value(long long v) {
        return {v, v, 1};
    }
};

// MERGE
Node merge(const Node& a, const Node& b) {
    // If one side is empty/neutral (size 0), return the other
    if (a.sz == 0) return b;
    if (b.sz == 0) return a;
    
    return {
        a.sum + b.sum,
        max(a.max_val, b.max_val),
        a.sz + b.sz
    };
}

// TAG
struct Tag {
    long long add; 
    
    // Identity Tag
    static Tag neutral() {
        return {0};
    }
};

// APPLY TAG
void apply_tag(Node& node, const Tag& tag) {
    if (node.sz == 0) return;
    node.sum += tag.add * node.sz; // Range Add logic for Sum
    node.max_val += tag.add;       // Range Add logic for Max
}

// COMBINE TAGS: How to merge a new tag onto an existing one
void combine_tags(Tag& old_tag, const Tag& new_tag) {
    old_tag.add += new_tag.add;
}

// CHECK (Descent): Predicate for finding an index
// reuturns first index where check is true
bool check(const Node& node, long long k) {
    return node.max_val >= k;
}

// LAZY SEGMENT TREE

struct LazySegTree {
    int n;
    vector<Node> tree;
    vector<Tag> lazy;

    LazySegTree(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n, Node::neutral());
        lazy.resize(4 * n, Tag::neutral());

        build(a,1,0,n-1);
    }

    void push(int node) {
        
        //MODIFY THIS
        //MODIFY THIS
        //MODIFY THIS
        if (lazy[node].add == 0) return; 

        apply_tag(tree[2 * node], lazy[node]);
        combine_tags(lazy[2 * node], lazy[node]);

        apply_tag(tree[2 * node + 1], lazy[node]);
        combine_tags(lazy[2 * node + 1], lazy[node]);

        lazy[node] = Tag::neutral();
    }

    void build(const vector<int>& a, int node, int start, int end) {
        if (start == end) {
            tree[node] = Node::from_value(a[start]);
        } else {
            int mid = (start + end) / 2;
            build(a, 2 * node, start, mid);
            build(a, 2 * node + 1, mid + 1, end);
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update(int l, int r, long long val, int node, int start, int end) {
        if (start > end || start > r || end < l) return;
        
        if (start >= l && end <= r) {

            //MODIFY THIS
            //MODIFY THIS
            //MODIFY THIS
            Tag new_tag = {val};

            apply_tag(tree[node], new_tag);
            combine_tags(lazy[node], new_tag);
            return;
        }

        push(node);
        int mid = (start + end) / 2;
        update(l, r, val, 2 * node, start, mid);
        update(l, r, val, 2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int l, int r, int node, int start, int end) {
        if (start > end || start > r || end < l) return Node::neutral();
        if (start >= l && end <= r) return tree[node];

        push(node);
        int mid = (start + end) / 2;
        return merge(query(l, r, 2 * node, start, mid),
                     query(l, r, 2 * node + 1, mid + 1, end));
    }

    // Descent: Find first index in [l, r] satisfying check()
    int find_first(int l, int r, long long k, int node, int start, int end) {

        if (start > end || start > r || end < l || !check(tree[node], k)) {
            return -1;
        }
        
        if (start == end) return start;

        push(node);
        int mid = (start + end) / 2;
        
        int res = find_first(l, r, k, 2 * node, start, mid);
        
        if (res == -1) {
            res = find_first(l, r, k, 2 * node + 1, mid + 1, end);
        }
        
        return res;
    }

    void build(const vector<int>& a) { build(a, 1, 0, n - 1); }
    void update(int l, int r, long long val) { update(l, r, val, 1, 0, n - 1); }
    Node query(int l, int r) { return query(l, r, 1, 0, n - 1); }
    int find_first(int l, int r, long long k) { return find_first(l, r, k, 1, 0, n - 1); }
};

int main() {
    vector<int> arr = {1, 2, 3, 4, 5};
    LazySegTree st(arr);

    st.update(1, 3, 10);

    cout << "Sum: " << st.query(0, 4).sum << endl;

    cout << "First >= 13: " << st.find_first(0, 4, 13) << endl;
}