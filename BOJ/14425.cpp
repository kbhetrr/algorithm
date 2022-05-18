#include <bits/stdc++.h>

using namespace std;

map<string, int> v;
int res;

int main() {
	int n, m;
	cin >> n >> m;
	
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		v[s] = 1;
	}
	
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		if (v[s] == 1) res++;
	}
	
	cout << res;
	
	return 0;
}
