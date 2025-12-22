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

constexpr int INF = 1e9;

typedef map<int, vector<pair<int, int>>> trans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<int> color(89);
	color[2] = color[5] = color[7] = color[10] = color[12] = 1;
	for(int i = 13; i < sz(color); i++)
		color[i] = color[i-12];
	vector<vector<trans>> up(4, vector<trans>(15));
	vector<vector<trans>> down(4, vector<trans>(15));
	vector<int> cnts(4);
	for(int i = 0; i < 4; i++)
		cin >> cnts[i];
	int L;
	cin >> L;
	for(int C = 0; C < sz(cnts); C++) {
		for(int i = 0; i < cnts[C]; i++) {
			int lo, hi;
			cin >> lo >> hi;
			for(int step = 1; step <= 12; step++) {
				int h;
				cin >> h;
				up[C][step][lo].emplace_back(hi, h);
				down[C][step][hi].emplace_back(lo, h);
			}
		}
	}

	vector<int> notes(L);
	for(int i = 0; i < L; i++) {
		cin >> notes[i];
	}

	vector<int> dp(6);
	for(int i = 1; i < L; i++) {
		if(notes[i] == notes[i-1])
			continue;
		bool goHi = notes[i] > notes[i-1];
		vector<int> newDp(6, INF);
		int lo = min(notes[i], notes[i-1]);
		int hi = max(notes[i], notes[i-1]);
		int mask = color[lo]*2+color[hi];
		int dist = hi-lo;
		for(int from = 1; from <= 5; from++) {
			if(dp[from] == INF)
				continue;
			if(goHi) {
				for(auto [next, cost] : up[mask][dist][from]) {
					newDp[next] = min(newDp[next], dp[from]+cost);
				}
			}
			else {
				for(auto [next, cost] : down[mask][dist][from]) {
					newDp[next] = min(newDp[next], dp[from]+cost);
				}
			}
		}
		dp = newDp;
	}
	cout << *min_element(all(dp)) << "\n";
}