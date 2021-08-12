#include <bits/stdc++.h>

using namespace std;

int n, r, c;

int main() {
	cin >> n;
	
	r = n / 2 + 1;
	c = n - r + 2;
	
	cout << r * c;
	
	return 0;
}
