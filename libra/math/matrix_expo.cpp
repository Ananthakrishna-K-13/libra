#include<bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7; 

struct Matrix {
    int n; 
    vector<vector<long long>> mat;

    Matrix(int size) : n(size) {
        mat.assign(n, vector<long long>(n, 0));
    }

    void makeIdentity() {
        for (int i = 0; i < n; ++i) {
            mat[i][i] = 1;
        }
    }

    Matrix operator*(const Matrix& other) const {
        Matrix res(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    res.mat[i][j] = (res.mat[i][j] + mat[i][k] * other.mat[k][j]) % MOD;
                }
            }
        }
        return res;
    }
};

Matrix power(Matrix base, long long exp) {
    Matrix res(base.n);
    res.makeIdentity(); 

    while (exp > 0) {
        if (exp & 1) {      
            res = res * base;
        }
        base = base * base;  
        exp >>= 1;
    }
    return res;
}

int main() {
    int size = 2;
    Matrix T(size);
    
    T.mat[0][0] = 1; T.mat[0][1] = 1;
    T.mat[1][0] = 1; T.mat[1][1] = 0;

    long long n = 10; 
    
    Matrix result = power(T, n);

    cout << "Resulting matrix after exponentiation:" << endl;
    for (int i = 0; i < result.n; ++i) {
        for (int j = 0; j < result.n; ++j) {
            cout << result.mat[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}