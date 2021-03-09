#include <bits/stdc++.h>

using namespace std;

double xa, ya, xb, yb, xc, yc;

double dist(double A1, double B1, double A2, double B2){
    return sqrt((A1-A2) * (A1-A2) + (B1-B2) * (B1-B2));
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> xa >> ya >> xb >> yb >> xc >> yc;
	
	double m1 = 987654321;
	double m2 = 987654321;
	
	if (xa != xb) m1 = abs(xb - xa) / abs(yb - ya);
	if (xb != xc) m2 = abs(xb - xc) / abs(yb - yc);
	
	if (m1 == m2) {
		cout << -1;
		return 0;
	}
	
	double ab = dist(xa, ya, xb, yb);
	double ac = dist(xa, ya, xc, yc);
	double bc = dist(xb, yb, xc, yc);
	
	double temp1 = (ab + ac) * 2;
	double temp2 = (ab + bc) * 2;
	double temp3 = (bc + ac) * 2;
	
	cout << fixed;
	cout.precision(16);
	
	cout << max({temp1, temp2, temp3}) - min({temp1, temp2, temp3});

	return 0;
}
