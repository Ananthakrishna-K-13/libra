#include<bits/stdc++.h> 
using namespace std;
const int mod = 998244353;

int binpow(int a, int b, long long m = mod){
    a %= m;
    int res = 1;
    while (b > 0){
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res%m;
}

// binpow(number,mod-2,mod) gives mod inverse if mod is prime