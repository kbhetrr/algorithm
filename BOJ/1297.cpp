#include <bits/stdc++.h>

using namespace std;

int d, h, w;
double r;

int main() {
	cin >> d >> h >> w;
	
	r = d / sqrt(pow(h, 2) + pow(w, 2));
	
	cout << floor(h * r) << " " << floor(w * r);
	
	return 0;
}
