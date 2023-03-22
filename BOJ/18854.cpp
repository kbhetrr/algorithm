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

int n = 499, m = 499;
vector<vector<int>> dango;
vector<int> dango_chk;
vector<string> MAP;
int CHK[501][501];

int BEST_SCORE = 0;

bool is_dango(char a, char b, char c) {
	return (a == 'P' && b == 'W' && c == 'G') || (a == 'G' && b == 'W' && c == 'P');
}

int main() {
	memset(CHK, -1, sizeof(CHK));
	
	string line;
    ifstream file("18854.txt");
    while (getline(file, line)) {
		MAP.push_back(line);
    }
    
    file.close();
    
	for (int i = 0; i < n; i++) {
    	for (int j = 0; j < m; j++) {
	    	if (MAP[i][j] == 'W') continue;
			if (i + 3 <= n && is_dango(MAP[i][j], MAP[i + 1][j], MAP[i + 2][j])) {
				dango.push_back({i * m + j, (i + 1) * m + j, (i + 2) * m + j, 0});
				dango_chk.push_back(0);
			}
			if (j + 3 <= m && is_dango(MAP[i][j], MAP[i][j + 1], MAP[i][j + 2])) {
				dango.push_back({i * m + j, i * m + j + 1, i * m + j + 2, 1});
				dango_chk.push_back(0);
			}
			if (i + 3 <= n && j + 3 <= m && is_dango(MAP[i][j], MAP[i + 1][j + 1], MAP[i + 2][j + 2])) {
				dango.push_back({i * m + j, (i + 1) * m + j + 1, (i + 2) * m + j + 2, 2});
				dango_chk.push_back(0);
			}
			if (i + 3 <= m && j - 2 >= 0 && is_dango(MAP[i][j], MAP[i + 1][j - 1], MAP[i + 2][j - 2])) {
				dango.push_back({i * m + j, (i + 1) * m + j - 1, (i + 2) * m + j - 2, 3});
				dango_chk.push_back(0);
			}
		}
  	}
  	
	int cnt = 0, last = -1;
	// 47220, 41980, 51390, 19120, 48620, 46500
	int bound = 46500;
	for (int it = 0; it < 1000000 && cnt < bound; it++) {
		vector<int> now;
		for (int i = 0; i < dango.size(); i++) {
			if (!dango_chk[i]) now.push_back(i);
		}
		random_shuffle(now.begin(), now.end());
		for (auto p : now) {
			int x = dango[p][0] / m, y = dango[p][0] % m;
			
			if (CHK[x][y] == p) continue;
			
			vector<int> bs;
			for (int i = 0; i < 3; ++i) {
				int u = dango[p][i];
				int x = u / m, y = u % m;
				if (CHK[x][y] != -1) bs.push_back(CHK[x][y]);
			}
			
			sort(bs.begin(), bs.end());
			bs.erase(unique(bs.begin(), bs.end()), bs.end());
			
			if (bs.size() >= 2) {
	        	if (last == -1 || it - last < 100) continue;
			}
			for (auto &x : bs) {
				dango_chk[x] = 0;
				for (int i = 0; i < 3; i++) {
			    	int u = dango[x][i];
					int x = u / m, y = u % m;
			    	CHK[x][y] = -1;
			    }
				cnt--;
			}
			
      		if (bs.empty()) last = it;
			dango_chk[p] = 1;
			for (int i = 0; i < 3; i++) {
		    	int u = dango[p][i];
				int x = u / m, y = u % m;
		    	CHK[x][y] = p;
		    }
			cnt++;
		}
		
		if (it % 1000 == 0) fprintf(stderr, "it=%d cnt=%d\n", it, cnt);
	}
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (CHK[i][j] != -1) {
				int c = CHK[i][j];
				int x = dango[c][1] / m, y = dango[c][1] % m;
				int t = dango[c][3];
				MAP[x][y] = "|-\\/"[t];
			}
		}
	}
	
	ofstream outFile;
    outFile.open("18854_out.txt");
    
    for (int i = 0; i < n; i++) {
        outFile << MAP[i] << endl;
	}

    outFile.close();
	
	
	return 0;
}