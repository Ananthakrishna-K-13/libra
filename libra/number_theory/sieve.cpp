#include<bits/stdc++.h> 
using namespace std;
const int mod = 998244353;

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10000000; // adjust as needed
vector<int> spf(MAXN+1); // smallest prime factor

// Precompute SPF  in O(n log log n)
void sieve() {
    iota(spf.begin(), spf.end(), 0); // spf[i] = i initially
    for (int i = 2; i * i <= MAXN; i++) {
        if (spf[i] == i) { // i is prime
            for (int j = i * i; j <= MAXN; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

//  prime factorization in O(log n)
vector<pair<int,int>> getPrimeFactors(int x) {
    vector<pair<int,int>> res;
    while (x > 1) {
        int p = spf[x], cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        res.push_back({p, cnt});
    }
    return res;
}

// all divisors in O(log n + #divisors(n))
// #divisors of n = n ^ 1/3
vector<int> getDivisors(int x) {
    auto pf = getPrimeFactors(x);
    vector<int> divisors = {1};

    for (auto [p, cnt] : pf) {
        int sz = divisors.size();
        long long pw = 1;
        for (int i = 1; i <= cnt; i++) {
            pw *= p;
            for (int j = 0; j < sz; j++) {
                divisors.push_back(divisors[j] * pw);
            }
        }
    }
    sort(divisors.begin(), divisors.end());
    return divisors;
}

