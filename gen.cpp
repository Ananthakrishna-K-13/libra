#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

long long randInt(long long L, long long R) {
    return uniform_int_distribution<long long>(L, R)(rng);
}

int main() {
    int a = randInt(1, 1000000000);
    int b = randInt(0,9);
    return 0;
}