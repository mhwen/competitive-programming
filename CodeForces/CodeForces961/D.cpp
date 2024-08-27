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

using namespace std;
typedef long long ll;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, c, k;
		cin >> n >> c >> k;
		string s;
		cin >> s;
		for(int i = 0; i < k; i++) {
			s += s.back();
		}
		vector<int> cnts(c);
		int myMask = 0;
		auto add = [&](int i) {
			cnts[i]++;
			if(cnts[i] == 1)
				myMask ^= (1<<i);
		};
		auto subtract = [&](int i) {
			cnts[i]--;
			if(cnts[i] == 0)
				myMask ^= (1<<i);
		};
		vector<bool> bad(1<<c);
		for(int i = 0; i < sz(s); i++) {
			add(s[i]-'A');
			if(i >= k)
				subtract(s[i-k]-'A');
			if(i >= k-1)
				bad[myMask] = true;
		}
		for(int mask = 0; mask < (1<<c); mask++) {
			for(int bit = 0; bit < c; bit++) {
				if(!(mask & (1<<bit))) {
					bad[mask^(1<<bit)] = bad[mask^(1<<bit)]|bad[mask];
				}
			}
		}
		int best = c;
		for(int mask = 0; mask < (1<<c); mask++) {
			if(!bad[mask])
				best = min(best, c-__builtin_popcount(mask));
		}
		cout << best << "\n";
	}
}