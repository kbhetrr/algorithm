#include <bits/stdc++.h>

using namespace std;

int n, mod, prefix[100001], l, r;
long long int answer;
vector<int> num;

int main() {
    ios_base :: sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	mod = 100000007;

	cin >> n;
	for (int i = 0; i < n; i++) {
	    int temp;
	    cin >> temp;
	    num.push_back(temp);
	}

	// 누적 합 구하기.
	prefix[0] = num[0];
	for (int i = 1; i < n; i++) {
        prefix[i] = num[i] + prefix[i - 1];
	}

	for (int i = 0; i < n; i++) cout << prefix[i] << ' ';

	for (int i = 0; i < n; i++) {


	}


    return 0;
}