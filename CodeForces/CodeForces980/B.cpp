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
#define pb push_back

constexpr ll INF = 1e18;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
	    int n;
	    cin >> n;
	    vector<ll> score(n);
	    for(int i = 0; i < n; i++)
	        cin >> score[i];
	    vector<ll> pre(n);
	    for(int i = 0; i < n; i++) {
	        pre[i] = score[i];
	        if(i > 0)
	            pre[i] += pre[i-1];
	    }
	    vector<int> next(n);
	    for(int i = 0; i < n; i++) {
	        cin >> next[i];
	        next[i]--;
	    }
	    vector<ll> vis(n, INF);
	    priority_queue<pair<ll, int>> q;
	    q.push({0, 0});
	    ll ans = 0;
	    while(!q.empty()) {
	        auto [d, curr] = q.top();
	        q.pop();
	        d = -d;
	        if(vis[curr] != INF)
	            continue;
	        vis[curr] = d;
	        ans = max(ans, pre[curr]-d);
	        if(curr > 0)
	            q.push({-d, curr-1});
	        q.push({-d-score[curr], next[curr]});
	    }
	    cout << ans << "\n";
	}
}