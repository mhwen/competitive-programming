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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	vector three(501, vector<pair<int, int>>(66, {INF, 0}));
	vector six(501, vector<pair<int, int>>(66, {INF, 0}));
	three[0][0] = six[0][0] = {0, 0};
	int val = 1;
	for(int i = 0; i < 500; i++) {
		for(int m = 0; m < 66; m++) {
			if(three[i][m].first != INF) {
				int nxt = (3*val+m)%66;
				three[i+1][nxt] = min(three[i+1][nxt], {3, m});
				nxt = (6*val+m)%66;
				six[i+1][nxt] = min(six[i+1][nxt], {3, m});
			}
			if(six[i][m].first != INF) {
				int nxt = (3*val+m)%66;
				three[i+1][nxt] = min(three[i+1][nxt], {6, m});
				nxt = (6*val+m)%66;
				six[i+1][nxt] = min(six[i+1][nxt], {6, m});
			}
		}
		val = val*10%66;
	}
	
	auto recover = [&](int n) {
		string ans = "";
		int curr = INF;
		if(three[n][0].first != INF)
			curr = 3;
		else if(six[n][0].first != INF)
			curr = 6;
		if(curr == INF)
			return string("-1");
		int level = n;
		int m = 0;
		while(level > 0) {
			ans += to_string(curr);
			if(curr == 3) {
				curr = three[level][m].first;
				m = three[level][m].second;
			}
			else {
				curr = six[level][m].first;
				m = six[level][m].second;
			}
			level--;
		}
		return ans;
	};
	
	while(t-->0) {
		int n;
		cin >> n;
		cout << recover(n) << "\n";
	}
}