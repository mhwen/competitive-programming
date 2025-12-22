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

constexpr int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m, k;
	cin >> n >> m >> k;
	vector<int> bad(1<<n);
	for(int i = 0; i < m; i++) {
	    string s;
	    cin >> s;
	    int mask = 0;
	    for(int bit = 0; bit < n; bit++) {
	        if(s[bit] == '1')
	            mask |= (1<<bit);
	    }
	    bad[mask] = 1;
	}
	for(int mask = 0; mask < sz(bad); mask++) {
	    for(int bit = 0; bit < n; bit++) {
	        bad[mask|(1<<bit)] |= bad[mask];
	    }
	}
	
	auto id = [&](int mask, int side, int taken) {
	    return (mask*2+side)*(k+1)+taken;
	};
	
	vector<int> vis((1<<n)*2*(k+1), INF);
	deque<pair<pair<int, int>, pair<int, int>>> q;
	q.push_back({{0, 0}, {0, 0}});
	int tot = (1<<n)-1;
	while(!q.empty()) {
	    auto curr = q.front();
	    q.pop_front();
	    auto [mask, dist] = curr.first;
	    auto [side, taken] = curr.second;
	    if(vis[id(mask, side, taken)] != INF)
	        continue;
	    vis[id(mask, side, taken)] = dist;
	    if(taken == 0 && side == 1 && mask == tot)
	        break;
	    vector<int> masks = {tot^mask, mask};
	    //move the boat
	    if(!bad[masks[side]] && vis[id(mask, side^1, 0)] == INF)
	        q.push_back({{mask, dist+1}, {side^1, 0}});
	    
	    //fill the boat more
	    if(taken < k) {
	        int mySide = masks[side];
	        for(int bit = 0; bit < n; bit++) {
	            if(mySide & (1<<bit)) {
	                int newMask = mask^(1<<bit);
	                if(vis[id(newMask, side, taken+1)] == INF)
	                    q.push_front({{newMask, dist}, {side, taken+1}});
	            }
	        }
	    }
	}
	int ans = vis[id(tot, 1, 0)];
	if(ans == INF)
	    ans = -1;
	cout << ans << "\n";
	
}