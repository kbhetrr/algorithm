#include <bits/stdc++.h>

using namespace std;

int x, n, m, dir;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> x;
	
	if (x == 1) {
		cout << "1/1";
		return 0;
	}
	
	n = 1;
	m = 2;
	dir = 0;
	
	for (int i = 2; i < x; i++) {
		if (dir) {
			if (n == 1) {
				m++;
				dir = !dir;
			} else {
				m++;
				n--;
			}
		} else {
			if (m == 1) {
				n++;	
				dir = !dir;
			} else {
				n++;
				m--;
			}
		}
	}
	cout << n << "/" << m;

	return 0;
}
