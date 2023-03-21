#include <bits/stdc++.h>

using namespace std;

int N, K, W0, CHK[1111][1111];
vector<pair<int, int>> original, gene, next_gene;

struct Random {
	mt19937 rd;
	Random() : rd((unsigned)chrono::steady_clock::now().time_since_epoch().count()) {}
	short GetInt(short l = 0, short r = 32767) {
		return uniform_int_distribution<short>(l, r)(rd);
	}
	double GetDouble(double l = 0, double r = 1) {
		return uniform_real_distribution<double>(l, r)(rd);
	}
} Rand;

int MIN_DIS[1111][1111], visited[1111];

int GET_SCORE() {
    vector<int> v[1111];
    for (int i = 0; i < N; i++) memset(MIN_DIS[i], 0, sizeof(MIN_DIS[i]));

    for (int i = 0; i < N - 1; i++) {
        v[original[i].first].push_back(original[i].second);
        v[original[i].second].push_back(original[i].first);
    }

    for (int i = 0; i < K; i++) {
        v[next_gene[i].first].push_back(next_gene[i].second);
        v[next_gene[i].second].push_back(next_gene[i].first);
    }

    memset(MIN_DIS, 0, sizeof(MIN_DIS));
    for (int i = 0; i < N; i++) {
        memset(visited, 0, sizeof(visited));
        queue<int> q;
        q.push(i);
        visited[i] = 1;
        MIN_DIS[i][i] = 0;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int next : v[curr]) {
                if (!visited[next]) {
                    q.push(next);
                    visited[next] = 1;
                    MIN_DIS[i][next] = MIN_DIS[i][curr] + 1;
                }
            }
        }
    }

    int score = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            score += MIN_DIS[i][j];
        }
    }
    return score;
}

int RES = 99999;
void SA(double T = 10.0, double d = 0.9999, double lim = 0.005) {
    int e1, e2;
    next_gene = gene;
    e1 = GET_SCORE();
    while (T >= lim) {
        next_gene = gene;
        double mutate_p = Rand.GetDouble();
        int x = Rand.GetInt(0, K - 1);
        int y = Rand.GetInt(0, N - 1);
        if (mutate_p >= 0.5) {
            while (next_gene[x].first == y || CHK[next_gene[x].second][y]) {
                y = Rand.GetInt(0, N - 1);
            }
            next_gene[x].first = y;
        } else {
            while (next_gene[x].second == y || CHK[next_gene[x].first][y]) {
                y = Rand.GetInt(0, N - 1);
            }
            next_gene[x].second = y;
        }
        e2 = GET_SCORE();
        double p = exp(-(e2 - e1) / (10.0 * T));
        if (p >= Rand.GetDouble()) {
            e1 = e2;
            gene = next_gene;
        }
        if (RES > e1) {
            RES = e1;
            cout << RES << "\n\n";
            cout << "-------------\n";

            
            for (auto i : gene) {
                cout << min(i.first, i.second) + 1 << ' ' << max(i.first, i.second) + 1 << '\n';
            }

            cout << "---------------\n";
        }
        T *= d;
    }
}

int main() {
    cin >> N >> K >> W0;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        original.push_back({ a - 1, b - 1 });
        CHK[a - 1][b - 1] = 1;
        CHK[b - 1][a - 1] = 1;
    }

    for (int i = 0; i < K; i++) {
        int a = Rand.GetInt(0, N - 1);
        int b = Rand.GetInt(0, N - 1);
        while (a == b || CHK[a][b]) {
            a = Rand.GetInt(0, N - 1);
            b = Rand.GetInt(0, N - 1);
        }
        gene.push_back({ a, b });
    }

    cout << "SA Start\n";
    while (1) SA();

    return 0;
}