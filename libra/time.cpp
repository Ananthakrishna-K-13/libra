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