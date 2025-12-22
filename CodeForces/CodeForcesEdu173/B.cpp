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

ll fact(ll a) {
	ll res = 1;
	for(ll i = 1; i <= a; i++)
		res *= i;
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		ll n, d;
		cin >> n >> d;
		set<ll> ans{1};
		if(n >= 3 || d%3==0)
			ans.insert(3);
		if(d%5==0)
			ans.insert(5);
		if(n >= 3 || d%7==0)
			ans.insert(7);
		if(n >= 6 || fact(n)*d%9==0)
			ans.insert(9);
		for(auto a : ans)
			cout << a << " ";
		cout << "\n";
	}
}