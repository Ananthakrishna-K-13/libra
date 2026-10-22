#include <bits/stdc++.h>
using namespace std;

// Internal indexing: 1-based
// Public API:        0-based

struct Fenwick2D {
    int n, m;
    vector<vector<long long>> bit;

    Fenwick2D(int n, int m) : n(n), m(m),
          bit(n + 1, vector<long long>(m + 1, 0)) {}

    Fenwick2D(const vector<vector<long long>>& a) : n((int)a.size()),
          m(a.empty() ? 0 : (int)a[0].size()),
          bit(n + 1, vector<long long>(m + 1, 0)) {

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                bit[i][j] = a[i - 1][j - 1];
            }
        }

        for (int i = 1; i <= n; i++) {
            int p = i + (i & -i);

            if (p <= n) {
                for (int j = 1; j <= m; j++) {
                    bit[p][j] += bit[i][j];
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int p = j + (j & -j);

                if (p <= m) {
                    bit[i][p] += bit[i][j];
                }
            }
        }
    }

    void add(int x, int y, long long delta) {
        for (int i = x + 1; i <= n; i += i & -i) {
            for (int j = y + 1; j <= m; j += j & -j) {
                bit[i][j] += delta;
            }
        }
    }

    long long prefixSum(int x, int y) const {
        if (x < 0 || y < 0) {
            return 0;
        }

        long long ans = 0;

        for (int i = x + 1; i > 0; i -= i & -i) {
            for (int j = y + 1; j > 0; j -= j & -j) {
                ans += bit[i][j];
            }
        }

        return ans;
    }

    long long sumRect(int x1, int y1, int x2, int y2) const {
        return prefixSum(x2, y2)
             - prefixSum(x1 - 1, y2)
             - prefixSum(x2, y1 - 1)
             + prefixSum(x1 - 1, y1 - 1);
    }
};
