#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T = long long>
struct XorBasis {
    static const int B = 62; 
    T basis[B];
    int sz = 0;

    XorBasis() {
        memset(basis, 0, sizeof(basis));
        sz = 0;
    }

    void clear() {
        memset(basis, 0, sizeof(basis));
        sz = 0;
    }

    // Insert a number into the basis
    void insert(T x) {
        for (int i = B - 1; i >= 0; i--) {
            if ((x >> i) & 1) {
                if (!basis[i]) {
                    basis[i] = x;
                    sz++;
                    return;
                }
                x ^= basis[i];
            }
        }
    }

    // Is there any subset having xor = x
    bool contains(T x) {
        for (int i = B - 1; i >= 0; i--) {
            if ((x >> i) & 1) {
                if (!basis[i]) return false;
                x ^= basis[i];
            }
        }
        return x == 0;
    }

    // Max subset xor after xoring starting it with x
    T max_xor(T x = 0) {
        for (int i = B - 1; i >= 0; i--) {
            x = max(x, x ^ basis[i]);
        }
        return x;
    }

    // Min subset xor after xoring starting it with x
    T min_xor(T x = 0) {
        for (int i = B - 1; i >= 0; i--) {
            x = min(x, x ^ basis[i]);
        }
        return x;
    }

    // Kth smallest subset xor (1-based index)
    // 1st smallest is 0. Returns -1 if k > 2^sz.
    T kth_smallest(T k) {
        T total = (T)1 << sz;
        if (k < 1 || k > total) return -1;
        
        T res = 0;
        T cnt = total; 

        // Iterate MSB to LSB
        for (int i = B - 1; i >= 0; i--) {
            if (basis[i]) {
                cnt >>= 1; 
                if (k > cnt) {
                    if (!((res >> i) & 1)) res ^= basis[i];
                    k -= cnt;
                } 
                else {
                    if ((res >> i) & 1) res ^= basis[i];
                }
            }
        }
        return res;
    }

    // Kth largest subset xor
    T kth_largest(T k) {
        T total = (T)1 << sz;
        if (k < 1 || k > total) return -1;
        return kth_smallest(total - k + 1);
    }

    // Number of subsets having xor < x
    T count_less(T x) {
        if (x < 0) return 0;
        
        T res = 0;
        T cnt = (T)1 << sz;
        T current_path = 0;

        for (int i = B - 1; i >= 0; i--) {
            if (basis[i]) {
                cnt >>= 1;
                int bit_x = (x >> i) & 1;
                int bit_path = (current_path >> i) & 1;

                if (bit_x == 1) {
                    res += cnt;
                    if (bit_path == 0) current_path ^= basis[i];
                } else {
                    if (bit_path == 1) current_path ^= basis[i];
                }
            } else {
                int bit_x = (x >> i) & 1;
                int bit_path = (current_path >> i) & 1;
                
                if (bit_path != bit_x) {
                    if (bit_path < bit_x) return res + cnt;
                    else return res;
                }
            }
        }
        return res;
    }
};

int main() {
    XorBasis<long long> xb;
    vector<long long> arr = {2, 4, 5}; 
    for(long long x : arr) xb.insert(x);

    cout << "Max XOR: " << xb.max_xor() << endl;       // 7
    cout << "Min XOR start 7: " << xb.min_xor(7) << endl; // 0
    
    // Total subsets = 2^3 = 8. Values: 0,1,2,3,4,5,6,7
    cout << "3rd smallest: " << xb.kth_smallest(3) << endl; // 2
    cout << "Count < 4: " << xb.count_less(4) << endl;      // 4 (0,1,2,3)
    
    return 0;
}