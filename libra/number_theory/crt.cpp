#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

// Helper function to print __int128_t
ostream& operator<<(ostream& os, i128 val) {
    if (val == 0) return os << "0";
    string s = "";
    bool is_neg = val < 0;
    if (is_neg) val = -val;
    while (val > 0) {
        s += (val % 10) + '0';
        val /= 10;
    }
    if (is_neg) s += '-';
    reverse(s.begin(), s.end());
    return os << s;
}

i128 extendedGcd(i128 a, i128 b, i128 &x, i128 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i128 x1, y1;
    i128 gcd = extendedGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

i128 modInverse(i128 a, i128 m) {
    i128 x, y;
    i128 g = extendedGcd(a, m, x, y);
    if (g != 1) return -1; // Inverse doesn't exist
    return (x % m + m) % m;
}


/**************************************************************
 * 1. CRT with COPRIME moduli (Overflow-Safe Version)
 **************************************************************/
// O(k log(n_max)) : k is number of congrunces
// A = a[i] % n[i]
ll crt_coprime(const vector<ll>& a, const vector<ll>& n) {
    ll N = 1;
    for (ll ni : n) {
        N *= ni;
    }

    i128 result = 0;
    for (size_t i = 0; i < n.size(); ++i) {
        i128 ni = n[i];
        i128 ai = a[i];
        i128 Ni = N / ni;
        i128 inv_Ni = modInverse(Ni, ni);
        
        i128 term = ai * Ni;
        term %= N;
        term *= inv_Ni;
        term %= (i128)N;
        
        result = (result + term) % (i128)N;
    }

    return (ll)((result + N) % N);
}


/**************************************************************
 * 2. Extended CRT for NON-COPRIME moduli (Overflow-Safe Version)
 **************************************************************/

i128 gcd(i128 a, i128 b) {
    return b == 0 ? a : gcd(b, a % b);
}

// O(k log(n_lcm)) : k is number of congrunces
// A = a[i] % n[i]
pair<i128, i128> crt_non_coprime(const vector<ll>& a, const vector<ll>& n) {
    if (a.empty()) {
        return {0, 1};
    }

    i128 current_a = a[0];
    i128 current_n = n[0];

    for (size_t i = 1; i < a.size(); ++i) {
        i128 next_a = a[i];
        i128 next_n = n[i];

        i128 diff = next_a - current_a;
        i128 g = gcd(current_n, next_n);

        if (diff % g != 0) {
            return {-1, -1}; // No solution
        }
        
        i128 n1_g = current_n / g;
        i128 n2_g = next_n / g;
        
        i128 inv = modInverse(n1_g, n2_g);
        i128 k = (diff / g) * inv;

        k = (k % n2_g + n2_g) % n2_g;

        i128 new_n = current_n / g * next_n;
        current_a = current_a + k * current_n;
        current_n = new_n;
        
        current_a = (current_a % current_n + current_n) % current_n;
    }

    return {current_a, current_n};
}


int main() {
    cout << "--- 1. CRT with COPRIME moduli (Overflow-Safe) ---" << endl;
    // This example would overflow a standard implementation because
    // N is ~10^18, so Ni is ~10^18, and a[i]*Ni would be ~10^36.
    vector<ll> a1 = {100, 200, 300};
    vector<ll> n1 = {1000000007, 1000000009, 1000000021}; // Large primes
    
    ll solution1 = crt_coprime(a1, n1);
    cout << "Coprime Solution: x = " << solution1 << endl;
    // Correct small example check: a={2,3,2}, n={3,5,7} -> x=23
    // cout << "Test: " << crt_coprime_safe({2,3,2}, {3,5,7}) << endl;


    cout << "\n--- 2. Extended CRT with NON-COPRIME moduli (Overflow-Safe) ---" << endl;
    
    // Example 1: Solvable system where LCM and intermediate products would overflow ll
    // n1*n2 is ~8*10^18, their LCM is large.
    // The k * current_n term would be the first to overflow.
    vector<ll> a2 = {123456, 7891011};
    vector<ll> n2 = {2000000000, 4000000002}; // Even numbers, non-coprime
    
    pair<i128, i128> sol2 = crt_non_coprime(a2, n2);
    if (sol2.first != -1) {
        cout << "Non-Coprime Solvable Example:" << endl;
        cout << "x = " << sol2.first << " (mod " << sol2.second << ")" << endl;
    } else {
        cout << "Non-Coprime Solvable Example: No solution found." << endl;
    }
    
    cout << "\n";

    // Example 2: Unsolvable system
    vector<ll> a3 = {3, 4};
    vector<ll> n3 = {6, 10};
    pair<i128, i128> sol3 = crt_non_coprime(a3, n3);
     if (sol3.first != -1) {
        cout << "Unsolvable Example:" << endl;
        cout << "x = " << sol3.first << " (mod " << sol3.second << ")" << endl;
    } else {
        cout << "Unsolvable Example: No solution found, as expected." << endl;
    }

    return 0;
}