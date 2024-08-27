#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <functional>


using namespace std;

typedef long long ll;
constexpr int BASE = 3000;
constexpr ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k;
		cin >> n >> k;
		vector<vector<vector<ll>>> counts(n+1, vector<vector<ll>>(n));
		for(int i = 1; i <= k; i++) {
			int left = i-1;
			int right = 0;
			while((int)counts[i][left].size() <= right)
				counts[i][left].push_back(0);
			counts[i][left][right] = 1;
		}
		for(int i = 1; i < n; i++) {
			for(int j = 0; j < (int)counts[i].size(); j++) {
				for(int h = 0; h < (int)counts[i][j].size(); h++) {
					int left = j;
					int right = h;
					ll val = counts[i][left][right];
					if(left+right+1 < k && left+1+i <= n) {
						while((int)counts[left+1+i][left].size() <= right+1) {
							counts[left+1+i][left].push_back(0);
						}
						counts[left+1+i][left][right+1] += val;
						counts[left+1+i][left][right+1] %= MOD;
					}
					if(right+1+i <= n) {
						while(counts[right+1+i][right].size() <= 0)
							counts[right+1+i][right].push_back(0);
						counts[right+1+i][right][0] += val;
						counts[right+1+i][right][0] %= MOD;
					}
				}
			}
		}
		ll ans = 0;
		for(int j = 0; j < (int)counts[n].size(); j++) {
			for(int h = 0; h < (int)counts[n][j].size(); h++) {
				ans += counts[n][j][h];
				ans %= MOD;
			}
		}
		cout << ans << "\n";
	}
}