#include<bits/stdc++.h>
using namespace std;

// ax + by = gcd
int egcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1; //gcd
}

// if gcd(a,m) = 1;
// ax + my = 1 => x is the mod inverse of a with mod m

int modinv(int a, int m){
    int x,y;
    int g = egcd(a,m,x,y);
    if(g==1) return (x%m + m)%m ;
    else return -1;
}