#include<bits/stdc++.h> 
using namespace std;

#define int long long
#define float long double
#define vi vector<int>
#define pii pair<int,int>
#define x first
#define y second
#define fr(i,a,b) for(int i=a;i<b;i++)
#define frn for(int i=0;i<n;i++)
#define pb push_back
#define all(x) (x).begin(), (x).end()
template <typename T>istream&operator>>(istream& in, vector<T>& a){for (int i = 0; i < a.size(); ++i)in >> a[i];return in;}
template <typename T>ostream&operator<<(ostream& out,vector<T>& a){for (int i = 0; i < a.size(); ++i) out << a[i] << " ";out << "\n";return out;}

#ifdef AKLOCAL
#include "dbg.hpp"
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define dbg(x...)
#define endl '\n'
#endif

void solve(){

    int l,r;
    cin>>l>>r;

    int lim = sqrt(r)+1;

    vi base_primes;
    vector<bool> is_prime(lim+1,1);
    for(int i=2;i*i<=r;i++){
        if(!is_prime[i]) continue; 
        for(int j = i*i;j<=lim;j+=i) {
            // dbg(j);
            is_prime[j] = false;
        }
    }

    for(int i = 2;i*i<=r;i++) if(is_prime[i]) base_primes.pb(i);

    vi is_prime_seg(r-l+1,1);
    for(int p : base_primes){
        int st = ((l+p-1)/p) * p;
        for(int j = st;j<=r;j+=p) is_prime_seg[j-l] = p;
    }
    if(l==1) is_prime_seg[0] = false;
    // is_prime_seg[i] = true ==> l+i is prime
}           

signed main(){
    ios_base::sync_with_stdio(false);   
    cin.tie(NULL); cout.tie(NULL);

    int T = 1;          
    // cin>>T;
    for(int i=1;i<=T;i++) solve();

    return 0;
}