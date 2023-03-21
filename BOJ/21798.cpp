#include <bits/stdc++.h>
#include <fstream>

using namespace std;

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

int N, K, W0, visited[1001], dis[1001][1001], original[1001][1001], state[1001][1001], nxt_state[1001][1001];
int mutate_list[301][2], nxt_mutate_list[301][2], ANS[301][2];
vector<int> adj[1001];

int get_score() {
    // 평가할 인접 리스트 초기화
    for (int i = 0; i < 1001; i++) adj[i].clear();
    // original, nxt_state 값에 따라 인접 리스트 생성
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (original[i][j] || nxt_state[i][j]) adj[i].push_back(j);
        }
    }
    // 거리 배열 초기화
    memset(dis, 10e7, sizeof(dis));
    // 1 ~ N까지의 각 정점에 대해 BFS 수행
    for (int i = 0; i < N; i++) {
        memset(visited, 0, sizeof(visited));
        queue<int> q;

        q.push(i);
        visited[i] = 1;
        dis[i][i] = 0;
        while (!q.empty()) {
            int x = q.front();
            q.pop();

            for (auto nxt : adj[x]) {
                if (!visited[nxt]) {
                    visited[nxt] = 1;
                    q.push(nxt);
                    dis[i][nxt] = dis[i][x] + 1;
                }
            }
        }
    }
    // 생성된 거리 배열을 통해 점수 계산
    int score = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            score += min(dis[i][j], dis[j][i]);
        }
    }
    return score;
}

int RES = 10e7;

int main() {
    cin >> N >> K >> W0;

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        original[a - 1][b - 1] = original[b - 1][a - 1] = 1;
    }

    int SA_GENE = 0;
    while (1) {
        SA_GENE++;

        double T = 1.0;
        double d = 0.9995;
        int e1, e2;

        ifstream file("21798.txt");
        
        string line;
        int i = 0;
        while (getline(file, line)) {
            int a = 0; string a_t = ""; int a_cur = 0;
            int b = 0; string b_t = ""; int b_cur = 0;
            while (1) {
                if (line[a_cur] == ' ') break;
                a_t += line[a_cur];
                a_cur++;
            }
            a = stoi(a_t);
            b_cur = a_cur + 1;
            while (1) {
                if (b_cur >= line.length()) break;
                b_t += line[b_cur];
                b_cur++;
            }
            b = stoi(b_t);
        	state[a - 1][b - 1] = state[b - 1][a - 1] = 1;
            mutate_list[i][0] = a - 1;
            mutate_list[i][1] = b - 1;
            i++;
        }
        
        file.close();

        // 기존의 state를 다음 state에 복사
        memcpy(nxt_state, state, sizeof(int) * 1001 * 1001);
        memcpy(nxt_mutate_list, mutate_list, sizeof(int) * 301 * 2);
        // 현재 점수 저장
        e1 = get_score();
        // SA 실행
        while (T >= 0.0003) {
            memcpy(nxt_state, state, sizeof(int) * 1001 * 1001);
            memcpy(nxt_mutate_list, mutate_list, sizeof(int) * 301 * 2);
            // 변이 로직
            int n = Rand.GetInt(1, 10);
            for (int i = 0; i < 1; i++) {
                double mutate_p = Rand.GetDouble();
                int x = Rand.GetInt(0, K - 1);
                int y = Rand.GetInt(0, N - 1);
                if (mutate_p >= 0.5) {
                    int origin_a = nxt_mutate_list[x][0];
                    int origin_b = nxt_mutate_list[x][1]; 
                    while (origin_b == y || original[y][origin_b] || nxt_state[y][origin_b]) y = Rand.GetInt(0, N - 1);
                    nxt_state[origin_a][origin_b] = nxt_state[origin_b][origin_a] = 0;
                    nxt_mutate_list[x][0] = y;
                    nxt_state[y][origin_b] = nxt_state[origin_b][y] = 1;
                } else {
                    int origin_a = nxt_mutate_list[x][0];
                    int origin_b = nxt_mutate_list[x][1];
                    while (origin_a == y || original[origin_a][y] || nxt_state[origin_a][y]) y = Rand.GetInt(0, N - 1);
                    nxt_state[origin_a][origin_b] = nxt_state[origin_b][origin_a] = 0;
                    nxt_mutate_list[x][1] = y;
                    nxt_state[origin_a][y] = nxt_state[y][origin_a] = 1;
                }
            }
            // 변이 후 점수 저장
            e2 = get_score();

            double p = exp(-(e2 - e1) / (30.0 * T));
            if (p >= Rand.GetDouble()) {
                e1 = e2;
                memcpy(state, nxt_state, sizeof(int) * 1001 * 1001);
                memcpy(mutate_list, nxt_mutate_list, sizeof(int) * 301 * 2);
            }
            if (RES > e1) {
                RES = e1;
                memcpy(ANS, mutate_list, sizeof(int) * 301 * 2);
                
                ofstream outFile; // 출력 파일 객체 선언
                outFile.open("21798.txt"); // 파일 열기
                
                for (int i = 0; i < K; i++) {
                    outFile << ANS[i][0] + 1 << ' ' << ANS[i][1] + 1 << endl;
            	}

                outFile.close(); // 파일 닫기
            }
            
            printf("SA: %d, NOW TEMP: %.5lf, NOW SCORE: %d, BEST SCORE: %d, P: %.5lf\r", SA_GENE, T, e1, RES, 18.0 * (double)pow(20.0, (double)1 - ((double)RES / (double)W0)));
            T *= d;
        }
    } 

    // 기존 original에 없는 간선 k개만큼 추가
    /*
    for (int i = 0; i < K; i++) {
        int a, b;
        do {
            a = Rand.GetInt(0, N - 1); b = Rand.GetInt(0, N - 1);
        } while (a == b || original[a][b]);
        state[a][b] = state[b][a] = 1;
        mutate_list[i][0] = a;
        mutate_list[i][1] = b;
    }*/
    // 기존 값으로 추가

    return 0;
}
