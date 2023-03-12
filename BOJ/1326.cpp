#include <bits/stdc++.h>

using namespace std;

int n, a, b, arr[11111], res;
queue<pair<int, int>> q;

int main() {
	cin >> n;
	
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	cin >> a >> b;
	res = -1;
		
	q.push({ a, 0 });
	
	while(!q.empty()) {
		pair<int, int> c = q.front();
		q.pop();
		if (c.first == b) {
			res = c.second;
			break;
		}
		int next = arr[c.first];
		int i = 1;
		while (1) {
			int next_step1 = c.first + (next * i);
			int next_step2 = c.first - (next * i);
			if (next_step1 <= n) q.push({ next_step1, c.second + 1 });
			if (next_step2 >= 1) q.push({ next_step2, c.second + 1 });
			if (next_step1 > n && next_step2 < 1) break;
			i++;
		}
	}
	
	cout << res;
	
	return 0;
}
