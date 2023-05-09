#include <bits/stdc++.h>

using namespace std;

int n, cnt, cur;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	
	cin >> n;
	
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		if (i == 0 || cur <= t) {
			cnt++;
		}
		cur = t;
	}
	
	cout << cnt;
	
	return 0;
}