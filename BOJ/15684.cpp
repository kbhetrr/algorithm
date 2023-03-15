#include <bits/stdc++.h>

using namespace std;

int n, m, h, MAP[33][33];
int res = 99999;

int check() {
    for (int i = 0; i < n; i++) {
        int x = i; int y = 0;
        while (1) {
            if (y == h) break;
            if (x != n - 1 && MAP[x][y]) x += 1;
            else if (x != 0 && MAP[x - 1][y]) x -= 1;
            y++;
        }
        if (x != i) return 0;
    }
    return 1;
}

void dfs(int d, int cnt, int nx, int ny) {
    if (cnt <= res && cnt <= 3) {
        if (check()) res = min(cnt, res);
    } else return;

    if (cnt >= 3) return;
    if (cnt >= res) return;

    if (nx == n - 1 && ny == h - 1) return;
    
    if (!MAP[nx][ny]) {
        MAP[nx][ny] = 1;
        if (ny + 1 >= h) dfs(d + 1, cnt + 1, nx + 1, 0);
        else dfs(d + 1, cnt + 1, nx, ny + 1);
        MAP[nx][ny] = 0;
    }

    if (ny + 1 >= h) dfs(d + 1, cnt, nx + 1, 0);
    else dfs(d + 1, cnt, nx, ny + 1);
}

int main() {
    cin >> n >> m >> h;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        MAP[b - 1][a - 1] = 1;
    }

    dfs(0, 0, 0, 0);

    if (res == 99999) cout << -1;
    else cout << res;

    return 0;
}