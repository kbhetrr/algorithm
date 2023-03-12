#include <bits/stdc++.h>

using namespace std;

int n, m, v[111];
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) v[i] = i + 1;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        
        int t = v[a - 1];
        v[a - 1] = v[b - 1];
        v[b - 1] = t;
    }

    for (int i = 0; i < n; i++) cout << v[i] << ' ';

    return 0;
}