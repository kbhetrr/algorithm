#include <bits/stdc++.h>

using namespace std;

int n, m, i, j, k, v[111];

int main() {
    cin >> n >> m;
    for (int t = 0; t < m; t++) {
        cin >> i >> j >> k;
        for (int s = i - 1; s < j; s++) v[s] = k;
    }

    for (int t = 0; t < n; t++) cout << v[t] << ' ';

    return 0;
}