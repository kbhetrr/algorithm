#include <bits/stdc++.h>

using namespace std;

int n, m, MAP[11][11], CHK_MAP[11][11];
int res = 10000;
vector<pair<int, pair<int, int>>> CCTV;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

int d3[4][2] = { { 1, -1 }, { 1, 1 }, { -1, 1 }, { -1, -1 } };

void dfs(int d) {
    if (d == CCTV.size()) {
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (CHK_MAP[i][j] == 0) cnt++;
            }
        }
        res = min(res, cnt);
        return;
    }

    int x = CCTV[d].second.first;
    int y = CCTV[d].second.second;

    int CHK_MAP_CPY[11][11];
    memcpy(CHK_MAP_CPY, CHK_MAP, sizeof(CHK_MAP));

    if (CCTV[d].first == 1) {
        for (int i = 0; i < 4; i++) {
            int nx = x; int ny = y;
            while (1) {
                nx += dx[i]; ny += dy[i];
                if (!(0 <= nx && nx < n && 0 <= ny && ny < m)) break;
                if (MAP[nx][ny] == 6) break;
                CHK_MAP[nx][ny] = 1;
            }
            dfs(d + 1);
            memcpy(CHK_MAP, CHK_MAP_CPY, sizeof(CHK_MAP));
        }
    } else if (CCTV[d].first == 2) {
        for (int i = 0; i < 2; i++) {
            int nx = x; int ny = y;
            while (1) {
                nx += dx[i]; ny += dy[i];
                if (!(0 <= nx && nx < n && 0 <= ny && ny < m)) break;
                if (MAP[nx][ny] == 6) break;
                CHK_MAP[nx][ny] = 1;
            }
            nx = x; ny = y;
            while (1) {
                nx += dx[i + 2]; ny += dy[i + 2];
                if (!(0 <= nx && nx < n && 0 <= ny && ny < m)) break;
                if (MAP[nx][ny] == 6) break;
                CHK_MAP[nx][ny] = 1;
            }
            dfs(d + 1);
            memcpy(CHK_MAP, CHK_MAP_CPY, sizeof(CHK_MAP));
        }
    } else if (CCTV[d].first == 3) {
        for (int i = 0; i < 4; i++) {
            int nx = x; int ny = y;
            while (1) {
                nx += d3[i][0];
                if (!(0 <= nx && nx < n && 0 <= y && y < m)) break;
                if (MAP[nx][y] == 6) break;
                CHK_MAP[nx][y] = 1;
            }
            nx = x;
            while (1) {
                ny += d3[i][1];
                if (!(0 <= x && x < n && 0 <= ny && ny < m)) break;
                if (MAP[x][ny] == 6) break;
                CHK_MAP[x][ny] = 1;
            }
            dfs(d + 1);
            memcpy(CHK_MAP, CHK_MAP_CPY, sizeof(CHK_MAP));
        }
    } else if (CCTV[d].first == 4) {
        for (int i = 0; i < 4; i++) {
            int nx = x; int ny = y;
            while (1) {
                nx += d3[i][0];
                if (!(0 <= nx && nx < n && 0 <= y && y < m)) break;
                if (MAP[nx][y] == 6) break;
                CHK_MAP[nx][y] = 1;
            }
            while (1) {
                ny += d3[i][1];
                if (!(0 <= x && x < n && 0 <= ny && ny < m)) break;
                if (MAP[x][ny] == 6) break;
                CHK_MAP[x][ny] = 1;
            }
            if (i % 2 == 0) {
                nx = x;
                while (1) {
                    nx += -d3[i][0];
                    if (!(0 <= nx && nx < n && 0 <= y && y < m)) break;
                    if (MAP[nx][y] == 6) break;
                    CHK_MAP[nx][y] = 1;
                }

            } else {
                ny = y;
                while (1) {
                    ny += -d3[i][1];
                    if (!(0 <= x && x < n && 0 <= ny && ny < m)) break;
                    if (MAP[x][ny] == 6) break;
                    CHK_MAP[x][ny] = 1;
                }
            }
            dfs(d + 1);
            memcpy(CHK_MAP, CHK_MAP_CPY, sizeof(CHK_MAP));
        }
    } else if (CCTV[d].first == 5) {
        for (int i = 0; i < 4; i++) {
            int nx = x; int ny = y;
            while (1) {
                nx += dx[i]; ny += dy[i];
                if (!(0 <= nx && nx < n && 0 <= ny && ny < m)) break;
                if (MAP[nx][ny] == 6) break;
                CHK_MAP[nx][ny] = 1;
            }
        }
        dfs(d + 1);
        memcpy(CHK_MAP, CHK_MAP_CPY, sizeof(CHK_MAP));
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> MAP[i][j];
            if (1 <= MAP[i][j] && MAP[i][j] <= 5) CCTV.push_back({ MAP[i][j], { i, j } });
            if (MAP[i][j] != 0) CHK_MAP[i][j] = 1;
        }
    }

    dfs(0);

    cout << res;

    return 0;
}