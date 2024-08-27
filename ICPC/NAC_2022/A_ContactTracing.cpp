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

//7:50
//7:55

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, k, c;
	cin >> n >> k >> c;
	vector<vector<pair<int, int>>> edges(k+1);
	vector<int> latest(n, -1);
	for(int i = 0; i < c; i++) {
		int a, b, d;
		cin >> a >> b >> d;
		a--; b--;
		latest[a] = max(latest[a], d);
		latest[b] = max(latest[b], d);
		edges[d].push_back({a, b});
	}
	vector<vector<bool>> infected(k+1, vector<bool>(n));
	for(int i = 0; i < n; i++) {
		if(latest[i] <= 1)
			infected[0][i] = true;
	}
	for(int d = 1; d <= k; d++) {
		for(auto[a, b] : edges[d]) {
			if(infected[d-1][a] && latest[b]-d <= 1)
				infected[d][b] = true;
			if(infected[d-1][b] && latest[a]-d <= 1)
				infected[d][a] = true;
		}
	}
	vector<int> ans;
	for(int i = 0; i < n; i++) {
		if(infected[k][i])
			ans.push_back(i+1);
	}
	cout << sz(ans) << "\n";
	for(int i : ans)
		cout << i << "\n";
}