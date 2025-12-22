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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	vector<set<int>> atX(1e5+2);
	for(int i = 0; i < sz(atX); i++)
	    atX[i].insert(0);
	for(int i = 0; i < n; i++) {
	    int x, y;
	    cin >> x >> y;
	    atX[x].insert(y);
	}
	
	array<map<pair<int, int>, pair<int, int>>, 2> ans;
	function<pair<int, int>(pair<int, int>)> solve;
	
	auto solveDir = [&](auto&& self, pair<int, int> xy, int dir) -> pair<int, int> {
	    if(ans[dir].count(xy))
	        return ans[dir][xy];

	    auto [x, y] = xy;
	    if(y == 1)
	        return {0, 0};
	    auto it = atX[x].upper_bound(y);
	    it--;
	    int stopY = *it;
	    if(stopY == y)
	        return ans[dir][xy] = {0, 0};
	    else if(stopY == y-1) {
	        int dx = dir ? 1 : -1;
	        return ans[dir][xy] = self(self, {x+dx, y}, dir);
	    }
	    else {
	        int newY = stopY+1;
	        int dist = y-newY;
	        auto [hi, lo] = solve({x, newY});
	        return ans[dir][xy] = {max(dist, hi), max(dist, lo)};
	    }
	};
	
	solve = [&](pair<int, int> xy) -> pair<int, int> {
	    auto [hi1, lo1] = solveDir(solveDir, xy, 0);
	    auto [hi2, lo2] = solveDir(solveDir, xy, 1);
	    if(hi1 == 0)
	        hi1 = hi2;
	    if(lo1 == 0)
	        lo1 = lo2;
	    if(hi2 == 0)
	        hi2 = hi1;
	    if(lo2 == 0)
	        lo2 = lo1;
	    return {max(hi1, hi2), min(lo1, lo2)};
	};

	int q;
	cin >> q;
	while(q-->0) {
	    int x, y;
	    cin >> x >> y;
	    auto [hi, lo] = solve({x, y});
	    cout << hi << " " << lo << "\n";
	}
}