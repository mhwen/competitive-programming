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

constexpr ll MAX = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		cin >> n;
		ll c1 = -1e18, c2 = -1e18;
		for(int i = 0; i < n; i++) {
			ll x, y;
			cin >> x >> y;
			c1 = max(c1, x+y);
			c2 = max(c2, y-x);
		}
		
		ll DX = 0, DY = 0;
		auto query = [&](ll dx, ll dy) {
			DX += dx;
			DY += dy;
			assert(dx == 0 || dy == 0);
			ll k = abs(dx)+abs(dy);
			string dir = "L";
			if(dx) {
				if(dx < 0) dir = "L";
				else dir = "R";
			}
			else {
				assert(dy);
				if(dy < 0) dir = "D";
				else dir = "U";
			}
			cout << "? " << dir << " " << k << endl;
			ll res;
			cin >> res;
			return res;
		};
		query(MAX, 0);
		query(MAX, 0);
		query(0, MAX);
		ll d1 = query(0, MAX);
		query(-MAX, 0);
		query(-MAX, 0);
		query(-MAX, 0);
		query(-MAX, 0);
		query(-MAX, 0);
		ll d2 = query(-MAX, 0);
		
		//(x+OFFSET)+y-c1 = d1
		//-x+y-c2 = d2
		//OFFSET+2y-c1-c2=d1+d2
		//y = d1+d2+c1+c2-OFFSET;
		ll OFFSET = 6*MAX;
		assert((d1+d2+c1+c2-OFFSET)%2==0);
		ll Y = (d1+d2+c1+c2-OFFSET)/2;
		ll X = d1+c1-Y-OFFSET;
		cout << "! " << X-DX << " " << Y-DY << endl;
	}
}