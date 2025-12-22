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

constexpr ll INF = 4e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, L;
	cin >> n >> L;
	vector<ll> clumps(n);
	for(int i = 0; i < n; i++) {
		cin >> clumps[i];
	}
	clumps.push_back(L);
	sort(all(clumps));
	vector vis(n+1, vector(n+1, vector<ll>(2, INF)));
	priority_queue<pair<ll, pair<int, pair<int, int>>>> q;
	for(int i = 0; i < sz(clumps); i++) {
		if(clumps[i] == L) {
			q.push({0, {0, {i, i}}});
			break;
		}
	}
	while(!q.empty()) {
		auto curr = q.top();
		q.pop();
		ll dist = -curr.first;
		int side = curr.second.first;
		int l = curr.second.second.first;
		int r = curr.second.second.second;
		if(vis[l][r][side] != INF)
			continue;
		vis[l][r][side] = dist;
		ll remaining = sz(clumps)-(r-l+1);
		ll loc = side == 0 ? clumps[l] : clumps[r];
		if(l > 0) {
			ll time = loc-clumps[l-1];
			q.push({-dist-time*remaining, {0, {l-1, r}}});
		}
		if(r < sz(clumps)-1) {
			ll time = clumps[r+1]-loc;
			q.push({-dist-time*remaining, {1, {l, r+1}}});
		}
	}
	cout << min(vis[0][n][0], vis[0][n][1]) << "\n";
}