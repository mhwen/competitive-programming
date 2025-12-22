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
typedef long double ld;
#define sz(x) (int)(x).size()
#define all(x) begin(x), end(x)

char l[5] = {'n', 'a', 'r', 'e' ,'k'};
constexpr ll INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	map<char, int> ma;
	for(int i = 0; i < 5; i++) {
		ma[l[i]] = i;
	}
	int t;
	cin >> t;
	while(t-->0) {
		int n, m;
		cin >> n >> m;
		
		auto process = [&](string& s, int start) {
			int amt = 0;
			for(char c : s) {
				if(ma.count(c) == 0)
					continue;
				int id = ma[c];
				if(id == start) {
					start++;
					if(start == 5) {
						amt+=5;
						start = 0;
					}
				}
				else
					amt--;
			}
			return pair{amt, start};
		};
		
		vector<ll> dp(5, -INF);
		dp[0] = 0;
		
		for(int i = 0; i < n; i++) {
			string s;
			cin >> s;
			vector<ll> newDp = dp;
			for(int j = 0; j < 5; j++) {
				if(dp[j] == -INF)
					continue;
				auto res = process(s, j);
				int gain = res.first;
				int id = res.second;
				newDp[id] = max(newDp[id], dp[j]+gain);
			}
			dp = newDp;
		}
		ll best = 0;
		for(int i = 0; i < 5; i++)
			best = max(best, dp[i]-i);
		cout << best << "\n";
	}
}