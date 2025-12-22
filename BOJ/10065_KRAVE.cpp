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
	int w, h;
	cin >> w >> h;
	vector<set<int>> x(2*(w+1));
	vector<set<int>> y(2*(h+1));
	auto update = [&](int l, int r, int val, vector<set<int>>& tree) {
		int n = sz(tree)/2;
		l+=n; r+=n;
		for(; l<=r; l/=2, r/=2) {
			if(l%2==1)
				tree[l++].insert(val);
			if(r%2==0)
				tree[r--].insert(val);
		}
	};
	auto query = [&](int p, int val, vector<set<int>>& tree) {
		int n = sz(tree)/2;
		p+=n;
		int lBound = -1, rBound = INF;
		while(p > 0) {
			auto it = tree[p].upper_bound(val);
			if(it != tree[p].end())
				rBound = min(rBound, *it);
			if(it != tree[p].begin())
				lBound = max(lBound, *prev(it));
			p/=2;
		}
		return make_pair(lBound, rBound);
	};
	//boundary lines
	update(0, w, 0, x);
	update(0, w, h, x);
	update(0, h, 0, y);
	update(0, h, w, y);

	int n;
	cin >> n;
	while(n-->0) {
		int X, Y, d;
		cin >> X >> Y >> d;
		//horizontal
		if(d == 1) {
			auto xBounds = query(Y, X, y);
			auto yBounds = query(X, Y, x);
			ll dx = xBounds.second-xBounds.first;
			ll dy1 = yBounds.second-Y;
			ll dy2 = Y-yBounds.first;
			if(dy1 > dy2)
				swap(dy1, dy2);
			cout << dy1*dx << " " << dy2*dx << "\n";
			update(xBounds.first, xBounds.second, Y, x);
		}
		//vertical
		else {
			auto yBounds = query(X, Y, x);
			auto xBounds = query(Y, X, y);
			ll dy = yBounds.second-yBounds.first;
			ll dx1 = xBounds.second-X;
			ll dx2 = X-xBounds.first;
			if(dx1 > dx2)
				swap(dx1, dx2);
			cout << dx1*dy << " " << dx2*dy << "\n";
			update(yBounds.first, yBounds.second, X, y);
		}
	}
}