#include<bits/stdc++.h>

using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

typedef __gnu_pbds::tree<long long, __gnu_pbds::null_type, less<long long>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> ordered_set;

// ordered set/ordered_multiset :two additional operations in log(n)
    // order_of_key: The number of items in a set that are strictly smaller than k
    // find_by_order: It returns an iterator to the ith largest element



// int main(){
//     int n;
//     cin>>n;
//     ordered_multiset st;
//     for(int i=0;i<n;i++){
//         int t;
//         cin>>t;
//         st.insert(t);
//     }
//     cout<<st.order_of_key(2);
// }