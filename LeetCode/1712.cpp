#include <bits/stdc++.h>

using namespace std;

int n, p[100001], l, r;
long long int answer;
vector<int> num;

int main() {
    ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n;
	for (int i = 0; i < n; i++) {
	    int temp;
	    cin >> temp;
	    num.push_back(temp);
	}

	// 누적 합 구하기.
	p[0] = num[0];
	for (int i = 1; i < n; i++) {
        p[i] = num[i] + p[i - 1];
	    cout << p[i] << ' ';
	}

	for (int i = 0; i < n; i++) {
	    l = max(l, i + 1);
	    while (l < n - 1 && p[l] < 2 * p[i]) l++;
	    r = max(l, r);
	    while (r < n - 1 && p[r] <= (p[n - 1] + p[i]) / 2) r++;
	    answer += (r - l);
	}

    cout << answer;

    return 0;
}