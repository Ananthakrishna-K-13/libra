#include <bits/stdc++.h>
using namespace std;

// Fenwick Tree for prefix sums, range sums, point updates,
// and order statistics.
//
// Internal indexing: 1-based
// Public API:       0-based

struct Fenwick {
    vector<long long> bit;
    int n;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

    // O(n) construction from an array of frequencies.
    Fenwick(const vector<int>& a) : n(a.size()), bit(n + 1, 0) {
        for (int i = 1; i <= n; i++) {
            bit[i] = a[i - 1];
        }

        for (int i = 1; i <= n; i++) {
            int p = i + (i & -i);

            if (p <= n) {
                bit[p] += bit[i];
            }
        }
    }

    // Sum of elements in [0, idx].
    long long sum(int idx) {
        long long ret = 0;

        for (++idx; idx > 0; idx -= idx & -idx) {
            ret += bit[idx];
        }

        return ret;
    }

    // Sum of elements in [l, r].
    long long sum(int l, int r) {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }

    // Add delta to the element at index idx.
    void add(int idx, long long delta) {
        for (++idx; idx <= n; idx += idx & -idx) {
            bit[idx] += delta;
        }
    }

    // Find the index of the k-th element.
    // k is 1-based: k = 1 means the first element.
    //
    // Returns the 0-based index.
    // Returns -1 if k is invalid.
    //
    // Requires every frequency to be non-negative.
    int kth(long long k) {
        if (k <= 0 || k > sum(n - 1)) {
            return -1;
        }

        int idx = 0;

        // Largest power of 2 <= n.
        int step = 1;
        while (step <= n / 2) {
            step <<= 1;
        }

        // Binary lifting.
        for (; step > 0; step >>= 1) {
            int next = idx + step;

            if (next <= n && bit[next] < k) {
                idx = next;
                k -= bit[next];
            }
        }

        return idx;
    }

    // PBDS-style interface:
    // Find the k-th element, using 0-based k.
    //
    // find_by_order(0) = first element.
    // find_by_order(1) = second element.
    //
    // Returns the 0-based index, or -1 if invalid.
    int find_by_order(long long k) {
        if (k < 0 || k >= sum(n - 1)) {
            return -1;
        }

        return kth(k + 1);
    }

    // Count the elements whose indices are strictly less than idx.
    //
    // Requires 0 <= idx <= n.
    // Returns the number of elements, not the number of
    // distinct indices.
    long long order_of_key(int idx) {
        return sum(idx - 1);
    }
};