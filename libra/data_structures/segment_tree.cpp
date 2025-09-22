#include <bits/stdc++.h>
using namespace std;

// 0 indexed usage
// 0 indexed usage
// 0 indexed usage
// 0 indexed usage
// 0 indexed usage


struct SegmentTree {
private:
    // — your per‐node data lives here —
    struct Node {
        long long sum;
        int       mx;
        int       mn;
        Node(long long _sum = 0, int _mx = INT_MIN, int _mn = INT_MAX) : sum(_sum), mx(_mx), mn(_mn) {}
    };

    int n;
    vector<Node> st;

    Node merge(const Node &L, const Node &R) {  //change as per node
        return Node(
            L.sum + R.sum,
            max(L.mx, R.mx),
            min(L.mn, R.mn)
        );
    }

    void build(const vector<int> &a, int p, int l, int r) {
        if (l == r) {
            st[p] = Node(a[l], a[l], a[l]);  // change as per node
            return;
        }
        int m = (l + r) >> 1;
        build(a, p<<1,   l,   m);
        build(a, p<<1|1, m+1, r);
        st[p] = merge(st[p<<1], st[p<<1|1]);
    }

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            st[p] = Node(val, val, val); //change as per node
            return;
        }
        int m = (l + r) >> 1;
        if (idx <= m) update(p<<1,   l,   m, idx, val);
        else          update(p<<1|1, m+1, r, idx, val);
        st[p] = merge(st[p<<1], st[p<<1|1]);
    }

    Node query(int p, int l, int r, int i, int j) {
        if (j < l || r < i) 
            return Node(0, INT_MIN, INT_MAX);  // identity - change as per node
        if (i <= l && r <= j) 
            return st[p];
        int m = (l + r) >> 1;
        Node L = query(p<<1,   l,   m, i, j);
        Node R = query(p<<1|1, m+1, r, i, j);
        return merge(L, R);
    }

    int get_k(int p, int l, int r, int k){
        if(l==r) return l;

        int m = (l+r)>>1;
        
        int cntl = st[2*p].sum;  //change as per node
        int cntr =  st[2*p +1].sum;

        if(cntl < k){
            return get_k(2*p + 1,m+1,r,k-cntl);
        }
        else{
            return get_k(2*p,l,m,k);
        }
    }

public:
    SegmentTree(const vector<int> &a) {
        n = (int)a.size();
        st.assign(4*n, Node());
        build(a, 1, 0, n-1);
    }

    // set a[idx] = val
    void update(int idx, int val) {
        update(1, 0, n-1, idx, val);
    }

    // query [l..r]
    // returns a tuple (sum, max, min).
    tuple<long long,int,int> query(int l, int r) {
        Node res = query(1, 0, n-1, l, r);
        return { res.sum, res.mx, res.mn };
    }

    //get index of kth one in a binary array (walking the st in O(log n))
    int get_k(int k){
        return get_k(1, 0, n-1,k);
    }
};

// — example usage —
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (int i = 0; i < N; i++) 
        cin >> A[i];

    SegmentTree st(A);

    while (Q--) {
        int type; 
        cin >> type;
        if (type == 1) {
            int idx, v;
            cin >> idx >> v;
            st.update(idx-1, v);
        } else {
            int l, r;
            cin >> l >> r;
            auto [sum, mx, mn] = st.query(l-1, r-1);
            cout << "sum=" << sum 
                 << " max=" << mx 
                 << " min=" << mn << "\n";
        }
    }
    return 0;
}
