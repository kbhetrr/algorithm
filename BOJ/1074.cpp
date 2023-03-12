#include <bits/stdc++.h>

using namespace std;

int N, r, c, ans;

void dnc(int n, int x, int y) {
    if (r == x && c == y) { cout << ans; return; }

    if (x <= r && r < x + n && y <= c && c < y + n) {
        dnc(n / 2, x, y);
        dnc(n / 2, x, y + n / 2);
        dnc(n / 2, x + n / 2, y);
        dnc(n / 2, x + n / 2, y + n / 2);
    } else ans += n * n;
};

int main() {
    cin >> N >> r >> c;
    
    dnc(pow(2, N), 0, 0);

    return 0;
}