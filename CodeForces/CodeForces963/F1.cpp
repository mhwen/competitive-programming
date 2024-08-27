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
#define all(x) begin(x), end(x)

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n, k, w, h;
		cin >> n >> k >> w >> h;
		int X = w+1;
		int Y = h+1;
		w = w*2;
		h = h*2;
		string s;
		cin >> s;
		map<pair<int, int>, int> counts;
		
		auto move = [&](int& x, int& y, int dx, int dy) {
			x += dx;
			y += dy;
			x = (x+w)%w;
			y = (y+h)%h;
			return;
		};
		
		auto dist = [&](int x, int y, int x2, int y2) {
			int dx = x2-x;
			int dy = y2-y;
			dx = (dx+w)%w;
			dy = (dy+h)%h;
			return pair<int, int>{dx, dy};
		};
		int dx = 0;
		int dy = 0;
		for(char c : s) {
			if(c == 'U')
				dy++;
			if(c == 'D')
				dy--;
			if(c == 'L')
				dx--;
			if(c == 'R')
				dx++;
			dx = (dx+w)%w;
			dy = (dy+h)%h;
			counts[{dx, dy}]++;
		}
		ll ans = 0;
		int x = X;
		int y = Y;
		for(int i = 0; i < k; i++) {
			auto want = dist(x, y, X, Y);
			ans += counts[want];
			move(x, y, dx, dy);
		}
		cout << ans << "\n";
	}
}