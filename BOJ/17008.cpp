#include <bits/stdc++.h>

#include <cstddef>
#include <cstdint>

using namespace std;

int n, m;
int C[11111][3];

using i8 = int8_t;
using u8 = uint8_t;
using i16 = int16_t;
using u16 = uint16_t;
using i32 = int32_t;
using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128_t;
using u128 = __uint128_t;
using usize = size_t;
using f32 = float;
using f64 = double;
using f80 = long double;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int> dis2(1, 100);
uniform_real_distribution<double> rnd_real(0, 1);


template<class T, class U>
T incMod(T x, U mod) {
	x += 1;
	return x == mod ? 0 : x;
}

template<class Domain, class CoDomain, size_t LEN = 75>
std::pair<Domain, CoDomain> dlas(
	std::function<CoDomain(Domain&)> f,
	std::function<void(Domain&)> mutate,
	Domain const& initial,
	u64 maxIdleIters = -1ULL
) {
	std::array<Domain, 50> S;
	S.fill(initial);
	CoDomain curF = f(S[0]);
	size_t curPos = 0;
	size_t minPos = 0;

	std::array<CoDomain, LEN> fitness;
	std::fill(fitness.begin(), fitness.end(), curF);
	CoDomain minF = curF;
	size_t k = 0;

	for (u64 idleIters = 0; idleIters < maxIdleIters; idleIters += 1) {
		CoDomain prvF = curF;

		size_t newPos = incMod(curPos, 50);
		if (newPos == minPos) newPos = incMod(newPos, 50);

		Domain& curS = S[curPos];
		Domain& newS = S[newPos];

		newS = curS;
		mutate(newS);
		CoDomain newF = f(newS);
		if (newF < minF) {
			idleIters = 0;
			minPos = newPos;
			minF = newF;
		}
		if (newF == curF || newF < *std::max_element(fitness.begin(), fitness.end())) {
			curPos = newPos;
			curF = newF;
		}

		CoDomain& fit = fitness[k];
		if (curF > fit || curF < fit && curF < prvF) {
			fit = curF;
		}
		k = incMod(k, LEN);
	}
	return { S[minPos], minF };
}

struct Item {
  int res[1001];
};

int BEST_SCORE = 0;
int get_score(Item& item) {
    int s = 0;
    for (int i = 0; i < m; i++) {
      bool now = false;
      now |= C[i][0] > 0 ? item.res[C[i][0]] : !item.res[-C[i][0]];
      now |= C[i][1] > 0 ? item.res[C[i][1]] : !item.res[-C[i][1]];
      now |= C[i][2] > 0 ? item.res[C[i][2]] : !item.res[-C[i][2]];
      s += now;
    }
    return -s;
}

void mutate(Item& item) {
    uniform_int_distribution<int> dis(1, n);
	int c_n = dis(gen);
    item.res[c_n] = !item.res[c_n];
}

pair<Item, int> result;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
    uniform_int_distribution<int> dis(0, 1);
    cin >> n >> m;
  
    for (int i = 0; i < m; i++) {
        cin >> C[i][0] >> C[i][1] >> C[i][2];
    }
	
	for (int j = 1; j <= n; j++) result.first.res[j] = dis(gen);
	int flag = 0;
    for (int i = 0; i < 12; i++) {
    	if (flag) break;
	    result = dlas<Item, int>(get_score, mutate, result.first, 512);
        if (-result.second == m) {
			flag = 1;
			cout << "1\n";
			for (int j = 1; j <= n; j++) {
				cout << result.first.res[j] << ' ';
			}
			break;
		}
    }
    
    if (!flag) cout << '0';
  
	return 0;
}