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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	auto check = [&](vector<pair<int, int>> r) {
	    auto [ax, ay] = r[0];
	    auto [bx, by] = r[1];
	    auto [cx, cy] = r[2];
	    auto [dx, dy] = r[3];
	    
	    if(ay==by && cy==dy && ax+bx==cx+dx && ax+bx==ay+cy)
	        return true;
	    if(ay==by && by==cy && cy==dy && ax+bx+cx+dx==ay)
	        return true;
	    if(bx==cx && cx==dx && by+cy+dy==ay && ax+bx==ay)
	        return true;
	    if(ay==by && cx==dx && cy+dy==by && ax+bx+cx==ay)
	        return true;
	    if(cy==dy && cx+dx==bx && ay==by+cy && ay==ax+bx)
	        return true;
	    return false;
	};
	vector<pair<int, int>> rects(4);
	for(int i = 0; i < 4; i++) {
	    cin >> rects[i].first >> rects[i].second;
	}
	vector<int> perm{0, 1, 2, 3};
	int ans = 0;
	do {
    	for(int mask = 0; mask < (1<<4); mask++) {
    	    vector<pair<int, int>> r;
    	    for(int i = 0; i < 4; i++) {
    	        auto [x, y] = rects[perm[i]];
    	        if(mask & (1<<i))
    	            swap(x, y);
    	        r.pb({x, y});
    	    }
    	    if(check(r)) ans = 1;
    	}
    } while(next_permutation(all(perm)));
    cout << ans << "\n";
}