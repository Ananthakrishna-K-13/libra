#include <bits/stdc++.h>
using namespace std;

struct MergeSortTree {
    int n;
    vector<vector<int>> tree;

    MergeSortTree(const vector<int>& a) {
        n = a.size();
        tree.resize(4 * n);
        if (n > 0) {
            build(a, 1, 0, n - 1);
        }
    }

    void build(const vector<int>& a, int node, int start, int end) {
        if (start == end) {
            // [MODIFY HERE 1: What to store]
            // If you need to store pairs (e.g., {value, original_index}), 
            // you change the vector type and initialize it here.
            tree[node] = {a[start]};
            return;
        }
        
        int mid = start + (end - start) / 2;
        build(a, 2 * node, start, mid);
        build(a, 2 * node + 1, mid + 1, end);
        
        // [MODIFY HERE 2: How to merge]
        // std::merge is O(N). If you are storing custom structs/pairs,
        // you might need to pass a custom comparator as the last argument.
        merge(tree[2 * node].begin(), tree[2 * node].end(),
              tree[2 * node + 1].begin(), tree[2 * node + 1].end(),
              back_inserter(tree[node]));
    }

    int query(int l, int r, int k, int node, int start, int end) {
        // [MODIFY HERE 3: Neutral Value]
        // If your query returns something else (like minimum difference),
        // change this return value to your neutral element.
        if (r < start || end < l) {
            return 0; 
        }
        
        if (l <= start && end <= r) {
            // [MODIFY HERE 4: The Query Logic]
            // Default: Count elements strictly greater than k ( > k )
            auto it = upper_bound(tree[node].begin(), tree[node].end(), k);
            return tree[node].end() - it;
            
            /* Other common logics:
            
            // Count elements less than or equal to k ( <= k )
            auto it = upper_bound(tree[node].begin(), tree[node].end(), k);
            return it - tree[node].begin();
            
            // Count elements strictly less than k ( < k )
            auto it = lower_bound(tree[node].begin(), tree[node].end(), k);
            return it - tree[node].begin();
            
            // Count elements greater than or equal to k ( >= k )
            auto it = lower_bound(tree[node].begin(), tree[node].end(), k);
            return tree[node].end() - it;
            */
        }
        
        int mid = start + (end - start) / 2;
        int p1 = query(l, r, k, 2 * node, start, mid);
        int p2 = query(l, r, k, 2 * node + 1, mid + 1, end);
        
        // [MODIFY HERE 5: Combining Results]
        // Default: Summing the counts. 
        // Change if you need to take the min, max, etc.
        return p1 + p2; 
    }

    // Wrapper function for clean usage
    int query(int l, int r, int k) {
        return query(l, r, k, 1, 0, n - 1);
    }
};

// Usage Example:
// vector<int> arr = {3, 1, 4, 1, 5, 9, 2};
// MergeSortTree mst(arr);
// int count = mst.query(1, 4, 3); // Queries range [1, 4] for elements > 3