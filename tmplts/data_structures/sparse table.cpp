// Might give segmentation fault locally for large MAXN but will work in custon invocation


#include<bits/stdc++.h>

using namespace std;
#define int long long

int log2_floor(unsigned long i) {
    return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
}

signed main(){

    vector<int> array = {1,5,3,1,5}; 

    int  MAXN = 2*1e5, K = log2_floor(MAXN),N=5;  // maxn is max size of array, k is atleast floor of log base 2 maxn
    int st[K + 1][MAXN];

    copy(array.begin(), array.end(), st[0]);

    for (int i = 1; i <= K; i++)
    for (int j = 0; j + (1 << i) <= N; j++){
        // st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]); 
        // f is the function for range query

        // st[i][j] = st[i - 1][j] + st[i - 1][j + (1 << (i - 1))]; --> Precompute for Range sum queries
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);  // range min queries
    }

    // Range sum queries --> O(log N)
    // long long sum = 0;
    // for (int i = K; i >= 0; i--) {
    //     if ((1 << i) <= R - L + 1) {
    //         sum += st[i][L];
    //         L += 1 << i;
    //     }
    // }


    // Range min query --> O(1)
    int L = 1,R=4;
    int i = log2_floor(R - L + 1);
    int minimum = min(st[i][L], st[i][R - (1 << i) + 1]);

    cout<<minimum<<endl;

    return 0;

}