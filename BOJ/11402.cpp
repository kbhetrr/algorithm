#include <bits/stdc++.h>

using namespace std;

long long int N, K, MOD, RES;
vector<long long int> A, B;

long long int dnc_pow(long long int x, long long int n) {
    if (n == 0) return 1 % MOD;
    long long u = dnc_pow(x, n / 2);
    u = (u * u) % MOD;
    if (n % 2 == 1) u = (u * x) % MOD;
    return u;
}

long long int get_bino(long long int n, long long int k) {
    long long int a, b;

    a = n;
    for (long long int i = n - 1; i >= n - k + 1; i--) a = (a * i) % MOD;

    b = 1;
    for (long long int i = 2; i <= k; i++) b = (b * i) % MOD;
    b = dnc_pow(b, MOD - 2);

    if (k == 0) return 1;
    else return (a * b) % MOD;
}

int main() {
    cin >> N >> K >> MOD;
    
    while (N > 0) {
        A.push_back(N % MOD);
        N /= MOD;
    }

    while (K > 0) {
        B.push_back(K % MOD);
        K /= MOD;
    }

    RES = 1;
    for (int i = 0; i < A.size(); i++) {
        long long int n, k;

        n = A[i];
        if (i >= B.size()) k = 0;
        else k = B[i]; 
        RES = (RES * get_bino(n, k)) % MOD;
    }

    cout << RES;

    return 0;
}