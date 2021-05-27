#include <bits/stdc++.h>

#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
using pii = pair<int, int>;

vector<int> suffix_array(string s) {
    s+="#";
    int n = s.size(), N = n + 256;
    vector<int> sa(n), ra(n);
    for(int i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
    for(int k = 0; k < n; k ? k *= 2 : k++) {
        vector<int> nsa(sa), nra(n), cnt(N);
        for(int i = 0; i < n; i++) nsa[i] = (nsa[i] - k + n) % n;
        for(int i = 0; i < n; i++) cnt[ra[i]]++;
        for(int i = 1; i < N; i++) cnt[i] += cnt[i - 1];
        for(int i = n - 1; i >= 0; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];
 
        int r = 0;
        for(int i = 1; i < n; i++) {
            if(ra[sa[i]] != ra[sa[i - 1]]) r++;
            else if(ra[(sa[i] + k) % n] != ra[(sa[i - 1] + k) % n]) r++;
            nra[sa[i]] = r;
        }
        ra = nra;
    }
    sa.erase(sa.begin());
    return sa;
}

vector<int> build_lcp(const string& s, const vector<int>& sa) {
    int n=s.size();
    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[sa[i]] = i;

    vector<int> lcp(n);
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (pos[i]==0) continue;
        if (k) k--;
        while (s[i+k] == s[sa[pos[i]-1]+k]) k++;
        lcp[pos[i]] = k;
    }
    return lcp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin>>s;
    auto sa=suffix_array(s);
    auto lcp=build_lcp(s, sa);
    for (auto i : sa) cout << i << ' ';
    cout << '\n';
    lcp.push_back(0);
    for (auto i : lcp) cout << i << ' ';
    cout << '\n';
    int ans=s.size();
    cout << ans << '\n';
    int l=0;
    for (int i=1; i<(int)s.size(); i++) {
        int len=max(lcp[i], lcp[i+1])+1;
        if (len>s.size()-sa[i]) continue;
        if (len<ans) {
            ans=len;
            l=sa[i];
        } else if (len==ans) l=min(l, sa[i]);
    }
    cout<<s.substr(l, ans);
}
