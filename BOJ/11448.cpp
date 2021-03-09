#include <bits/stdc++.h>

using namespace std;

int tc, n, answer, visited[111][111];
vector<string> MAP;

int dx[] = { -1, 0, 1, 1, 1, 0, -1, -1 };
int dy[] = { -1, -1, -1, 0, 1, 1, 1, 0 };

void dfs(int y, int x) {
	visited[y][x] = 1;
	if (MAP[y][x] == '-') answer++;
	for (int i = 0; i < 8; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 <= nx && nx < n && 0 <= ny && ny < n) {
			if ((MAP[ny][nx] == 'w' || MAP[ny][nx] == '-') && !visited[ny][nx]) dfs(ny, nx);
		}
	}
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> tc;
	while (tc--) {
		answer = 0;
		MAP.clear();
		memset(visited, 0, sizeof(visited));
		
		cin >> n;
		for (int i = 0; i < n; i++) {
			string temp;
			cin >> temp;
			MAP.push_back(temp);
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if ((MAP[i][j] == 'w') && !visited[i][j]) dfs(i, j);
			}
		}
		
		cout << answer << '\n';
	}

	return 0;
}
