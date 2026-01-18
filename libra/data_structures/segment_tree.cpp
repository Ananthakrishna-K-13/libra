#include <bits/stdc++.h>
using namespace std;

// MODIFY THIS SECTION, BUILD and UPDATE

struct Node {
    long long sum;
    long long max_val;
    
    static Node neutral() {
        return {0, (long long)-1e18}; 
    }
};

// Merge logic
Node merge(const Node& a, const Node& b) {
    return {
        a.sum + b.sum,
        max(a.max_val, b.max_val)
    };
}

// Descent Predicate
// we get first index from the left where the check function is true
bool check(const Node& node, long long k) {
    return node.max_val >= k; 
}

//  SEGMENT TREE TEMPLATE

struct SegTree {
    int n;
    vector<Node> tree;

    SegTree(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n, Node::neutral());

        build(a,1,0,n-1);
    }

    void build(const vector<int>& a, int node, int start, int end) {
        if (start == end) {

            // MODIFY THIS
            // MODIFY THIS
            // MODIFY THIS            
            tree[node] = { (long long)a[start], (long long)a[start] };

        } else {
            int mid = (start + end) / 2;
            build(a, 2 * node, start, mid);
            build(a, 2 * node + 1, mid + 1, end);
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    void update(int idx, int val, int node, int start, int end) {
        if (start == end) {

            // MODIFY THIS   
            // MODIFY THIS
            // MODIFY THIS   
            tree[node] = { (long long)val, (long long)val };

        } else {
            int mid = (start + end) / 2;
            if (start <= idx && idx <= mid) {
                update(idx, val, 2 * node, start, mid);
            } else {
                update(idx, val, 2 * node + 1, mid + 1, end);
            }
            tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
        }
    }

    Node query(int l, int r, int node, int start, int end) {
        if (r < start || end < l) {
            return Node::neutral();
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        Node p1 = query(l, r, 2 * node, start, mid);
        Node p2 = query(l, r, 2 * node + 1, mid + 1, end);
        return merge(p1, p2);
    }

    // Descent: Find first index in range [l, r] where check reutrns true
    int find_first(int l, int r, long long k, int node, int start, int end) {
        if (start > r || end < l || !check(tree[node], k)) {
            return -1;
        }
        
        if (start == end) {
            return start;
        }
        
        int mid = (start + end) / 2;
        int res = -1;
        
        // 2. Try Left
        if (mid >= l) {
            res = find_first(l, r, k, 2 * node, start, mid);
        }
        
        // 3. Try Right if not found in Left
        if (res == -1) {
            res = find_first(l, r, k, 2 * node + 1, mid + 1, end);
        }
        
        return res;
    }

    // Wrappers
    void build(const vector<int>& a) { build(a, 1, 0, n - 1); }
    void update(int idx, int val) { update(idx, val, 1, 0, n - 1); }
    Node query(int l, int r) { return query(l, r, 1, 0, n - 1); }
    int find_first(int l, int r, long long k) { return find_first(l, r, k, 1, 0, n - 1); }
};

int main() {
    vector<int> arr = {1, 3, 5, 2, 4, 6};
    int n = arr.size();
    SegTree st(arr);

    Node res = st.query(1, 4);

    int idx = st.find_first(0, 5, 4); 
    cout << "First index >= 4: " << idx << endl;

    st.update(2, 1); 

    idx = st.find_first(0, 5, 4);
    cout << "First index >= 4: " << idx << endl;

    return 0;
}