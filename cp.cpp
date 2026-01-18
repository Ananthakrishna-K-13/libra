#include<bits/stdc++.h> 
using namespace std;

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#ifdef AKLOCAL
#include "dbg.hpp"
#else
#define dbg(x...)
#define endl '\n'
#endif

// #define int long long
#define pb push_back
#define all(x) (x).begin(), (x).end()

template<const int &MOD>
struct _m_int {
    int val;

    _m_int(int64_t v = 0) {
        if (v < 0) v = v % MOD + MOD;
        if (v >= MOD) v %= MOD;
        val = int(v);
    }

    _m_int(uint64_t v) {
        if (v >= MOD) v %= MOD;
        val = int(v);
    }

    _m_int(int v) : _m_int(int64_t(v)) {}
    _m_int(unsigned v) : _m_int(uint64_t(v)) {}

    explicit operator int() const { return val; }
    explicit operator unsigned() const { return val; }
    explicit operator int64_t() const { return val; }
    explicit operator uint64_t() const { return val; }
    explicit operator double() const { return val; }
    explicit operator long double() const { return val; }

    _m_int& operator+=(const _m_int &other) {
        val -= MOD - other.val;
        if (val < 0) val += MOD;
        return *this;
    }

    _m_int& operator-=(const _m_int &other) {
        val -= other.val;
        if (val < 0) val += MOD;
        return *this;
    }

    static unsigned fast_mod(uint64_t x, unsigned m = MOD) {
#if !defined(_WIN32) || defined(_WIN64)
        return unsigned(x % m);
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * m for this to work, so that x / m fits in an unsigned 32-bit int.
        unsigned x_high = unsigned(x >> 32), x_low = unsigned(x);
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }

    _m_int& operator*=(const _m_int &other) {
        val = fast_mod(uint64_t(val) * other.val);
        return *this;
    }

    _m_int& operator/=(const _m_int &other) {
        return *this *= other.inv();
    }

    friend _m_int operator+(const _m_int &a, const _m_int &b) { return _m_int(a) += b; }
    friend _m_int operator-(const _m_int &a, const _m_int &b) { return _m_int(a) -= b; }
    friend _m_int operator*(const _m_int &a, const _m_int &b) { return _m_int(a) *= b; }
    friend _m_int operator/(const _m_int &a, const _m_int &b) { return _m_int(a) /= b; }

    _m_int& operator++() {
        val = val == MOD - 1 ? 0 : val + 1;
        return *this;
    }

    _m_int& operator--() {
        val = val == 0 ? MOD - 1 : val - 1;
        return *this;
    }

    _m_int operator++(int) { _m_int before = *this; ++*this; return before; }
    _m_int operator--(int) { _m_int before = *this; --*this; return before; }

    _m_int operator-() const {
        return val == 0 ? 0 : MOD - val;
    }

    friend bool operator==(const _m_int &a, const _m_int &b) { return a.val == b.val; }
    friend bool operator!=(const _m_int &a, const _m_int &b) { return a.val != b.val; }
    friend bool operator<(const _m_int &a, const _m_int &b) { return a.val < b.val; }
    friend bool operator>(const _m_int &a, const _m_int &b) { return a.val > b.val; }
    friend bool operator<=(const _m_int &a, const _m_int &b) { return a.val <= b.val; }
    friend bool operator>=(const _m_int &a, const _m_int &b) { return a.val >= b.val; }

    static const int SAVE_INV = int(1e6) + 5;
    static _m_int save_inv[SAVE_INV];

    static void prepare_inv() {
        // Ensures that MOD is prime, which is necessary for the inverse algorithm below.
        for (int64_t p = 2; p * p <= MOD; p += p % 2 + 1)
            assert(MOD % p != 0);

        save_inv[0] = 0;
        save_inv[1] = 1;

        for (int i = 2; i < SAVE_INV; i++)
            save_inv[i] = save_inv[MOD % i] * (MOD - MOD / i);
    }

    _m_int inv() const {
        if (save_inv[1] == 0)
            prepare_inv();

        if (val < SAVE_INV)
            return save_inv[val];

        _m_int product = 1;
        int v = val;

        do {
            product *= MOD - MOD / v;
            v = MOD % v;
        } while (v >= SAVE_INV);

        return product * save_inv[v];
    }

    _m_int pow(int64_t p) const {
        if (p < 0)
            return inv().pow(-p);

        _m_int a = *this, result = 1;

        while (p > 0) {
            if (p & 1)
                result *= a;

            p >>= 1;

            if (p > 0)
                a *= a;
        }

        return result;
    }

    friend ostream& operator<<(ostream &os, const _m_int &m) {
        return os << m.val;
    }
};

template<const int &MOD> _m_int<MOD> _m_int<MOD>::save_inv[_m_int<MOD>::SAVE_INV];

const int MOD = 998244353;
using mint = _m_int<MOD>;
void __print(mint x) { cerr << x; }

void solve(){   
    int n;
    cin>>n;
    string s;
    cin>>s;

    mint ze = 0;

    vector<vector<vector<mint>>> dp(n+1,vector<vector<mint>>(n+1,vector<mint>(4,ze)));
    vector<vector<vector<mint>>> ndp(n+1,vector<vector<mint>>(n+1,vector<mint>(4,ze)));

    dp[0][0][0] = 1;

    for(int i=0;i<n;i++){
        ndp = dp;
        for(int b = 0;b<=n;b++){
            for(int l=0;l<=n;l++){
                for(int k = 0;k<4;k++){
                    if(s[i]=='(' && (k==1 || k==2)){
                        if(b+1 <= n && l+1<=n) ndp[b+1][l+1][k+1]+= dp[b][l][k];
                    }
                    else if(s[i]=='(' && (k==0 || k==3)){
                        if(b+1 <= n && l+1<=n) ndp[b+1][l+1][k]+= dp[b][l][k];
                    }
                    else if(s[i]==')' && b>0 && (k==0)){
                        if(b-1 >= 0 && l+1<=n) ndp[b-1][l+1][k+1]+= dp[b][l][k];
                    }
                    else if(s[i]==')' && b>0 && (k>0)){
                        if(b-1 >= 0 && l+1<=n) ndp[b-1][l+1][k]+= dp[b][l][k];
                    }
                }
            }
        }
        swap(dp,ndp);
    }

    mint ans = 0;
    mint two = 2;
    for(int l = 0;l<=n;l++){
        ans += dp[0][l][3] * (((mint)l) - two);
    }
    cout<<ans<<endl;
}

signed main(){
    ios_base::sync_with_stdio(false);   
    cin.tie(NULL); cout.tie(NULL);

    int T = 1;          
    cin>>T;
    for(int i=1;i<=T;i++) solve();

    return 0;
}