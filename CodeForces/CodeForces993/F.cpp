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
	int n, m, q;
	cin >> n >> m >> q;
	vector<ll> A, B;
	ll x = 0, y = 0;
	for(int i = 0; i < n; i++) {
		int a;
		cin >> a;
		y += a;
		A.push_back(a);
	}
	for(int i = 0; i < m; i++) {
		int b;
		cin >> b;
		x += b;
		B.push_back(b);
	}
	sort(all(A));
	sort(all(B));
	A.erase(unique(all(A)), A.end());
	B.erase(unique(all(B)), B.end());
	auto has = [&](vector<ll>& v, ll val) {
		auto it = lower_bound(all(v), val);
		if(it != v.end() && *it == val)
			return true;
		return false;
	};
	ll tot = x*y;
	bool zero = has(A, 0);
	set<ll> good;
	for(auto b : B) {
		if(zero)
			good.insert(tot-b*y);
		if(x-b == 0)
			good.insert(tot-b*y);
		else {
			ll curr = tot-(ll)2e5-b*y;
			curr -= curr%(x-b);
			ll amt = x-b>0 ? x-b : b-x;
			while(true) {
				ll M = tot-b*y-curr;
				if(M > (ll)2e5+amt || M < (ll)-2e5-amt)
					break;
				if(has(A, curr/(x-b)))
					good.insert(M);
				curr += amt;
			}
		}
	}
	while(q-->0) {
		int X;
		cin >> X;
		if(good.count(X))
			cout << "YES\n";
		else
			cout << "NO\n";
	}
	
}