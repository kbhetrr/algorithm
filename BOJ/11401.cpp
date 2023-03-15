#include <bits/stdc++.h>

using namespace std;

long long int n, k, a, b;
long long int MOD = 1'000'000'007;

long long int dnc_pow(long long int x, long long int m) {
    if (m == 0) return 1 % MOD;
    long long u = dnc_pow(x, m / 2);
    u = (u * u) % MOD;
    if (m % 2 == 1) u = (u * x) % MOD;
    return u;
}

int main() {
    cin >> n >> k;

    a = n;
    for (long long int i = n - 1; i >= n - k + 1; i--) a = (a * i) % MOD;

    b = 1;
    for (long long int i = 2; i <= k; i++) b = (b * i) % MOD;
    b = dnc_pow(b, MOD - 2);

    if (k == 0) cout << 1;
    else cout << (a * b) % MOD;

    return 0;
}