#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7; // Update if the problem requires 998244353

struct Matrix {
    int n, m;
    vector<vector<long long>> mat;
    
    // Constructor 1: Initialize with dimensions (filled with zeros)
    Matrix(int _n, int _m) {
        n = _n;
        m = _m;
        mat.assign(n, vector<long long>(m, 0));
    }
    
    // Constructor 2: Initialize directly from a 2D vector
    Matrix(const vector<vector<long long>>& _mat) {
        n = _mat.size();
        m = n > 0 ? _mat[0].size() : 0;
        mat = _mat;
    }
    
    // Set current matrix to identity matrix
    void make_identity() {
        assert(n == m);
        for (int i = 0; i < n; i++) {
            mat[i][i] = 1;
        }
    }
    
    // Matrix multiplication with modulo arithmetic
    Matrix operator*(const Matrix &other) const {
        assert(m == other.n);
        Matrix res(n, other.m);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                if (mat[i][k] == 0) continue; // Optimization for sparse matrices
                for (int j = 0; j < other.m; j++) {
                    res.mat[i][j] += (mat[i][k] * other.mat[k][j]) % MOD;
                    if (res.mat[i][j] >= MOD) {
                        res.mat[i][j] %= MOD;
                    }
                }
            }
        }
        return res;
    }
};

// Binary exponentiation for matrices
Matrix power(Matrix a, long long b) {
    assert(a.n == a.m);
    Matrix res(a.n, a.n);
    res.make_identity();
    
    while (b > 0) {
        if (b & 1) res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {
    // Example: Finding the N-th Fibonacci number using Matrix Exponentiation
    // Transition matrix T for Fibonacci: F(n) = F(n-1) + F(n-2)
    // | 1 1 |   | F(n-1) |   | F(n)   |
    // | 1 0 | * | F(n-2) | = | F(n-1) |
    
    long long N;
    cin >> N;
    
    if (N == 0) {
        cout << 0 << "\n";
        return;
    }
    
    // Use the 2D vector constructor
    Matrix T({{1, 1}, {1, 0}});
    
    // Raise the transition matrix to the power of N-1
    Matrix res = power(T, N - 1);
    
    // The base cases are F(1) = 1, F(0) = 0
    // We want the top-left element after multiplying by the base case vector [1, 0]^T
    long long ans = res.mat[0][0]; 
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t = 1;
    // cin >> t; // Uncomment if there are multiple test cases
    while (t--) {
        solve();
    }
    
    return 0;
}