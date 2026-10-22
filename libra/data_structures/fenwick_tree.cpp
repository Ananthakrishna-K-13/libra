#include <bits/stdc++.h>
using namespace std;

// Fenwick Tree for range sum queries.
// Internal indexing: 1-based
// Public API:        0-based

struct Fenwick {
    vector<long long> bit;
    int n;

    Fenwick(int n) : n(n), bit(n + 1, 0) {}

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

    long long sum(int idx) {
        long long ret = 0;

        for (++idx; idx > 0; idx -= idx & -idx) {
            ret += bit[idx];
        }

        return ret;
    }

    long long sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, long long delta) {
        for (++idx; idx <= n; idx += idx & -idx) {
            bit[idx] += delta;
        }
    }
};