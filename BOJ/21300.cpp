#include <bits/stdc++.h>

using namespace std;

int n;

int main() {
	cin >> n;
	
	cout << (int)(n - (n * 0.22)) << " " << (int)(n - (n * 0.2 * 0.22));
	
	return 0;
}
