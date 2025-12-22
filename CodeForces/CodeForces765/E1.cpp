#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <cmath>
#include <numeric>
#include <iomanip>
#include <cassert>

using namespace std;
typedef long long ll;
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, q;
	cin >> n >> q;
	string s;
	cin >> s;
	vector<ll> cnt(n);
	vector<ll> tot(n);
	vector<int> level(n, -1);
	vector<int> posInLevel(n, -1);
	vector<vector<ll>> levelSum(n, vector<ll>{0});
	int L = 0;
	stack<int> st;
	for(int i = 0; i < n; i++) {
		if(s[i] == '(') {
			level[i] = L++;
			st.push(i);
		}
		else {
			if(st.empty())
				continue;
			int left = st.top();
			st.pop();
			L--;
			cnt[i] = cnt[left];
			level[i] = level[left];
			assert(level[i] == L);
			posInLevel[left] = posInLevel[i] = sz(levelSum[L]);
			tot[i] = tot[left] += 1+cnt[i]*(cnt[i]-1)/2;
			levelSum[L].push_back(levelSum[L].back()+tot[i]);
			if(!st.empty()) {
				cnt[st.top()]++;
				tot[st.top()] += tot[i];
			}
		}
	}
	while(q-->0) {
		int t, l, r;
		cin >> t >> l >> r;
		l--; r--;
		assert(level[l] == level[r]);
		int lev = level[l];
		int lpos = posInLevel[l];
		int rpos = posInLevel[r];
		ll diff = rpos-lpos+1;
		cout << levelSum[lev][rpos]-levelSum[lev][lpos-1]+diff*(diff-1)/2 << "\n";
	}
}