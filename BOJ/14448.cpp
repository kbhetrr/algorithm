#include <bits/stdc++.h>

using namespace std;

int n, N[55], NEXT_N[55], STATUS[55], NEXT_STATUS[55], ANS;

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

int GET_LIS() {
    vector<int> LIS;
    for (int i = 0; i < n; i++) {
        if (LIS.empty() || LIS.back() <= NEXT_N[i]) LIS.push_back(NEXT_N[i]);
        else *lower_bound(LIS.begin(), LIS.end(), NEXT_N[i]) = NEXT_N[i];
    }
    return LIS.size();
}

void REVERSE_N() {
    for (int s = 0, e = n - 1; s < e; s++, e--) {
        while (s < e && !NEXT_STATUS[s]) s++;
        while (s < e && !NEXT_STATUS[e]) e--;
        if (s < e) {
            int temp = NEXT_N[s];
            NEXT_N[s] = NEXT_N[e];
            NEXT_N[e] = temp;
        }
    }
}

int SA(double lim = 0.000001, double T = 10.0, double d = 0.9999) {
    int e1, e2;
    int RES = 0;

    memcpy(NEXT_N, N, sizeof(int) * n);

    e1 = 1;

    for (int i = 0; i < 100000; i++, T *= d) {
        memcpy(NEXT_STATUS, STATUS, sizeof(int) * n);

        int MUTATE = Rand.GetInt(0, n - 1);
        NEXT_STATUS[MUTATE] = !NEXT_STATUS[MUTATE];
        memcpy(NEXT_N, N, sizeof(int) * n);

        REVERSE_N();
        e2 = GET_LIS();

        double p = exp(-(e1 - e2) / (1.0 * T));
        if (p >= Rand.GetDouble()) {
            e1 = e2;
            memcpy(STATUS, NEXT_STATUS, sizeof(int) * n);
        }
        RES = max(RES, e1);
    }
    return RES;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> N[i];
    for (int i = 0; i < 20; i++) ANS = max(ANS, SA());
    cout << max(1, ANS);

    return 0;
}