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

ll binpow(ll a, ll b) {
	ll p = a;
	ll res = 1;
	while(b > 0) {
		if(b%2==1)
			res = res*p;
		b/=2;
		if(b)
			p = p*p;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int t;
	cin >> t;
	while(t-->0) {
		int n;
		ll k;
		cin >> n >> k;
		ll p = 1;
		int cnt = 0;
		while(p < k) {
			p *= 2;
			cnt++;
		}
		vector<int> front;
		vector<int> back;
		for(int i = 0; i < n-1; i++) {
			int rem = n-i-1;
			if(rem > 60)
				front.push_back(i+1);
			else {
				ll po = binpow(2, rem-1);
				if(po < k) {
					k -= po;
					back.push_back(i+1);
				}
				else
					front.push_back(i+1);
			}
		}
		if(k > 1) {
			cout << -1 << "\n";
			continue;
		}
		front.push_back(n);
		for(int i : front)
			cout << i << " ";
		reverse(all(back));
		for(int i : back)
			cout << i << " ";
		cout << "\n";
	}
}