#include<bits/stdc++.h> 
using namespace std;
const int mod = 998244353;

bool prime[15000105]; 
void sieve(int n) { 
    for (int i = 0; i <= n; i++) prime[i] = 1;
    for (int p = 2; p * p <= n; p++)
        if (prime[p] == true)  
            for (int i = p * p; i <= n; i += p)  prime[i] = false; 
     
    prime[1] = prime[0] = 0;
} 
    
vector<int> primelist;
// call Seive before this 
void genprimes(int n){ 
    for (int i = 2; i <= n; i++) if (prime[i]) primelist.push_back(i);
}


// TC:O(sqrt(n)/log(n)) --> no of prime less than n = O(n/log(n));
// Call genprimes before this
// Gives repeated primes --> make unique if required
// If causes !!TLE!! copy the inner code inside solve -> reduces tc due to vector push back

vector<int> factors(int n){ 
    vector<int> facs;

    for (int i = 0; primelist[i] * primelist[i] <= n && i < primelist.size(); i++){
    if (n % primelist[i] == 0) {
        while (n % primelist[i] == 0) {
        n /= primelist[i];
        facs.push_back(primelist[i]);
        }
    }
    }
    if (n > 1) {
    facs.push_back(n);
    }
    sort(facs.begin(), facs.end());
    // set<int> factset(all(facs));
    // facs.clear();
    // for(int i: factset) facs.pb(i);
    
    // for unique only
    return facs;
}

