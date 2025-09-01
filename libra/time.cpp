#include<bits/stdc++.h> 
using namespace std;

#define int long long
#define pb push_back
#define all(x) (x).begin(), (x).end()

#ifdef AKLOCAL
#include "dbg.hpp"
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define dbg(x...)
#define endl '\n'
#endif

void solve()  {

}

signed main(){
    #ifdef AKLOCAL
    auto begin = std::chrono::high_resolution_clock::now();
    #endif
    
    ios_base::sync_with_stdio(false);   
    cin.tie(NULL); cout.tie(NULL);

    int T = 1;          
    cin>>T;
    for(int i=1;i<=T;i++) solve();

    #ifdef AKLOCAL
    auto end = std::chrono::high_resolution_clock::now();
    cerr << setprecision(4) << fixed;
    cerr << "-> " << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << " sec" << endl;
    #endif

    return 0;
}