//BOJ 11401 이항계수3
//exponentiation by squaring + modular inverse

#include <iostream>

using namespace std;
using ll = long long;

const int dv = 1'000'000'007;
ll fact[4000001];

void init() {
    fact[0] = 1;
    for (int i = 1; i <= 4000000; i++) {
        fact[i] = (fact[i - 1] * i) % dv;
    }
}

int main() {
    
    int n, k;
    cin >> n >> k;
    init();

    ll res = 1,lower = (fact[k] * fact[n - k]) % dv;
    int pow = dv - 2;

    while (pow) {
        if (pow & 1) res = (res * lower) % dv;
        pow >>= 1;
        lower = (lower * lower) % dv;
    }

    res = (res * fact[n]) % dv;
    cout << res;

    return 0;
}
