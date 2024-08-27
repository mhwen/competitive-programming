#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <fstream>

using namespace std;

typedef long long ll;
constexpr ll MOD = 1e9+9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ifstream cin("team.in");
	ofstream cout("team.out");
	int n, m, teamSize;
	cin >> n >> m >> teamSize;
	vector<pair<ll, int>> cows;
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		cows.push_back({a, 0});
	}
	for(int i = 0; i < m; i++) {
		int b;
		cin >> b;
		cows.push_back({b, 1});
	}
	sort(cows.begin(), cows.end());
	
	vector<vector<vector<ll>>> dp(n+m+1, vector<vector<ll>>(teamSize+1, vector<ll>(teamSize+1)));
	dp[0][0][0] = 1;
	for(int i = 1; i <= n+m; i++) {
		int type = cows[i-1].second;
		
		for(int a = 0; a <= teamSize; a++) {
			for(int b = 0; b <= teamSize; b++) {
				dp[i][a][b] += dp[i-1][a][b];
				dp[i][a][b] %= MOD;
			}
		}
		
		//b
		if(type == 1) {
			for(int b = 0; b+1 <= teamSize; b++) {
				for(int a = 0; a <= teamSize; a++) {
					dp[i][a][b+1] += dp[i-1][a][b];
					dp[i][a][b+1] %= MOD;
				}
			}
		}
		//a
		else {
			for(int b = 0; b <= teamSize; b++) {
				for(int a = 0; a+1 <= teamSize; a++) {
					if(a+1 > b)
						continue;
					dp[i][a+1][b] += dp[i-1][a][b];
					dp[i][a+1][b] %= MOD;
				}
			}
		}
	}

	cout << dp[n+m][teamSize][teamSize] << "\n";
}