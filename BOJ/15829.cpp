#include <bits/stdc++.h>

using namespace std;

int l;
string s;
long long int answer, p;

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	p = 1;

	cin >> l;
	cin >> s;
	
	for (int i = 0; i < l; i++) {
		long long int cursor = s[i] - 'a' + 1;
		answer += cursor * p;
		p *= 31;
		p %= 1234567891;
		answer %= 1234567891;
	}
	
	cout << answer;

	return 0;
}
